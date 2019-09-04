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

int r_sys_setenv(const char *key, const char *value) {
#if __UNIX__ || __CYGWIN__ && !defined(MINGW32)
	if (!key) {
		return 0;
	}
	if (!value) {
		unsetenv (key);
		return 0;
	}
	return setenv (key, value, 1);
#elif __WINDOWS__
	SetEnvironmentVariable (key, (LPSTR)value);
	return 0; // TODO. get ret
#else
#warning s_sys_setenv : unimplemented for this platform
	return 0;
#endif
}