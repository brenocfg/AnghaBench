#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  text ;
struct pg_tm {int tm_hour; int tm_min; int tm_sec; int tm_year; int tm_mon; int tm_mday; char* tm_zone; } ;
typedef  scalar_t__ fsec_t ;
struct TYPE_7__ {int ssss; int ss; int mi; int hh; scalar_t__ clock; int year; int cc; int yysz; int j; int ww; scalar_t__ mode; int ddd; int w; int dd; int mm; int ms; scalar_t__ us; int ff; scalar_t__ tzsign; scalar_t__ tzh; int tzm; scalar_t__ bc; scalar_t__ d; scalar_t__ pm; } ;
typedef  TYPE_1__ TmFromChar ;
struct TYPE_8__ {char* format; } ;
typedef  char FormatNode ;
typedef  TYPE_2__ DCHCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERROR ; 
 scalar_t__ CLOCK_12_HOUR ; 
 int /*<<< orphan*/  DAY ; 
 int DCH_CACHE_SIZE ; 
 int DCH_FLAG ; 
 TYPE_2__* DCH_cache_fetch (char*,int) ; 
 int /*<<< orphan*/  DCH_datetime_type (char*,int*) ; 
 int /*<<< orphan*/  DCH_from_char (char*,char*,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  DCH_index ; 
 int /*<<< orphan*/  DCH_keywords ; 
 int /*<<< orphan*/  DCH_suff ; 
 int /*<<< orphan*/  DEBUG_TM (struct pg_tm*) ; 
 int /*<<< orphan*/  DEBUG_TMFC (TYPE_1__*) ; 
 int /*<<< orphan*/  DTERR_FIELD_OVERFLOW ; 
 int /*<<< orphan*/  DTERR_TZDISP_OVERFLOW ; 
 int DTK_DATE_M ; 
 int DTK_M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DateTimeParseError (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_DATETIME_FORMAT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FROM_CHAR_DATE_ISOWEEK ; 
 int HOURS_PER_DAY ; 
 scalar_t__ INT64CONST (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_TZDISP_HOUR ; 
 int MINS_PER_HOUR ; 
 int /*<<< orphan*/  MONTH ; 
 int MONTHS_PER_YEAR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int SECS_PER_HOUR ; 
 int SECS_PER_MINUTE ; 
 int STD_FLAG ; 
 scalar_t__ USECS_PER_SEC ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int ValidateDate (int,int,int,int,struct pg_tm*) ; 
 int /*<<< orphan*/  YEAR ; 
 int /*<<< orphan*/  ZERO_tm (struct pg_tm*) ; 
 int /*<<< orphan*/  ZERO_tmfc (TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 size_t isleap (int) ; 
 int /*<<< orphan*/  isoweek2date (int,int*,int*,int*) ; 
 int isoweek2j (int,int) ; 
 int /*<<< orphan*/  isoweekdate2date (int,scalar_t__,int*,int*,int*) ; 
 int /*<<< orphan*/  j2date (int,int*,int*,int*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  parse_format (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* psprintf (char*,char,scalar_t__,int) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_to_timestamp(text *date_txt, text *fmt, bool std,
				struct pg_tm *tm, fsec_t *fsec, int *fprec,
				uint32 *flags, bool *have_error)
{
	FormatNode *format = NULL;
	TmFromChar	tmfc;
	int			fmt_len;
	char	   *date_str;
	int			fmask;
	bool		incache = false;

	date_str = text_to_cstring(date_txt);

	ZERO_tmfc(&tmfc);
	ZERO_tm(tm);
	*fsec = 0;
	fmask = 0;					/* bit mask for ValidateDate() */

	fmt_len = VARSIZE_ANY_EXHDR(fmt);

	if (fmt_len)
	{
		char	   *fmt_str;

		fmt_str = text_to_cstring(fmt);

		if (fmt_len > DCH_CACHE_SIZE)
		{
			/*
			 * Allocate new memory if format picture is bigger than static
			 * cache and do not use cache (call parser always)
			 */
			format = (FormatNode *) palloc((fmt_len + 1) * sizeof(FormatNode));

			parse_format(format, fmt_str, DCH_keywords, DCH_suff, DCH_index,
						 DCH_FLAG | (std ? STD_FLAG : 0), NULL);
		}
		else
		{
			/*
			 * Use cache buffers
			 */
			DCHCacheEntry *ent = DCH_cache_fetch(fmt_str, std);

			incache = true;
			format = ent->format;
		}

#ifdef DEBUG_TO_FROM_CHAR
		/* dump_node(format, fmt_len); */
		/* dump_index(DCH_keywords, DCH_index); */
#endif

		DCH_from_char(format, date_str, &tmfc, std, have_error);
		CHECK_ERROR;

		pfree(fmt_str);

		if (flags)
			*flags = DCH_datetime_type(format, have_error);

		if (!incache)
		{
			pfree(format);
			format = NULL;
		}

		CHECK_ERROR;
	}

	DEBUG_TMFC(&tmfc);

	/*
	 * Convert to_date/to_timestamp input fields to standard 'tm'
	 */
	if (tmfc.ssss)
	{
		int			x = tmfc.ssss;

		tm->tm_hour = x / SECS_PER_HOUR;
		x %= SECS_PER_HOUR;
		tm->tm_min = x / SECS_PER_MINUTE;
		x %= SECS_PER_MINUTE;
		tm->tm_sec = x;
	}

	if (tmfc.ss)
		tm->tm_sec = tmfc.ss;
	if (tmfc.mi)
		tm->tm_min = tmfc.mi;
	if (tmfc.hh)
		tm->tm_hour = tmfc.hh;

	if (tmfc.clock == CLOCK_12_HOUR)
	{
		if (tm->tm_hour < 1 || tm->tm_hour > HOURS_PER_DAY / 2)
		{
			RETURN_ERROR(ereport(ERROR,
								 (errcode(ERRCODE_INVALID_DATETIME_FORMAT),
								  errmsg("hour \"%d\" is invalid for the 12-hour clock",
										 tm->tm_hour),
								  errhint("Use the 24-hour clock, or give an hour between 1 and 12."))));
		}

		if (tmfc.pm && tm->tm_hour < HOURS_PER_DAY / 2)
			tm->tm_hour += HOURS_PER_DAY / 2;
		else if (!tmfc.pm && tm->tm_hour == HOURS_PER_DAY / 2)
			tm->tm_hour = 0;
	}

	if (tmfc.year)
	{
		/*
		 * If CC and YY (or Y) are provided, use YY as 2 low-order digits for
		 * the year in the given century.  Keep in mind that the 21st century
		 * AD runs from 2001-2100, not 2000-2099; 6th century BC runs from
		 * 600BC to 501BC.
		 */
		if (tmfc.cc && tmfc.yysz <= 2)
		{
			if (tmfc.bc)
				tmfc.cc = -tmfc.cc;
			tm->tm_year = tmfc.year % 100;
			if (tm->tm_year)
			{
				if (tmfc.cc >= 0)
					tm->tm_year += (tmfc.cc - 1) * 100;
				else
					tm->tm_year = (tmfc.cc + 1) * 100 - tm->tm_year + 1;
			}
			else
			{
				/* find century year for dates ending in "00" */
				tm->tm_year = tmfc.cc * 100 + ((tmfc.cc >= 0) ? 0 : 1);
			}
		}
		else
		{
			/* If a 4-digit year is provided, we use that and ignore CC. */
			tm->tm_year = tmfc.year;
			if (tmfc.bc && tm->tm_year > 0)
				tm->tm_year = -(tm->tm_year - 1);
		}
		fmask |= DTK_M(YEAR);
	}
	else if (tmfc.cc)
	{
		/* use first year of century */
		if (tmfc.bc)
			tmfc.cc = -tmfc.cc;
		if (tmfc.cc >= 0)
			/* +1 because 21st century started in 2001 */
			tm->tm_year = (tmfc.cc - 1) * 100 + 1;
		else
			/* +1 because year == 599 is 600 BC */
			tm->tm_year = tmfc.cc * 100 + 1;
		fmask |= DTK_M(YEAR);
	}

	if (tmfc.j)
	{
		j2date(tmfc.j, &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
		fmask |= DTK_DATE_M;
	}

	if (tmfc.ww)
	{
		if (tmfc.mode == FROM_CHAR_DATE_ISOWEEK)
		{
			/*
			 * If tmfc.d is not set, then the date is left at the beginning of
			 * the ISO week (Monday).
			 */
			if (tmfc.d)
				isoweekdate2date(tmfc.ww, tmfc.d, &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
			else
				isoweek2date(tmfc.ww, &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
			fmask |= DTK_DATE_M;
		}
		else
			tmfc.ddd = (tmfc.ww - 1) * 7 + 1;
	}

	if (tmfc.w)
		tmfc.dd = (tmfc.w - 1) * 7 + 1;
	if (tmfc.dd)
	{
		tm->tm_mday = tmfc.dd;
		fmask |= DTK_M(DAY);
	}
	if (tmfc.mm)
	{
		tm->tm_mon = tmfc.mm;
		fmask |= DTK_M(MONTH);
	}

	if (tmfc.ddd && (tm->tm_mon <= 1 || tm->tm_mday <= 1))
	{
		/*
		 * The month and day field have not been set, so we use the
		 * day-of-year field to populate them.  Depending on the date mode,
		 * this field may be interpreted as a Gregorian day-of-year, or an ISO
		 * week date day-of-year.
		 */

		if (!tm->tm_year && !tmfc.bc)
		{
			RETURN_ERROR(ereport(ERROR,
								 (errcode(ERRCODE_INVALID_DATETIME_FORMAT),
								  errmsg("cannot calculate day of year without year information"))));
		}

		if (tmfc.mode == FROM_CHAR_DATE_ISOWEEK)
		{
			int			j0;		/* zeroth day of the ISO year, in Julian */

			j0 = isoweek2j(tm->tm_year, 1) - 1;

			j2date(j0 + tmfc.ddd, &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
			fmask |= DTK_DATE_M;
		}
		else
		{
			const int  *y;
			int			i;

			static const int ysum[2][13] = {
				{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
			{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}};

			y = ysum[isleap(tm->tm_year)];

			for (i = 1; i <= MONTHS_PER_YEAR; i++)
			{
				if (tmfc.ddd <= y[i])
					break;
			}
			if (tm->tm_mon <= 1)
				tm->tm_mon = i;

			if (tm->tm_mday <= 1)
				tm->tm_mday = tmfc.ddd - y[i - 1];

			fmask |= DTK_M(MONTH) | DTK_M(DAY);
		}
	}

	if (tmfc.ms)
		*fsec += tmfc.ms * 1000;
	if (tmfc.us)
		*fsec += tmfc.us;
	if (fprec)
		*fprec = tmfc.ff;		/* fractional precision, if specified */

	/* Range-check date fields according to bit mask computed above */
	if (fmask != 0)
	{
		/* We already dealt with AD/BC, so pass isjulian = true */
		int			dterr = ValidateDate(fmask, true, false, false, tm);

		if (dterr != 0)
		{
			/*
			 * Force the error to be DTERR_FIELD_OVERFLOW even if ValidateDate
			 * said DTERR_MD_FIELD_OVERFLOW, because we don't want to print an
			 * irrelevant hint about datestyle.
			 */
			RETURN_ERROR(DateTimeParseError(DTERR_FIELD_OVERFLOW, date_str, "timestamp"));
		}
	}

	/* Range-check time fields too */
	if (tm->tm_hour < 0 || tm->tm_hour >= HOURS_PER_DAY ||
		tm->tm_min < 0 || tm->tm_min >= MINS_PER_HOUR ||
		tm->tm_sec < 0 || tm->tm_sec >= SECS_PER_MINUTE ||
		*fsec < INT64CONST(0) || *fsec >= USECS_PER_SEC)
	{
		RETURN_ERROR(DateTimeParseError(DTERR_FIELD_OVERFLOW, date_str, "timestamp"));
	}

	/* Save parsed time-zone into tm->tm_zone if it was specified */
	if (tmfc.tzsign)
	{
		char	   *tz;

		if (tmfc.tzh < 0 || tmfc.tzh > MAX_TZDISP_HOUR ||
			tmfc.tzm < 0 || tmfc.tzm >= MINS_PER_HOUR)
		{
			RETURN_ERROR(DateTimeParseError(DTERR_TZDISP_OVERFLOW, date_str, "timestamp"));
		}

		tz = psprintf("%c%02d:%02d",
					  tmfc.tzsign > 0 ? '+' : '-', tmfc.tzh, tmfc.tzm);

		tm->tm_zone = tz;
	}

	DEBUG_TM(tm);

on_error:

	if (format && !incache)
		pfree(format);

	pfree(date_str);
}