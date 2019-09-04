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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  cdf_timestamp_t ;

/* Variables and functions */

int
/*ARGSUSED*/
cdf_timespec_to_timestamp(cdf_timestamp_t *t, const struct timespec *ts)
{
#ifndef __lint__
	(void)&t;
	(void)&ts;
#endif
#ifdef notyet
	struct tm tm;
	if (php_gmtime_r(&ts->ts_sec, &tm) == NULL) {
		errno = EINVAL;
		return -1;
	}
	*t = (ts->ts_nsec / 100) * CDF_TIME_PREC;
	*t = tm.tm_sec;
	*t += tm.tm_min * 60;
	*t += tm.tm_hour * 60 * 60;
	*t += tm.tm_mday * 60 * 60 * 24;
#endif
	return 0;
}