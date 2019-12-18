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
union un_fmt_comb {char* str_val; int uint_val; char char_val; double int64_val; } ;
typedef  double timestamp ;
struct tm {size_t tm_mon; int tm_year; int tm_mday; int tm_hour; int tm_yday; int tm_min; int tm_sec; } ;
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int PGTYPES_TYPE_CHAR ; 
 int PGTYPES_TYPE_INT64 ; 
 int PGTYPES_TYPE_NOTHING ; 
 int PGTYPES_TYPE_STRING_CONSTANT ; 
 int PGTYPES_TYPE_UINT ; 
 int PGTYPES_TYPE_UINT_2_LS ; 
 int PGTYPES_TYPE_UINT_2_LZ ; 
 int PGTYPES_TYPE_UINT_3_LZ ; 
 double SetEpochTimestamp () ; 
 char** days ; 
 char** months ; 
 char** pgtypes_date_months ; 
 char** pgtypes_date_weekdays_short ; 
 int pgtypes_fmt_replace (union un_fmt_comb,int,char**,int*) ; 
 int strftime (char*,int,char const*,struct tm*) ; 

__attribute__((used)) static int
dttofmtasc_replace(timestamp * ts, date dDate, int dow, struct tm *tm,
				   char *output, int *pstr_len, const char *fmtstr)
{
	union un_fmt_comb replace_val;
	int			replace_type;
	int			i;
	const char *p = fmtstr;
	char	   *q = output;

	while (*p)
	{
		if (*p == '%')
		{
			p++;
			/* fix compiler warning */
			replace_type = PGTYPES_TYPE_NOTHING;
			switch (*p)
			{
					/* the abbreviated name of the day in the week */
					/* XXX should be locale aware */
				case 'a':
					replace_val.str_val = pgtypes_date_weekdays_short[dow];
					replace_type = PGTYPES_TYPE_STRING_CONSTANT;
					break;
					/* the full name of the day in the week */
					/* XXX should be locale aware */
				case 'A':
					replace_val.str_val = days[dow];
					replace_type = PGTYPES_TYPE_STRING_CONSTANT;
					break;
					/* the abbreviated name of the month */
					/* XXX should be locale aware */
				case 'b':
				case 'h':
					replace_val.str_val = months[tm->tm_mon];
					replace_type = PGTYPES_TYPE_STRING_CONSTANT;
					break;
					/* the full name of the month */
					/* XXX should be locale aware */
				case 'B':
					replace_val.str_val = pgtypes_date_months[tm->tm_mon];
					replace_type = PGTYPES_TYPE_STRING_CONSTANT;
					break;

					/*
					 * The	preferred  date  and  time	representation	for
					 * the current locale.
					 */
				case 'c':
					/* XXX */
					break;
					/* the century number with leading zeroes */
				case 'C':
					replace_val.uint_val = tm->tm_year / 100;
					replace_type = PGTYPES_TYPE_UINT_2_LZ;
					break;
					/* day with leading zeroes (01 - 31) */
				case 'd':
					replace_val.uint_val = tm->tm_mday;
					replace_type = PGTYPES_TYPE_UINT_2_LZ;
					break;
					/* the date in the format mm/dd/yy */
				case 'D':

					/*
					 * ts, dDate, dow, tm is information about the timestamp
					 *
					 * q is the start of the current output buffer
					 *
					 * pstr_len is a pointer to the remaining size of output,
					 * i.e. the size of q
					 */
					i = dttofmtasc_replace(ts, dDate, dow, tm,
										   q, pstr_len,
										   "%m/%d/%y");
					if (i)
						return i;
					break;
					/* day with leading spaces (01 - 31) */
				case 'e':
					replace_val.uint_val = tm->tm_mday;
					replace_type = PGTYPES_TYPE_UINT_2_LS;
					break;

					/*
					 * alternative format modifier
					 */
				case 'E':
					{
						char		tmp[4] = "%Ex";

						p++;
						if (*p == '\0')
							return -1;
						tmp[2] = *p;

						/*
						 * strftime's month is 0 based, ours is 1 based
						 */
						tm->tm_mon -= 1;
						i = strftime(q, *pstr_len, tmp, tm);
						if (i == 0)
							return -1;
						while (*q)
						{
							q++;
							(*pstr_len)--;
						}
						tm->tm_mon += 1;
						replace_type = PGTYPES_TYPE_NOTHING;
						break;
					}

					/*
					 * The ISO 8601 year with century as a decimal number. The
					 * 4-digit year corresponding to the ISO week number.
					 */
				case 'G':
					{
						/* Keep compiler quiet - Don't use a literal format */
						const char *fmt = "%G";

						tm->tm_mon -= 1;
						i = strftime(q, *pstr_len, fmt, tm);
						if (i == 0)
							return -1;
						while (*q)
						{
							q++;
							(*pstr_len)--;
						}
						tm->tm_mon += 1;
						replace_type = PGTYPES_TYPE_NOTHING;
					}
					break;

					/*
					 * Like %G, but without century, i.e., with a 2-digit year
					 * (00-99).
					 */
				case 'g':
					{
						const char *fmt = "%g"; /* Keep compiler quiet about
												 * 2-digit year */

						tm->tm_mon -= 1;
						i = strftime(q, *pstr_len, fmt, tm);
						if (i == 0)
							return -1;
						while (*q)
						{
							q++;
							(*pstr_len)--;
						}
						tm->tm_mon += 1;
						replace_type = PGTYPES_TYPE_NOTHING;
					}
					break;
					/* hour (24 hour clock) with leading zeroes */
				case 'H':
					replace_val.uint_val = tm->tm_hour;
					replace_type = PGTYPES_TYPE_UINT_2_LZ;
					break;
					/* hour (12 hour clock) with leading zeroes */
				case 'I':
					replace_val.uint_val = tm->tm_hour % 12;
					replace_type = PGTYPES_TYPE_UINT_2_LZ;
					break;

					/*
					 * The day of the year as a decimal number with leading
					 * zeroes. It ranges from 001 to 366.
					 */
				case 'j':
					replace_val.uint_val = tm->tm_yday;
					replace_type = PGTYPES_TYPE_UINT_3_LZ;
					break;

					/*
					 * The hour (24 hour clock). Leading zeroes will be turned
					 * into spaces.
					 */
				case 'k':
					replace_val.uint_val = tm->tm_hour;
					replace_type = PGTYPES_TYPE_UINT_2_LS;
					break;

					/*
					 * The hour (12 hour clock). Leading zeroes will be turned
					 * into spaces.
					 */
				case 'l':
					replace_val.uint_val = tm->tm_hour % 12;
					replace_type = PGTYPES_TYPE_UINT_2_LS;
					break;
					/* The month as a decimal number with a leading zero */
				case 'm':
					replace_val.uint_val = tm->tm_mon;
					replace_type = PGTYPES_TYPE_UINT_2_LZ;
					break;
					/* The minute as a decimal number with a leading zero */
				case 'M':
					replace_val.uint_val = tm->tm_min;
					replace_type = PGTYPES_TYPE_UINT_2_LZ;
					break;
					/* A newline character */
				case 'n':
					replace_val.char_val = '\n';
					replace_type = PGTYPES_TYPE_CHAR;
					break;
					/* the AM/PM specifier (uppercase) */
					/* XXX should be locale aware */
				case 'p':
					if (tm->tm_hour < 12)
						replace_val.str_val = "AM";
					else
						replace_val.str_val = "PM";
					replace_type = PGTYPES_TYPE_STRING_CONSTANT;
					break;
					/* the AM/PM specifier (lowercase) */
					/* XXX should be locale aware */
				case 'P':
					if (tm->tm_hour < 12)
						replace_val.str_val = "am";
					else
						replace_val.str_val = "pm";
					replace_type = PGTYPES_TYPE_STRING_CONSTANT;
					break;
					/* the time in the format %I:%M:%S %p */
					/* XXX should be locale aware */
				case 'r':
					i = dttofmtasc_replace(ts, dDate, dow, tm,
										   q, pstr_len,
										   "%I:%M:%S %p");
					if (i)
						return i;
					break;
					/* The time in 24 hour notation (%H:%M) */
				case 'R':
					i = dttofmtasc_replace(ts, dDate, dow, tm,
										   q, pstr_len,
										   "%H:%M");
					if (i)
						return i;
					break;
					/* The number of seconds since the Epoch (1970-01-01) */
				case 's':
					replace_val.int64_val = (*ts - SetEpochTimestamp()) / 1000000.0;
					replace_type = PGTYPES_TYPE_INT64;
					break;
					/* seconds as a decimal number with leading zeroes */
				case 'S':
					replace_val.uint_val = tm->tm_sec;
					replace_type = PGTYPES_TYPE_UINT_2_LZ;
					break;
					/* A tabulator */
				case 't':
					replace_val.char_val = '\t';
					replace_type = PGTYPES_TYPE_CHAR;
					break;
					/* The time in 24 hour notation (%H:%M:%S) */
				case 'T':
					i = dttofmtasc_replace(ts, dDate, dow, tm,
										   q, pstr_len,
										   "%H:%M:%S");
					if (i)
						return i;
					break;

					/*
					 * The day of the week as a decimal, Monday = 1, Sunday =
					 * 7
					 */
				case 'u':
					replace_val.uint_val = dow;
					if (replace_val.uint_val == 0)
						replace_val.uint_val = 7;
					replace_type = PGTYPES_TYPE_UINT;
					break;
					/* The week number of the year as a decimal number */
				case 'U':
					tm->tm_mon -= 1;
					i = strftime(q, *pstr_len, "%U", tm);
					if (i == 0)
						return -1;
					while (*q)
					{
						q++;
						(*pstr_len)--;
					}
					tm->tm_mon += 1;
					replace_type = PGTYPES_TYPE_NOTHING;
					break;

					/*
					 * The ISO 8601:1988 week number of the current year as a
					 * decimal number.
					 */
				case 'V':
					{
						/* Keep compiler quiet - Don't use a literal format */
						const char *fmt = "%V";

						i = strftime(q, *pstr_len, fmt, tm);
						if (i == 0)
							return -1;
						while (*q)
						{
							q++;
							(*pstr_len)--;
						}
						replace_type = PGTYPES_TYPE_NOTHING;
					}
					break;

					/*
					 * The day of the week as a decimal, Sunday being 0 and
					 * Monday 1.
					 */
				case 'w':
					replace_val.uint_val = dow;
					replace_type = PGTYPES_TYPE_UINT;
					break;
					/* The week number of the year (another definition) */
				case 'W':
					tm->tm_mon -= 1;
					i = strftime(q, *pstr_len, "%U", tm);
					if (i == 0)
						return -1;
					while (*q)
					{
						q++;
						(*pstr_len)--;
					}
					tm->tm_mon += 1;
					replace_type = PGTYPES_TYPE_NOTHING;
					break;

					/*
					 * The preferred date representation for the current
					 * locale without the time.
					 */
				case 'x':
					{
						const char *fmt = "%x"; /* Keep compiler quiet about
												 * 2-digit year */

						tm->tm_mon -= 1;
						i = strftime(q, *pstr_len, fmt, tm);
						if (i == 0)
							return -1;
						while (*q)
						{
							q++;
							(*pstr_len)--;
						}
						tm->tm_mon += 1;
						replace_type = PGTYPES_TYPE_NOTHING;
					}
					break;

					/*
					 * The preferred time representation for the current
					 * locale without the date.
					 */
				case 'X':
					tm->tm_mon -= 1;
					i = strftime(q, *pstr_len, "%X", tm);
					if (i == 0)
						return -1;
					while (*q)
					{
						q++;
						(*pstr_len)--;
					}
					tm->tm_mon += 1;
					replace_type = PGTYPES_TYPE_NOTHING;
					break;
					/* The year without the century (2 digits, leading zeroes) */
				case 'y':
					replace_val.uint_val = tm->tm_year % 100;
					replace_type = PGTYPES_TYPE_UINT_2_LZ;
					break;
					/* The year with the century (4 digits) */
				case 'Y':
					replace_val.uint_val = tm->tm_year;
					replace_type = PGTYPES_TYPE_UINT;
					break;
					/* The time zone offset from GMT */
				case 'z':
					tm->tm_mon -= 1;
					i = strftime(q, *pstr_len, "%z", tm);
					if (i == 0)
						return -1;
					while (*q)
					{
						q++;
						(*pstr_len)--;
					}
					tm->tm_mon += 1;
					replace_type = PGTYPES_TYPE_NOTHING;
					break;
					/* The name or abbreviation of the time zone */
				case 'Z':
					tm->tm_mon -= 1;
					i = strftime(q, *pstr_len, "%Z", tm);
					if (i == 0)
						return -1;
					while (*q)
					{
						q++;
						(*pstr_len)--;
					}
					tm->tm_mon += 1;
					replace_type = PGTYPES_TYPE_NOTHING;
					break;
					/* A % sign */
				case '%':
					replace_val.char_val = '%';
					replace_type = PGTYPES_TYPE_CHAR;
					break;
				case '\0':
					/* fmtstr: foo%' - The string ends with a % sign */

					/*
					 * this is not compliant to the specification
					 */
					return -1;
				default:

					/*
					 * if we don't know the pattern, we just copy it
					 */
					if (*pstr_len > 1)
					{
						*q = '%';
						q++;
						(*pstr_len)--;
						if (*pstr_len > 1)
						{
							*q = *p;
							q++;
							(*pstr_len)--;
						}
						else
						{
							*q = '\0';
							return -1;
						}
						*q = '\0';
					}
					else
						return -1;
					break;
			}
			i = pgtypes_fmt_replace(replace_val, replace_type, &q, pstr_len);
			if (i)
				return i;
		}
		else
		{
			if (*pstr_len > 1)
			{
				*q = *p;
				(*pstr_len)--;
				q++;
				*q = '\0';
			}
			else
				return -1;
		}
		p++;
	}
	return 0;
}