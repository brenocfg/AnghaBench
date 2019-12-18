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
struct pg_tm {int tm_year; int tm_mon; int tm_mday; } ;
typedef  scalar_t__ Timestamp ;
typedef  scalar_t__ TimeOffset ;

/* Variables and functions */
 int /*<<< orphan*/  DTK_DATE_M ; 
 int /*<<< orphan*/  ERRCODE_DATETIME_FIELD_OVERFLOW ; 
 int /*<<< orphan*/  ERRCODE_DATETIME_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int HOURS_PER_DAY ; 
 int /*<<< orphan*/  IS_VALID_JULIAN (int,int,int) ; 
 int /*<<< orphan*/  IS_VALID_TIMESTAMP (scalar_t__) ; 
 int MINS_PER_HOUR ; 
 scalar_t__ POSTGRES_EPOCH_JDATE ; 
 double SECS_PER_MINUTE ; 
 scalar_t__ USECS_PER_DAY ; 
 int USECS_PER_SEC ; 
 int ValidateDate (int /*<<< orphan*/ ,int,int,int,struct pg_tm*) ; 
 scalar_t__ date2j (int,int,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int,int,int,...) ; 
 scalar_t__ isnan (double) ; 
 scalar_t__ rint (double) ; 

__attribute__((used)) static Timestamp
make_timestamp_internal(int year, int month, int day,
						int hour, int min, double sec)
{
	struct pg_tm tm;
	TimeOffset	date;
	TimeOffset	time;
	int			dterr;
	Timestamp	result;

	tm.tm_year = year;
	tm.tm_mon = month;
	tm.tm_mday = day;

	/*
	 * Note: we'll reject zero or negative year values.  Perhaps negatives
	 * should be allowed to represent BC years?
	 */
	dterr = ValidateDate(DTK_DATE_M, false, false, false, &tm);

	if (dterr != 0)
		ereport(ERROR,
				(errcode(ERRCODE_DATETIME_FIELD_OVERFLOW),
				 errmsg("date field value out of range: %d-%02d-%02d",
						year, month, day)));

	if (!IS_VALID_JULIAN(tm.tm_year, tm.tm_mon, tm.tm_mday))
		ereport(ERROR,
				(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
				 errmsg("date out of range: %d-%02d-%02d",
						year, month, day)));

	date = date2j(tm.tm_year, tm.tm_mon, tm.tm_mday) - POSTGRES_EPOCH_JDATE;

	/*
	 * This should match the checks in DecodeTimeOnly, except that since we're
	 * dealing with a float "sec" value, we also explicitly reject NaN.  (An
	 * infinity input should get rejected by the range comparisons, but we
	 * can't be sure how those will treat a NaN.)
	 */
	if (hour < 0 || min < 0 || min > MINS_PER_HOUR - 1 ||
		isnan(sec) ||
		sec < 0 || sec > SECS_PER_MINUTE ||
		hour > HOURS_PER_DAY ||
	/* test for > 24:00:00 */
		(hour == HOURS_PER_DAY && (min > 0 || sec > 0)))
		ereport(ERROR,
				(errcode(ERRCODE_DATETIME_FIELD_OVERFLOW),
				 errmsg("time field value out of range: %d:%02d:%02g",
						hour, min, sec)));

	/* This should match tm2time */
	time = (((hour * MINS_PER_HOUR + min) * SECS_PER_MINUTE)
			* USECS_PER_SEC) + rint(sec * USECS_PER_SEC);

	result = date * USECS_PER_DAY + time;
	/* check for major overflow */
	if ((result - time) / USECS_PER_DAY != date)
		ereport(ERROR,
				(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
				 errmsg("timestamp out of range: %d-%02d-%02d %d:%02d:%02g",
						year, month, day,
						hour, min, sec)));

	/* check for just-barely overflow (okay except time-of-day wraps) */
	/* caution: we want to allow 1999-12-31 24:00:00 */
	if ((result < 0 && date > 0) ||
		(result > 0 && date < -1))
		ereport(ERROR,
				(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
				 errmsg("timestamp out of range: %d-%02d-%02d %d:%02d:%02g",
						year, month, day,
						hour, min, sec)));

	/* final range check catches just-out-of-range timestamps */
	if (!IS_VALID_TIMESTAMP(result))
		ereport(ERROR,
				(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
				 errmsg("timestamp out of range: %d-%02d-%02d %d:%02d:%02g",
						year, month, day,
						hour, min, sec)));

	return result;
}