#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  jvmtiJlocationFormat ;
typedef  int /*<<< orphan*/  jvmtiEventCallbacks ;
typedef  int /*<<< orphan*/  jvmtiEnv ;
typedef  int /*<<< orphan*/  jvmtiCapabilities ;
typedef  int /*<<< orphan*/  JavaVM ;

/* Variables and functions */

int main(void)
{
	JavaVM			jvm	__attribute__((unused));
	jvmtiEventCallbacks	cb	__attribute__((unused));
	jvmtiCapabilities	caps	__attribute__((unused));
	jvmtiJlocationFormat	format	__attribute__((unused));
	jvmtiEnv		jvmti	__attribute__((unused));

	return 0;
}