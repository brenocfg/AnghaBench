#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jstring ;
typedef  int /*<<< orphan*/  jmethodID ;
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_5__ {int /*<<< orphan*/  (* GetStaticMethodID ) (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  (* FindClass ) (TYPE_1__**,char*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  bailif0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prop2env (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 

int ProcessSystemProperties(JNIEnv *env)
{
  jclass cls;
  jmethodID mid;
  jstring jName, jValue;
  const char *value;

  bailif0(cls = (*env)->FindClass(env, "java/lang/System"));
  bailif0(mid = (*env)->GetStaticMethodID(env, cls, "getProperty",
    "(Ljava/lang/String;)Ljava/lang/String;"));

  prop2env("turbojpeg.optimize", "TJ_OPTIMIZE");
  prop2env("turbojpeg.arithmetic", "TJ_ARITHMETIC");
  prop2env("turbojpeg.restart", "TJ_RESTART");
  prop2env("turbojpeg.progressive", "TJ_PROGRESSIVE");
  return 0;

bailout:
  return -1;
}