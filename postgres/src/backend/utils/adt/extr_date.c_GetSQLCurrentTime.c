#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pg_tm {int dummy; } ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  fsec_t ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_4__ {int /*<<< orphan*/  time; } ;
typedef  TYPE_1__ TimeTzADT ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustTimeForTypmod (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATETIME_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentTransactionStartTimestamp () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ timestamp2tm (int /*<<< orphan*/ ,int*,struct pg_tm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tm2timetz (struct pg_tm*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 

TimeTzADT *
GetSQLCurrentTime(int32 typmod)
{
	TimeTzADT  *result;
	TimestampTz ts;
	struct pg_tm tt,
			   *tm = &tt;
	fsec_t		fsec;
	int			tz;

	ts = GetCurrentTransactionStartTimestamp();

	if (timestamp2tm(ts, &tz, tm, &fsec, NULL, NULL) != 0)
		ereport(ERROR,
				(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
				 errmsg("timestamp out of range")));

	result = (TimeTzADT *) palloc(sizeof(TimeTzADT));
	tm2timetz(tm, fsec, tz, result);
	AdjustTimeForTypmod(&(result->time), typmod);
	return result;
}