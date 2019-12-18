#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double zone; int /*<<< orphan*/  time; } ;
typedef  TYPE_1__ TimeTzADT ;
struct TYPE_6__ {double day; double month; int /*<<< orphan*/  time; } ;
typedef  int Oid ;
typedef  TYPE_2__ Interval ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
#define  DATEOID 133 
 double DAYS_PER_YEAR ; 
 int /*<<< orphan*/  DatumGetDateADT (int /*<<< orphan*/ ) ; 
 TYPE_2__* DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 double DatumGetTimeADT (int /*<<< orphan*/ ) ; 
 TYPE_1__* DatumGetTimeTzADTP (int /*<<< orphan*/ ) ; 
 double DatumGetTimestamp (int /*<<< orphan*/ ) ; 
 double DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
#define  INTERVALOID 132 
 scalar_t__ MONTHS_PER_YEAR ; 
#define  TIMEOID 131 
#define  TIMESTAMPOID 130 
#define  TIMESTAMPTZOID 129 
#define  TIMETZOID 128 
 double USECS_PER_DAY ; 
 double date2timestamp_no_overflow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double
convert_timevalue_to_scalar(Datum value, Oid typid, bool *failure)
{
	switch (typid)
	{
		case TIMESTAMPOID:
			return DatumGetTimestamp(value);
		case TIMESTAMPTZOID:
			return DatumGetTimestampTz(value);
		case DATEOID:
			return date2timestamp_no_overflow(DatumGetDateADT(value));
		case INTERVALOID:
			{
				Interval   *interval = DatumGetIntervalP(value);

				/*
				 * Convert the month part of Interval to days using assumed
				 * average month length of 365.25/12.0 days.  Not too
				 * accurate, but plenty good enough for our purposes.
				 */
				return interval->time + interval->day * (double) USECS_PER_DAY +
					interval->month * ((DAYS_PER_YEAR / (double) MONTHS_PER_YEAR) * USECS_PER_DAY);
			}
		case TIMEOID:
			return DatumGetTimeADT(value);
		case TIMETZOID:
			{
				TimeTzADT  *timetz = DatumGetTimeTzADTP(value);

				/* use GMT-equivalent time */
				return (double) (timetz->time + (timetz->zone * 1000000.0));
			}
	}

	*failure = true;
	return 0;
}