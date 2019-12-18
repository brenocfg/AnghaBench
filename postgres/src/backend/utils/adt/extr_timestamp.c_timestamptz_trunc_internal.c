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
typedef  int /*<<< orphan*/  text ;
struct pg_tm {int tm_year; int tm_mon; int tm_mday; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;
typedef  int /*<<< orphan*/  pg_tz ;
typedef  int fsec_t ;
typedef  scalar_t__ TimestampTz ;

/* Variables and functions */
#define  DTK_CENTURY 140 
#define  DTK_DAY 139 
#define  DTK_DECADE 138 
#define  DTK_HOUR 137 
#define  DTK_MICROSEC 136 
#define  DTK_MILLENNIUM 135 
#define  DTK_MILLISEC 134 
#define  DTK_MINUTE 133 
#define  DTK_MONTH 132 
#define  DTK_QUARTER 131 
#define  DTK_SECOND 130 
#define  DTK_WEEK 129 
#define  DTK_YEAR 128 
 int DecodeUnits (int /*<<< orphan*/ ,char*,int*) ; 
 int DetermineTimeZoneOffset (struct pg_tm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_DATETIME_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int MONTHS_PER_YEAR ; 
 int UNITS ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int date2isoweek (int,int,int) ; 
 char* downcase_truncate_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  isoweek2date (int,int*,int*,int*) ; 
 scalar_t__ timestamp2tm (scalar_t__,int*,struct pg_tm*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tm2timestamp (struct pg_tm*,int,int*,scalar_t__*) ; 

__attribute__((used)) static TimestampTz
timestamptz_trunc_internal(text *units, TimestampTz timestamp, pg_tz *tzp)
{
	TimestampTz result;
	int			tz;
	int			type,
				val;
	bool		redotz = false;
	char	   *lowunits;
	fsec_t		fsec;
	struct pg_tm tt,
			   *tm = &tt;

	lowunits = downcase_truncate_identifier(VARDATA_ANY(units),
											VARSIZE_ANY_EXHDR(units),
											false);

	type = DecodeUnits(0, lowunits, &val);

	if (type == UNITS)
	{
		if (timestamp2tm(timestamp, &tz, tm, &fsec, NULL, tzp) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
					 errmsg("timestamp out of range")));

		switch (val)
		{
			case DTK_WEEK:
				{
					int			woy;

					woy = date2isoweek(tm->tm_year, tm->tm_mon, tm->tm_mday);

					/*
					 * If it is week 52/53 and the month is January, then the
					 * week must belong to the previous year. Also, some
					 * December dates belong to the next year.
					 */
					if (woy >= 52 && tm->tm_mon == 1)
						--tm->tm_year;
					if (woy <= 1 && tm->tm_mon == MONTHS_PER_YEAR)
						++tm->tm_year;
					isoweek2date(woy, &(tm->tm_year), &(tm->tm_mon), &(tm->tm_mday));
					tm->tm_hour = 0;
					tm->tm_min = 0;
					tm->tm_sec = 0;
					fsec = 0;
					redotz = true;
					break;
				}
				/* one may consider DTK_THOUSAND and DTK_HUNDRED... */
			case DTK_MILLENNIUM:

				/*
				 * truncating to the millennium? what is this supposed to
				 * mean? let us put the first year of the millennium... i.e.
				 * -1000, 1, 1001, 2001...
				 */
				if (tm->tm_year > 0)
					tm->tm_year = ((tm->tm_year + 999) / 1000) * 1000 - 999;
				else
					tm->tm_year = -((999 - (tm->tm_year - 1)) / 1000) * 1000 + 1;
				/* FALL THRU */
			case DTK_CENTURY:
				/* truncating to the century? as above: -100, 1, 101... */
				if (tm->tm_year > 0)
					tm->tm_year = ((tm->tm_year + 99) / 100) * 100 - 99;
				else
					tm->tm_year = -((99 - (tm->tm_year - 1)) / 100) * 100 + 1;
				/* FALL THRU */
			case DTK_DECADE:

				/*
				 * truncating to the decade? first year of the decade. must
				 * not be applied if year was truncated before!
				 */
				if (val != DTK_MILLENNIUM && val != DTK_CENTURY)
				{
					if (tm->tm_year > 0)
						tm->tm_year = (tm->tm_year / 10) * 10;
					else
						tm->tm_year = -((8 - (tm->tm_year - 1)) / 10) * 10;
				}
				/* FALL THRU */
			case DTK_YEAR:
				tm->tm_mon = 1;
				/* FALL THRU */
			case DTK_QUARTER:
				tm->tm_mon = (3 * ((tm->tm_mon - 1) / 3)) + 1;
				/* FALL THRU */
			case DTK_MONTH:
				tm->tm_mday = 1;
				/* FALL THRU */
			case DTK_DAY:
				tm->tm_hour = 0;
				redotz = true;	/* for all cases >= DAY */
				/* FALL THRU */
			case DTK_HOUR:
				tm->tm_min = 0;
				/* FALL THRU */
			case DTK_MINUTE:
				tm->tm_sec = 0;
				/* FALL THRU */
			case DTK_SECOND:
				fsec = 0;
				break;
			case DTK_MILLISEC:
				fsec = (fsec / 1000) * 1000;
				break;
			case DTK_MICROSEC:
				break;

			default:
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("timestamp with time zone units \"%s\" not "
								"supported", lowunits)));
				result = 0;
		}

		if (redotz)
			tz = DetermineTimeZoneOffset(tm, tzp);

		if (tm2timestamp(tm, fsec, &tz, &result) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
					 errmsg("timestamp out of range")));
	}
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("timestamp with time zone units \"%s\" not recognized",
						lowunits)));
		result = 0;
	}

	return result;
}