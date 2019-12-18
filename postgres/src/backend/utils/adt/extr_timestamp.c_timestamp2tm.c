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
struct pg_tm {int tm_isdst; int tm_gmtoff; char* tm_zone; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  int /*<<< orphan*/  pg_tz ;
typedef  scalar_t__ pg_time_t ;
typedef  scalar_t__ fsec_t ;
typedef  scalar_t__ Timestamp ;

/* Variables and functions */
 scalar_t__ INT64CONST (int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ POSTGRES_EPOCH_JDATE ; 
 scalar_t__ SECS_PER_DAY ; 
 int /*<<< orphan*/  TMODULO (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ UNIX_EPOCH_JDATE ; 
 scalar_t__ USECS_PER_DAY ; 
 scalar_t__ USECS_PER_SEC ; 
 int /*<<< orphan*/  dt2time (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  j2date (int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 struct pg_tm* pg_localtime (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * session_timezone ; 

int
timestamp2tm(Timestamp dt, int *tzp, struct pg_tm *tm, fsec_t *fsec, const char **tzn, pg_tz *attimezone)
{
	Timestamp	date;
	Timestamp	time;
	pg_time_t	utime;

	/* Use session timezone if caller asks for default */
	if (attimezone == NULL)
		attimezone = session_timezone;

	time = dt;
	TMODULO(time, date, USECS_PER_DAY);

	if (time < INT64CONST(0))
	{
		time += USECS_PER_DAY;
		date -= 1;
	}

	/* add offset to go from J2000 back to standard Julian date */
	date += POSTGRES_EPOCH_JDATE;

	/* Julian day routine does not work for negative Julian days */
	if (date < 0 || date > (Timestamp) INT_MAX)
		return -1;

	j2date((int) date, &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
	dt2time(time, &tm->tm_hour, &tm->tm_min, &tm->tm_sec, fsec);

	/* Done if no TZ conversion wanted */
	if (tzp == NULL)
	{
		tm->tm_isdst = -1;
		tm->tm_gmtoff = 0;
		tm->tm_zone = NULL;
		if (tzn != NULL)
			*tzn = NULL;
		return 0;
	}

	/*
	 * If the time falls within the range of pg_time_t, use pg_localtime() to
	 * rotate to the local time zone.
	 *
	 * First, convert to an integral timestamp, avoiding possibly
	 * platform-specific roundoff-in-wrong-direction errors, and adjust to
	 * Unix epoch.  Then see if we can convert to pg_time_t without loss. This
	 * coding avoids hardwiring any assumptions about the width of pg_time_t,
	 * so it should behave sanely on machines without int64.
	 */
	dt = (dt - *fsec) / USECS_PER_SEC +
		(POSTGRES_EPOCH_JDATE - UNIX_EPOCH_JDATE) * SECS_PER_DAY;
	utime = (pg_time_t) dt;
	if ((Timestamp) utime == dt)
	{
		struct pg_tm *tx = pg_localtime(&utime, attimezone);

		tm->tm_year = tx->tm_year + 1900;
		tm->tm_mon = tx->tm_mon + 1;
		tm->tm_mday = tx->tm_mday;
		tm->tm_hour = tx->tm_hour;
		tm->tm_min = tx->tm_min;
		tm->tm_sec = tx->tm_sec;
		tm->tm_isdst = tx->tm_isdst;
		tm->tm_gmtoff = tx->tm_gmtoff;
		tm->tm_zone = tx->tm_zone;
		*tzp = -tm->tm_gmtoff;
		if (tzn != NULL)
			*tzn = tm->tm_zone;
	}
	else
	{
		/*
		 * When out of range of pg_time_t, treat as GMT
		 */
		*tzp = 0;
		/* Mark this as *no* time zone available */
		tm->tm_isdst = -1;
		tm->tm_gmtoff = 0;
		tm->tm_zone = NULL;
		if (tzn != NULL)
			*tzn = NULL;
	}

	return 0;
}