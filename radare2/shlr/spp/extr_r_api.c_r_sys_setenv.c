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

/* Variables and functions */
 int SetEnvironmentVariableA (char const*,char const*) ; 
 int setenv (char const*,char const*,int) ; 
 int /*<<< orphan*/  unsetenv (char const*) ; 

int r_sys_setenv(const char *key, const char *value) {
	if (!key) {
		return 0;
	}
#if __UNIX__
	if (!value) {
		unsetenv (key);
		return 0;
	}
	return setenv (key, value, 1);
#elif __WINDOWS__
	int ret = SetEnvironmentVariableA (key, value);
	return ret ? 0 : -1;
#else
#warning r_sys_setenv : unimplemented for this platform
	return 0;
#endif
}