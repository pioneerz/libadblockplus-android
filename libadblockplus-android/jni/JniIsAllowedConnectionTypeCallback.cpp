/*
 * This file is part of Adblock Plus <https://adblockplus.org/>,
 * Copyright (C) 2006-present eyeo GmbH
 *
 * Adblock Plus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * Adblock Plus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Adblock Plus.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "JniCallbacks.h"
#include "Utils.h"

JniIsAllowedConnectionTypeCallback::JniIsAllowedConnectionTypeCallback(JNIEnv* env,
    jobject callbackObject)
    : JniCallbackBase(env, callbackObject)
{
}

bool JniIsAllowedConnectionTypeCallback::Callback(const std::string* allowedConnectionType)
{
  JNIEnvAcquire env(GetJavaVM());

  jmethodID method = env->GetMethodID(
      *JniLocalReference<jclass>(*env, env->GetObjectClass(GetCallbackObject())),
      "isConnectionAllowed",
      "(Ljava/lang/String;)Z");

  jstring jAllowedConnectionType =
    (allowedConnectionType != NULL
    ? JniStdStringToJava(*env, *allowedConnectionType)
    : NULL);
  bool result = env->CallBooleanMethod(GetCallbackObject(), method, jAllowedConnectionType);

  CheckAndLogJavaException(*env);
  return result;
}