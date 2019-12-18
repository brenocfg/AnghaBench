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
struct tm {int tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; int tm_isdst; int tm_year; int tm_mon; int tm_mday; int tm_wday; } ;
typedef  double fsec_t ;

/* Variables and functions */
#define  ADBC 156 
 int AM ; 
#define  AMPM 155 
 int BC ; 
 int const DAY ; 
#define  DOW 154 
#define  DTK_DATE 153 
 int DTK_DATE_M ; 
#define  DTK_DAY 152 
#define  DTK_HOUR 151 
#define  DTK_JULIAN 150 
 int DTK_M (int const) ; 
#define  DTK_MINUTE 149 
#define  DTK_MONTH 148 
#define  DTK_NOW 147 
#define  DTK_NUMBER 146 
#define  DTK_SECOND 145 
#define  DTK_SPECIAL 144 
#define  DTK_STRING 143 
#define  DTK_TIME 142 
 int DTK_TIME_M ; 
#define  DTK_TODAY 141 
#define  DTK_TOMORROW 140 
#define  DTK_TZ 139 
#define  DTK_YEAR 138 
#define  DTK_YESTERDAY 137 
#define  DTK_ZULU 136 
#define  DTZ 135 
#define  DTZMOD 134 
 int /*<<< orphan*/  DecodeDate (char*,int,int*,struct tm*,int) ; 
 int /*<<< orphan*/  DecodeNumber (int,char*,int,int*,struct tm*,double*,int*,int) ; 
 int DecodeNumberField (int,char*,int,int*,struct tm*,double*,int*) ; 
 int /*<<< orphan*/  DecodePosixTimezone (char*,int*) ; 
 int DecodeSpecial (int,char*,int*) ; 
 int /*<<< orphan*/  DecodeTime (char*,int*,struct tm*,double*) ; 
 int /*<<< orphan*/  DecodeTimezone (char*,int*) ; 
 int /*<<< orphan*/  GetCurrentDateTime (struct tm*) ; 
 int const HOUR ; 
 int HR24 ; 
#define  IGNORE_DTF 133 
#define  ISOTIME 132 
 int const MINUTE ; 
#define  MONTH 131 
 int PM ; 
#define  RESERV 130 
 int const SECOND ; 
