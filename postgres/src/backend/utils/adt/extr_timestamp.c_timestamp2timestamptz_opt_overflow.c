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
struct pg_tm {int dummy; } ;
typedef  int /*<<< orphan*/  fsec_t ;
typedef  scalar_t__ TimestampTz ;
typedef  scalar_t__ Timestamp ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int DetermineTimeZoneOffset (struct pg_tm*,int /*<<< orphan*/ ) ; 
 scalar_t__ END_TIMESTAMP ; 
 int /*<<< orphan*/  ERRCODE_DATETIME_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IS_VALID_TIMESTAMP (scalar_t__) ; 
 scalar_t__ MIN_TIMESTAMP ; 
 scalar_t__ TIMESTAMP_NOT_FINITE (scalar_t__) ; 
 scalar_t__ dt2local (scalar_t__,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  session_timezone ; 
 int /*<<< orphan*/  timestamp2tm (scalar_t__,int /*<<< orphan*/ *,struct pg_tm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

TimestampTz
timestamp2timestamptz_opt_overflow(Timestamp timestamp, int *overflow)
{
	TimestampTz result;
	struct pg_tm tt,
			   *tm = &tt;
	fsec_t		fsec;
	int			tz;

	if (TIMESTAMP_NOT_FINITE(timestamp))
		return timestamp;

	if (!timestamp2tm(timestamp, NULL, tm, &fsec, NULL, NULL))
	{
		tz = DetermineTimeZoneOffset(tm, session_timezone);

		result = dt2local(timestamp, -tz);

		if (IS_VALID_TIMESTAMP(result))
		{
			return result;
		}
		else if (overflow)
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
	}

	ereport(ERROR,
			(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
			 errmsg("timestamp out of range")));

	return 0;
}