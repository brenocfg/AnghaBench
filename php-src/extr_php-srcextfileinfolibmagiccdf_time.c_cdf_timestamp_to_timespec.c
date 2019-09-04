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
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_year; scalar_t__ tm_isdst; scalar_t__ tm_yday; scalar_t__ tm_wday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_mday; } ;
struct timespec {int tv_nsec; int tv_sec; } ;
typedef  int cdf_timestamp_t ;

/* Variables and functions */
 scalar_t__ CDF_BASE_YEAR ; 
 int CDF_TIME_PREC ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  cdf_getday (int,int) ; 
 int cdf_getdays (int) ; 
 int /*<<< orphan*/  cdf_getmonth (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int mktime (struct tm*) ; 

int
cdf_timestamp_to_timespec(struct timespec *ts, cdf_timestamp_t t)
{
	struct tm tm;
#ifdef HAVE_STRUCT_TM_TM_ZONE
	static char UTC[] = "UTC";
#endif
	int rdays;

	/* Unit is 100's of nanoseconds */
	ts->tv_nsec = (t % CDF_TIME_PREC) * 100;

	t /= CDF_TIME_PREC;
	tm.tm_sec = (int)(t % 60);
	t /= 60;

	tm.tm_min = (int)(t % 60);
	t /= 60;

	tm.tm_hour = (int)(t % 24);
	t /= 24;

	/* XXX: Approx */
	tm.tm_year = (int)(CDF_BASE_YEAR + (t / 365));

	rdays = cdf_getdays(tm.tm_year);
	t -= rdays - 1;
	tm.tm_mday = cdf_getday(tm.tm_year, (int)t);
	tm.tm_mon = cdf_getmonth(tm.tm_year, (int)t);
	tm.tm_wday = 0;
	tm.tm_yday = 0;
	tm.tm_isdst = 0;
#ifdef HAVE_STRUCT_TM_TM_GMTOFF
	tm.tm_gmtoff = 0;
#endif
#ifdef HAVE_STRUCT_TM_TM_ZONE
	tm.tm_zone = UTC;
#endif
	tm.tm_year -= 1900;
	ts->tv_sec = mktime(&tm);
	if (ts->tv_sec == -1) {
		errno = EINVAL;
		return -1;
	}
	return 0;
}