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
struct pg_tm {scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
typedef  int TimestampTz ;
typedef  int DateADT ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DATE_IS_NOBEGIN (int) ; 
 scalar_t__ DATE_IS_NOEND (int) ; 
 int DetermineTimeZoneOffset (struct pg_tm*,int /*<<< orphan*/ ) ; 
 int END_TIMESTAMP ; 
 int /*<<< orphan*/  ERRCODE_DATETIME_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IS_VALID_TIMESTAMP (int) ; 
 int MIN_TIMESTAMP ; 
 int POSTGRES_EPOCH_JDATE ; 
 int TIMESTAMP_END_JULIAN ; 
 int /*<<< orphan*/  TIMESTAMP_NOBEGIN (int) ; 
 int /*<<< orphan*/  TIMESTAMP_NOEND (int) ; 
 int USECS_PER_DAY ; 
 int USECS_PER_SEC ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  j2date (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_timezone ; 

TimestampTz
date2timestamptz_opt_overflow(DateADT dateVal, int *overflow)
{
	TimestampTz result;
	struct pg_tm tt,
			   *tm = &tt;
	int			tz;

	if (DATE_IS_NOBEGIN(dateVal))
		TIMESTAMP_NOBEGIN(result);
	else if (DATE_IS_NOEND(dateVal))
		TIMESTAMP_NOEND(result);
	else
	{
		/*
		 * Date's range is wider than timestamp's, so check for boundaries.
		 * Since dates have the same minimum values as timestamps, only upper
		 * boundary need be checked for overflow.
		 */
		if (dateVal >= (TIMESTAMP_END_JULIAN - POSTGRES_EPOCH_JDATE))
		{
			if (overflow)
			{
				*overflow = 1;
				return (TimestampTz) 0;
			}
			else
			{
				ereport(ERROR,
						(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
						 errmsg("date out of range for timestamp")));
			}
		}

		j2date(dateVal + POSTGRES_EPOCH_JDATE,
			   &(tm->tm_year), &(tm->tm_mon), &(tm->tm_mday));
		tm->tm_hour = 0;
		tm->tm_min = 0;
		tm->tm_sec = 0;
		tz = DetermineTimeZoneOffset(tm, session_timezone);

		result = dateVal * USECS_PER_DAY + tz * USECS_PER_SEC;

		/*
		 * Since it is possible to go beyond allowed timestamptz range because
		 * of time zone, check for allowed timestamp range after adding tz.
		 */
		if (!IS_VALID_TIMESTAMP(result))
		{
			if (overflow)
			{
				if (result < MIN_TIMESTAMP)
					*overflow = -1;
				else
				{
					Assert(result >= END_TIMESTAMP);
					*overflow = 1;
				}
				return (TimestampTz) 0;
			}
			else
			{
				ereport(ERROR,
						(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
						 errmsg("date out of range for timestamp")));
			}
		}
	}

	return result;
}