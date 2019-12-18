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
struct pg_tm {int tm_sec; int tm_min; int tm_hour; int tm_isdst; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
typedef  int /*<<< orphan*/  pg_tz ;
typedef  int pg_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_VALID_JULIAN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MINS_PER_HOUR ; 
 int SECS_PER_DAY ; 
 int SECS_PER_MINUTE ; 
 int UNIX_EPOCH_JDATE ; 
 int date2j (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pg_next_dst_boundary (int*,long*,int*,int*,long*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
DetermineTimeZoneOffsetInternal(struct pg_tm *tm, pg_tz *tzp, pg_time_t *tp)
{
	int			date,
				sec;
	pg_time_t	day,
				mytime,
				prevtime,
				boundary,
				beforetime,
				aftertime;
	long int	before_gmtoff,
				after_gmtoff;
	int			before_isdst,
				after_isdst;
	int			res;

	/*
	 * First, generate the pg_time_t value corresponding to the given
	 * y/m/d/h/m/s taken as GMT time.  If this overflows, punt and decide the
	 * timezone is GMT.  (For a valid Julian date, integer overflow should be
	 * impossible with 64-bit pg_time_t, but let's check for safety.)
	 */
	if (!IS_VALID_JULIAN(tm->tm_year, tm->tm_mon, tm->tm_mday))
		goto overflow;
	date = date2j(tm->tm_year, tm->tm_mon, tm->tm_mday) - UNIX_EPOCH_JDATE;

	day = ((pg_time_t) date) * SECS_PER_DAY;
	if (day / SECS_PER_DAY != date)
		goto overflow;
	sec = tm->tm_sec + (tm->tm_min + tm->tm_hour * MINS_PER_HOUR) * SECS_PER_MINUTE;
	mytime = day + sec;
	/* since sec >= 0, overflow could only be from +day to -mytime */
	if (mytime < 0 && day > 0)
		goto overflow;

	/*
	 * Find the DST time boundary just before or following the target time. We
	 * assume that all zones have GMT offsets less than 24 hours, and that DST
	 * boundaries can't be closer together than 48 hours, so backing up 24
	 * hours and finding the "next" boundary will work.
	 */
	prevtime = mytime - SECS_PER_DAY;
	if (mytime < 0 && prevtime > 0)
		goto overflow;

	res = pg_next_dst_boundary(&prevtime,
							   &before_gmtoff, &before_isdst,
							   &boundary,
							   &after_gmtoff, &after_isdst,
							   tzp);
	if (res < 0)
		goto overflow;			/* failure? */

	if (res == 0)
	{
		/* Non-DST zone, life is simple */
		tm->tm_isdst = before_isdst;
		*tp = mytime - before_gmtoff;
		return -(int) before_gmtoff;
	}

	/*
	 * Form the candidate pg_time_t values with local-time adjustment
	 */
	beforetime = mytime - before_gmtoff;
	if ((before_gmtoff > 0 &&
		 mytime < 0 && beforetime > 0) ||
		(before_gmtoff <= 0 &&
		 mytime > 0 && beforetime < 0))
		goto overflow;
	aftertime = mytime - after_gmtoff;
	if ((after_gmtoff > 0 &&
		 mytime < 0 && aftertime > 0) ||
		(after_gmtoff <= 0 &&
		 mytime > 0 && aftertime < 0))
		goto overflow;

	/*
	 * If both before or both after the boundary time, we know what to do. The
	 * boundary time itself is considered to be after the transition, which
	 * means we can accept aftertime == boundary in the second case.
	 */
	if (beforetime < boundary && aftertime < boundary)
	{
		tm->tm_isdst = before_isdst;
		*tp = beforetime;
		return -(int) before_gmtoff;
	}
	if (beforetime > boundary && aftertime >= boundary)
	{
		tm->tm_isdst = after_isdst;
		*tp = aftertime;
		return -(int) after_gmtoff;
	}

	/*
	 * It's an invalid or ambiguous time due to timezone transition.  In a
	 * spring-forward transition, prefer the "before" interpretation; in a
	 * fall-back transition, prefer "after".  (We used to define and implement
	 * this test as "prefer the standard-time interpretation", but that rule
	 * does not help to resolve the behavior when both times are reported as
	 * standard time; which does happen, eg Europe/Moscow in Oct 2014.  Also,
	 * in some zones such as Europe/Dublin, there is widespread confusion
	 * about which time offset is "standard" time, so it's fortunate that our
	 * behavior doesn't depend on that.)
	 */
	if (beforetime > aftertime)
	{
		tm->tm_isdst = before_isdst;
		*tp = beforetime;
		return -(int) before_gmtoff;
	}
	tm->tm_isdst = after_isdst;
	*tp = aftertime;
	return -(int) after_gmtoff;

overflow:
	/* Given date is out of range, so assume UTC */
	tm->tm_isdst = 0;
	*tp = 0;
	return 0;
}