#define  TZ 129 
#define  UNITS 128 
 double USECS_PER_DAY ; 
 int const YEAR ; 
 int /*<<< orphan*/  date2j (int,int,int) ; 
 int** day_tab ; 
 int /*<<< orphan*/  dt2time (double,int*,int*,int*,double*) ; 
 int /*<<< orphan*/  isalpha (unsigned char) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 size_t isleap (int) ; 
 int /*<<< orphan*/  j2date (int,int*,int*,int*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 double strtod (char*,char**) ; 
 int strtoint (char*,char**,int) ; 

int
DecodeDateTime(char **field, int *ftype, int nf,
			   int *dtype, struct tm *tm, fsec_t *fsec, bool EuroDates)
{
	int			fmask = 0,
				tmask,
				type;
	int			ptype = 0;		/* "prefix type" for ISO y2001m02d04 format */
	int			i;
	int			val;
	int			mer = HR24;
	bool		haveTextMonth = false;
	bool		is2digits = false;
	bool		bc = false;
	int			t = 0;
	int		   *tzp = &t;

	/***
	 * We'll insist on at least all of the date fields, but initialize the
	 * remaining fields in case they are not set later...
	 ***/
	*dtype = DTK_DATE;
	tm->tm_hour = 0;
	tm->tm_min = 0;
	tm->tm_sec = 0;
	*fsec = 0;
	/* don't know daylight savings time status apriori */
	tm->tm_isdst = -1;
	if (tzp != NULL)
		*tzp = 0;

	for (i = 0; i < nf; i++)
	{
		switch (ftype[i])
		{
			case DTK_DATE:
				/***
				 * Integral julian day with attached time zone?
				 * All other forms with JD will be separated into
				 * distinct fields, so we handle just this case here.
				 ***/
				if (ptype == DTK_JULIAN)
				{
					char	   *cp;
					int			val;

					if (tzp == NULL)
						return -1;

					val = strtoint(field[i], &cp, 10);
					if (*cp != '-')
						return -1;

					j2date(val, &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
					/* Get the time zone from the end of the string */
					if (DecodeTimezone(cp, tzp) != 0)
						return -1;

					tmask = DTK_DATE_M | DTK_TIME_M | DTK_M(TZ);
					ptype = 0;
					break;
				}
				/***
				 * Already have a date? Then this might be a POSIX time
				 * zone with an embedded dash (e.g. "PST-3" == "EST") or
				 * a run-together time with trailing time zone (e.g. hhmmss-zz).
				 * - thomas 2001-12-25
				 ***/
				else if (((fmask & DTK_DATE_M) == DTK_DATE_M)
						 || (ptype != 0))
				{
					/* No time zone accepted? Then quit... */
					if (tzp == NULL)
						return -1;

					if (isdigit((unsigned char) *field[i]) || ptype != 0)
					{
						char	   *cp;

						if (ptype != 0)
						{
							/* Sanity check; should not fail this test */
							if (ptype != DTK_TIME)
								return -1;
							ptype = 0;
						}

						/*
						 * Starts with a digit but we already have a time
						 * field? Then we are in trouble with a date and time
						 * already...
						 */
						if ((fmask & DTK_TIME_M) == DTK_TIME_M)
							return -1;

						if ((cp = strchr(field[i], '-')) == NULL)
							return -1;

						/* Get the time zone from the end of the string */
						if (DecodeTimezone(cp, tzp) != 0)
							return -1;
						*cp = '\0';

						/*
						 * Then read the rest of the field as a concatenated
						 * time
						 */
						if ((ftype[i] = DecodeNumberField(strlen(field[i]), field[i], fmask,
														  &tmask, tm, fsec, &is2digits)) < 0)
							return -1;

						/*
						 * modify tmask after returning from
						 * DecodeNumberField()
						 */
						tmask |= DTK_M(TZ);
					}
					else
					{
						if (DecodePosixTimezone(field[i], tzp) != 0)
							return -1;

						ftype[i] = DTK_TZ;
						tmask = DTK_M(TZ);
					}
				}
				else if (DecodeDate(field[i], fmask, &tmask, tm, EuroDates) != 0)
					return -1;
				break;

			case DTK_TIME:
				if (DecodeTime(field[i], &tmask, tm, fsec) != 0)
					return -1;

				/*
				 * Check upper limit on hours; other limits checked in
				 * DecodeTime()
				 */
				/* test for > 24:00:00 */
				if (tm->tm_hour > 24 ||
					(tm->tm_hour == 24 && (tm->tm_min > 0 || tm->tm_sec > 0)))
					return -1;
				break;

			case DTK_TZ:
				{
					int			tz;

					if (tzp == NULL)
						return -1;

					if (DecodeTimezone(field[i], &tz) != 0)
						return -1;

					/*
					 * Already have a time zone? Then maybe this is the second
					 * field of a POSIX time: EST+3 (equivalent to PST)
					 */
					if (i > 0 && (fmask & DTK_M(TZ)) != 0 &&
						ftype[i - 1] == DTK_TZ &&
						isalpha((unsigned char) *field[i - 1]))
					{
						*tzp -= tz;
						tmask = 0;
					}
					else
					{
						*tzp = tz;
						tmask = DTK_M(TZ);
					}
				}
				break;

			case DTK_NUMBER:

				/*
				 * Was this an "ISO date" with embedded field labels? An
				 * example is "y2001m02d04" - thomas 2001-02-04
				 */
				if (ptype != 0)
				{
					char	   *cp;
					int			val;

					val = strtoint(field[i], &cp, 10);

					/*
					 * only a few kinds are allowed to have an embedded
					 * decimal
					 */
					if (*cp == '.')
						switch (ptype)
						{
							case DTK_JULIAN:
							case DTK_TIME:
							case DTK_SECOND:
								break;
							default:
								return 1;
								break;
						}
					else if (*cp != '\0')
						return -1;

					switch (ptype)
					{
						case DTK_YEAR:
							tm->tm_year = val;
							tmask = DTK_M(YEAR);
							break;

						case DTK_MONTH:

							/*
							 * already have a month and hour? then assume
							 * minutes
							 */
							if ((fmask & DTK_M(MONTH)) != 0 &&
								(fmask & DTK_M(HOUR)) != 0)
							{
								tm->tm_min = val;
								tmask = DTK_M(MINUTE);
							}
							else
							{
								tm->tm_mon = val;
								tmask = DTK_M(MONTH);
							}
							break;

						case DTK_DAY:
							tm->tm_mday = val;
							tmask = DTK_M(DAY);
							break;

						case DTK_HOUR:
							tm->tm_hour = val;
							tmask = DTK_M(HOUR);
							break;

						case DTK_MINUTE:
							tm->tm_min = val;
							tmask = DTK_M(MINUTE);
							break;

						case DTK_SECOND:
							tm->tm_sec = val;
							tmask = DTK_M(SECOND);
							if (*cp == '.')
							{
								double		frac;

								frac = strtod(cp, &cp);
								if (*cp != '\0')
									return -1;
								*fsec = frac * 1000000;
							}
							break;

						case DTK_TZ:
							tmask = DTK_M(TZ);
							if (DecodeTimezone(field[i], tzp) != 0)
								return -1;
							break;

						case DTK_JULIAN:
							/***
							 * previous field was a label for "julian date"?
							 ***/
							tmask = DTK_DATE_M;
							j2date(val, &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
							/* fractional Julian Day? */
							if (*cp == '.')
							{
								double		time;

								time = strtod(cp, &cp);
								if (*cp != '\0')
									return -1;

								tmask |= DTK_TIME_M;
								dt2time((time * USECS_PER_DAY), &tm->tm_hour, &tm->tm_min, &tm->tm_sec, fsec);
							}
							break;

						case DTK_TIME:
							/* previous field was "t" for ISO time */
							if ((ftype[i] = DecodeNumberField(strlen(field[i]), field[i], (fmask | DTK_DATE_M),
															  &tmask, tm, fsec, &is2digits)) < 0)
								return -1;

							if (tmask != DTK_TIME_M)
								return -1;
							break;

						default:
							return -1;
							break;
					}

					ptype = 0;
					*dtype = DTK_DATE;
				}
				else
				{
					char	   *cp;
					int			flen;

					flen = strlen(field[i]);
					cp = strchr(field[i], '.');

					/* Embedded decimal and no date yet? */
					if (cp != NULL && !(fmask & DTK_DATE_M))
					{
						if (DecodeDate(field[i], fmask, &tmask, tm, EuroDates) != 0)
							return -1;
					}
					/* embedded decimal and several digits before? */
					else if (cp != NULL && flen - strlen(cp) > 2)
					{
						/*
						 * Interpret as a concatenated date or time Set the
						 * type field to allow decoding other fields later.
						 * Example: 20011223 or 040506
						 */
						if ((ftype[i] = DecodeNumberField(flen, field[i], fmask,
														  &tmask, tm, fsec, &is2digits)) < 0)
							return -1;
					}
					else if (flen > 4)
					{
						if ((ftype[i] = DecodeNumberField(flen, field[i], fmask,
														  &tmask, tm, fsec, &is2digits)) < 0)
							return -1;
					}
					/* otherwise it is a single date/time field... */
					else if (DecodeNumber(flen, field[i], fmask,
										  &tmask, tm, fsec, &is2digits, EuroDates) != 0)
						return -1;
				}
				break;

			case DTK_STRING:
			case DTK_SPECIAL:
				type = DecodeSpecial(i, field[i], &val);
				if (type == IGNORE_DTF)
					continue;

				tmask = DTK_M(type);
				switch (type)
				{
					case RESERV:
						switch (val)
						{
							case DTK_NOW:
								tmask = (DTK_DATE_M | DTK_TIME_M | DTK_M(TZ));
								*dtype = DTK_DATE;
								GetCurrentDateTime(tm);
								break;

							case DTK_YESTERDAY:
								tmask = DTK_DATE_M;
								*dtype = DTK_DATE;
								GetCurrentDateTime(tm);
								j2date(date2j(tm->tm_year, tm->tm_mon, tm->tm_mday) - 1,
									   &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
								tm->tm_hour = 0;
								tm->tm_min = 0;
								tm->tm_sec = 0;
								break;

							case DTK_TODAY:
								tmask = DTK_DATE_M;
								*dtype = DTK_DATE;
								GetCurrentDateTime(tm);
								tm->tm_hour = 0;
								tm->tm_min = 0;
								tm->tm_sec = 0;
								break;

							case DTK_TOMORROW:
								tmask = DTK_DATE_M;
								*dtype = DTK_DATE;
								GetCurrentDateTime(tm);
								j2date(date2j(tm->tm_year, tm->tm_mon, tm->tm_mday) + 1,
									   &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
								tm->tm_hour = 0;
								tm->tm_min = 0;
								tm->tm_sec = 0;
								break;

							case DTK_ZULU:
								tmask = (DTK_TIME_M | DTK_M(TZ));
								*dtype = DTK_DATE;
								tm->tm_hour = 0;
								tm->tm_min = 0;
								tm->tm_sec = 0;
								if (tzp != NULL)
									*tzp = 0;
								break;

							default:
								*dtype = val;
						}

						break;

					case MONTH:

						/*
						 * already have a (numeric) month? then see if we can
						 * substitute...
						 */
						if ((fmask & DTK_M(MONTH)) && !haveTextMonth &&
							!(fmask & DTK_M(DAY)) && tm->tm_mon >= 1 && tm->tm_mon <= 31)
						{
							tm->tm_mday = tm->tm_mon;
							tmask = DTK_M(DAY);
						}
						haveTextMonth = true;
						tm->tm_mon = val;
						break;

					case DTZMOD:

						/*
						 * daylight savings time modifier (solves "MET DST"
						 * syntax)
						 */
						tmask |= DTK_M(DTZ);
						tm->tm_isdst = 1;
						if (tzp == NULL)
							return -1;
						*tzp -= val;
						break;

					case DTZ:

						/*
						 * set mask for TZ here _or_ check for DTZ later when
						 * getting default timezone
						 */
						tmask |= DTK_M(TZ);
						tm->tm_isdst = 1;
						if (tzp == NULL)
							return -1;
						*tzp = -val;
						ftype[i] = DTK_TZ;
						break;

					case TZ:
						tm->tm_isdst = 0;
						if (tzp == NULL)
							return -1;
						*tzp = -val;
						ftype[i] = DTK_TZ;
						break;

					case IGNORE_DTF:
						break;

					case AMPM:
						mer = val;
						break;

					case ADBC:
						bc = (val == BC);
						break;

					case DOW:
						tm->tm_wday = val;
						break;

					case UNITS:
						tmask = 0;
						ptype = val;
						break;

					case ISOTIME:

						/*
						 * This is a filler field "t" indicating that the next
						 * field is time. Try to verify that this is sensible.
						 */
						tmask = 0;

						/* No preceding date? Then quit... */
						if ((fmask & DTK_DATE_M) != DTK_DATE_M)
							return -1;

						/***
						 * We will need one of the following fields:
						 *	DTK_NUMBER should be hhmmss.fff
						 *	DTK_TIME should be hh:mm:ss.fff
						 *	DTK_DATE should be hhmmss-zz
						 ***/
						if (i >= nf - 1 ||
							(ftype[i + 1] != DTK_NUMBER &&
							 ftype[i + 1] != DTK_TIME &&
							 ftype[i + 1] != DTK_DATE))
							return -1;

						ptype = val;
						break;

					default:
						return -1;
				}
				break;

			default:
				return -1;
		}

		if (tmask & fmask)
			return -1;
		fmask |= tmask;
	}

	/* there is no year zero in AD/BC notation; i.e. "1 BC" == year 0 */
	if (bc)
	{
		if (tm->tm_year > 0)
			tm->tm_year = -(tm->tm_year - 1);
		else
			return -1;
	}
	else if (is2digits)
	{
		if (tm->tm_year < 70)
			tm->tm_year += 2000;
		else if (tm->tm_year < 100)
			tm->tm_year += 1900;
	}

	if (mer != HR24 && tm->tm_hour > 12)
		return -1;
	if (mer == AM && tm->tm_hour == 12)
		tm->tm_hour = 0;
	else if (mer == PM && tm->tm_hour != 12)
		tm->tm_hour += 12;

	/* do additional checking for full date specs... */
	if (*dtype == DTK_DATE)
	{
		if ((fmask & DTK_DATE_M) != DTK_DATE_M)
			return ((fmask & DTK_TIME_M) == DTK_TIME_M) ? 1 : -1;

		/*
		 * check for valid day of month, now that we know for sure the month
		 * and year...
		 */
		if (tm->tm_mday < 1 || tm->tm_mday > day_tab[isleap(tm->tm_year)][tm->tm_mon - 1])
			return -1;

		/*
		 * backend tried to find local timezone here but we don't use the
		 * result afterwards anyway so we only check for this error: daylight
		 * savings time modifier but no standard timezone?
		 */
		if ((fmask & DTK_DATE_M) == DTK_DATE_M && tzp != NULL && !(fmask & DTK_M(TZ)) && (fmask & DTK_M(DTZMOD)))
			return -1;
	}

	return 0;
}