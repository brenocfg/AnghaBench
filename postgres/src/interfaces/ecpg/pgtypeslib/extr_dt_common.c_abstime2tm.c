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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_isdst; int tm_gmtoff; int /*<<< orphan*/  tm_zone; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  int /*<<< orphan*/  AbsoluteTime ;

/* Variables and functions */
 scalar_t__ MAXTZLEN ; 
 scalar_t__ PGTYPES_TS_BAD_TIMESTAMP ; 
 int SECS_PER_HOUR ; 
 int /*<<< orphan*/  StrNCpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int TIMEZONE_GLOBAL ; 
 int /*<<< orphan*/ * TZNAME_GLOBAL ; 
 scalar_t__ errno ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
abstime2tm(AbsoluteTime _time, int *tzp, struct tm *tm, char **tzn)
{
	time_t		time = (time_t) _time;
	struct tm  *tx;

	errno = 0;
	if (tzp != NULL)
		tx = localtime((time_t *) &time);
	else
		tx = gmtime((time_t *) &time);

	if (!tx)
	{
		errno = PGTYPES_TS_BAD_TIMESTAMP;
		return;
	}

	tm->tm_year = tx->tm_year + 1900;
	tm->tm_mon = tx->tm_mon + 1;
	tm->tm_mday = tx->tm_mday;
	tm->tm_hour = tx->tm_hour;
	tm->tm_min = tx->tm_min;
	tm->tm_sec = tx->tm_sec;
	tm->tm_isdst = tx->tm_isdst;

#if defined(HAVE_STRUCT_TM_TM_ZONE)
	tm->tm_gmtoff = tx->tm_gmtoff;
	tm->tm_zone = tx->tm_zone;

	if (tzp != NULL)
	{
		/*
		 * We have a brute force time zone per SQL99? Then use it without
		 * change since we have already rotated to the time zone.
		 */
		*tzp = -tm->tm_gmtoff;	/* tm_gmtoff is Sun/DEC-ism */

		/*
		 * FreeBSD man pages indicate that this should work - tgl 97/04/23
		 */
		if (tzn != NULL)
		{
			/*
			 * Copy no more than MAXTZLEN bytes of timezone to tzn, in case it
			 * contains an error message, which doesn't fit in the buffer
			 */
			StrNCpy(*tzn, tm->tm_zone, MAXTZLEN + 1);
			if (strlen(tm->tm_zone) > MAXTZLEN)
				tm->tm_isdst = -1;
		}
	}
	else
		tm->tm_isdst = -1;
#elif defined(HAVE_INT_TIMEZONE)
	if (tzp != NULL)
	{
		*tzp = (tm->tm_isdst > 0) ? TIMEZONE_GLOBAL - SECS_PER_HOUR : TIMEZONE_GLOBAL;

		if (tzn != NULL)
		{
			/*
			 * Copy no more than MAXTZLEN bytes of timezone to tzn, in case it
			 * contains an error message, which doesn't fit in the buffer
			 */
			StrNCpy(*tzn, TZNAME_GLOBAL[tm->tm_isdst], MAXTZLEN + 1);
			if (strlen(TZNAME_GLOBAL[tm->tm_isdst]) > MAXTZLEN)
				tm->tm_isdst = -1;
		}
	}
	else
		tm->tm_isdst = -1;
#else							/* not (HAVE_STRUCT_TM_TM_ZONE || HAVE_INT_TIMEZONE) */
	if (tzp != NULL)
	{
		/* default to UTC */
		*tzp = 0;
		if (tzn != NULL)
			*tzn = NULL;
	}
	else
		tm->tm_isdst = -1;
#endif
}