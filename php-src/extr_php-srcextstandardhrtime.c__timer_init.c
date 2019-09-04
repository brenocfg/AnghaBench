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

__attribute__((used)) static int _timer_init()
{/*{{{*/
#if PHP_HRTIME_PLATFORM_WINDOWS

	LARGE_INTEGER tf = {0};
	if (!QueryPerformanceFrequency(&tf) || 0 == tf.QuadPart) {
		return -1;
	}
	_timer_scale = (double)NANO_IN_SEC / (php_hrtime_t)tf.QuadPart;

#elif PHP_HRTIME_PLATFORM_APPLE

	if (mach_timebase_info(&_timerlib_info)) {
		return -1;
	}

#elif PHP_HRTIME_PLATFORM_POSIX

#if !_POSIX_MONOTONIC_CLOCK
#ifdef _SC_MONOTONIC_CLOCK
	if (0 >= sysconf(_SC_MONOTONIC_CLOCK)) {
		return -1;
	}
#endif
#endif

#elif PHP_HRTIME_PLATFORM_HPUX

	/* pass */

#elif PHP_HRTIME_PLATFORM_AIX

	/* pass */

#else
	/* Timer unavailable. */
	return -1;
#endif

	return 0;
}