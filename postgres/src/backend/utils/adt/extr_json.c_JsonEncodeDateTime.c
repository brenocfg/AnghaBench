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
struct pg_tm {int tm_isdst; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
typedef  int /*<<< orphan*/  fsec_t ;
typedef  int TimestampTz ;
typedef  int Timestamp ;
typedef  int /*<<< orphan*/  TimeTzADT ;
typedef  int /*<<< orphan*/  TimeADT ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ DateADT ;

/* Variables and functions */
#define  DATEOID 132 
 int /*<<< orphan*/  DATE_NOT_FINITE (scalar_t__) ; 
 scalar_t__ DatumGetDateADT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetTimeADT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetTimeTzADTP (int /*<<< orphan*/ ) ; 
 int DatumGetTimestamp (int /*<<< orphan*/ ) ; 
 int DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATETIME_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EncodeDateOnly (struct pg_tm*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EncodeDateTime (struct pg_tm*,int /*<<< orphan*/ ,int,int,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EncodeSpecialDate (scalar_t__,char*) ; 
 int /*<<< orphan*/  EncodeSpecialTimestamp (int,char*) ; 
 int /*<<< orphan*/  EncodeTimeOnly (struct pg_tm*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MAXDATELEN ; 
 scalar_t__ POSTGRES_EPOCH_JDATE ; 
#define  TIMEOID 131 
#define  TIMESTAMPOID 130 
#define  TIMESTAMPTZOID 129 
 int /*<<< orphan*/  TIMESTAMP_NOT_FINITE (int) ; 
#define  TIMETZOID 128 
 int USECS_PER_SEC ; 
 int /*<<< orphan*/  USE_XSD_DATES ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  j2date (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* palloc (scalar_t__) ; 
 int /*<<< orphan*/  time2tm (int /*<<< orphan*/ ,struct pg_tm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timestamp2tm (int,int*,struct pg_tm*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timetz2tm (int /*<<< orphan*/ *,struct pg_tm*,int /*<<< orphan*/ *,int*) ; 

char *
JsonEncodeDateTime(char *buf, Datum value, Oid typid, const int *tzp)
{
	if (!buf)
		buf = palloc(MAXDATELEN + 1);

	switch (typid)
	{
		case DATEOID:
			{
				DateADT		date;
				struct pg_tm tm;

				date = DatumGetDateADT(value);

				/* Same as date_out(), but forcing DateStyle */
				if (DATE_NOT_FINITE(date))
					EncodeSpecialDate(date, buf);
				else
				{
					j2date(date + POSTGRES_EPOCH_JDATE,
						   &(tm.tm_year), &(tm.tm_mon), &(tm.tm_mday));
					EncodeDateOnly(&tm, USE_XSD_DATES, buf);
				}
			}
			break;
		case TIMEOID:
			{
				TimeADT		time = DatumGetTimeADT(value);
				struct pg_tm tt,
						   *tm = &tt;
				fsec_t		fsec;

				/* Same as time_out(), but forcing DateStyle */
				time2tm(time, tm, &fsec);
				EncodeTimeOnly(tm, fsec, false, 0, USE_XSD_DATES, buf);
			}
			break;
		case TIMETZOID:
			{
				TimeTzADT  *time = DatumGetTimeTzADTP(value);
				struct pg_tm tt,
						   *tm = &tt;
				fsec_t		fsec;
				int			tz;

				/* Same as timetz_out(), but forcing DateStyle */
				timetz2tm(time, tm, &fsec, &tz);
				EncodeTimeOnly(tm, fsec, true, tz, USE_XSD_DATES, buf);
			}
			break;
		case TIMESTAMPOID:
			{
				Timestamp	timestamp;
				struct pg_tm tm;
				fsec_t		fsec;

				timestamp = DatumGetTimestamp(value);
				/* Same as timestamp_out(), but forcing DateStyle */
				if (TIMESTAMP_NOT_FINITE(timestamp))
					EncodeSpecialTimestamp(timestamp, buf);
				else if (timestamp2tm(timestamp, NULL, &tm, &fsec, NULL, NULL) == 0)
					EncodeDateTime(&tm, fsec, false, 0, NULL, USE_XSD_DATES, buf);
				else
					ereport(ERROR,
							(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
							 errmsg("timestamp out of range")));
			}
			break;
		case TIMESTAMPTZOID:
			{
				TimestampTz timestamp;
				struct pg_tm tm;
				int			tz;
				fsec_t		fsec;
				const char *tzn = NULL;

				timestamp = DatumGetTimestampTz(value);

				/*
				 * If a time zone is specified, we apply the time-zone shift,
				 * convert timestamptz to pg_tm as if it were without a time
				 * zone, and then use the specified time zone for converting
				 * the timestamp into a string.
				 */
				if (tzp)
				{
					tz = *tzp;
					timestamp -= (TimestampTz) tz * USECS_PER_SEC;
				}

				/* Same as timestamptz_out(), but forcing DateStyle */
				if (TIMESTAMP_NOT_FINITE(timestamp))
					EncodeSpecialTimestamp(timestamp, buf);
				else if (timestamp2tm(timestamp, tzp ? NULL : &tz, &tm, &fsec,
									  tzp ? NULL : &tzn, NULL) == 0)
				{
					if (tzp)
						tm.tm_isdst = 1;	/* set time-zone presence flag */

					EncodeDateTime(&tm, fsec, true, tz, tzn, USE_XSD_DATES, buf);
				}
				else
					ereport(ERROR,
							(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
							 errmsg("timestamp out of range")));
			}
			break;
		default:
			elog(ERROR, "unknown jsonb value datetime type oid %d", typid);
			return NULL;
	}

	return buf;
}