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
struct pg_tm {int tm_mon; scalar_t__ tm_isdst; scalar_t__ tm_year; int tm_mday; int tm_hour; int tm_min; size_t tm_wday; } ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 char* AppendTimestampSeconds (char*,struct pg_tm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DATEORDER_DMY ; 
 int /*<<< orphan*/  DateOrder ; 
 char* EncodeTimezone (char*,int,int) ; 
 char* MAXTZLEN ; 
 int MONTHS_PER_YEAR ; 
#define  USE_GERMAN_DATES 132 
#define  USE_ISO_DATES 131 
#define  USE_POSTGRES_DATES 130 
#define  USE_SQL_DATES 129 
#define  USE_XSD_DATES 128 
 int date2j (int,int,int) ; 
 char** days ; 
 size_t j2day (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char** months ; 
 char* pg_ltostr_zeropad (char*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void
EncodeDateTime(struct pg_tm *tm, fsec_t fsec, bool print_tz, int tz, const char *tzn, int style, char *str)
{
	int			day;

	Assert(tm->tm_mon >= 1 && tm->tm_mon <= MONTHS_PER_YEAR);

	/*
	 * Negative tm_isdst means we have no valid time zone translation.
	 */
	if (tm->tm_isdst < 0)
		print_tz = false;

	switch (style)
	{
		case USE_ISO_DATES:
		case USE_XSD_DATES:
			/* Compatible with ISO-8601 date formats */
			str = pg_ltostr_zeropad(str,
									(tm->tm_year > 0) ? tm->tm_year : -(tm->tm_year - 1), 4);
			*str++ = '-';
			str = pg_ltostr_zeropad(str, tm->tm_mon, 2);
			*str++ = '-';
			str = pg_ltostr_zeropad(str, tm->tm_mday, 2);
			*str++ = (style == USE_ISO_DATES) ? ' ' : 'T';
			str = pg_ltostr_zeropad(str, tm->tm_hour, 2);
			*str++ = ':';
			str = pg_ltostr_zeropad(str, tm->tm_min, 2);
			*str++ = ':';
			str = AppendTimestampSeconds(str, tm, fsec);
			if (print_tz)
				str = EncodeTimezone(str, tz, style);
			break;

		case USE_SQL_DATES:
			/* Compatible with Oracle/Ingres date formats */
			if (DateOrder == DATEORDER_DMY)
			{
				str = pg_ltostr_zeropad(str, tm->tm_mday, 2);
				*str++ = '/';
				str = pg_ltostr_zeropad(str, tm->tm_mon, 2);
			}
			else
			{
				str = pg_ltostr_zeropad(str, tm->tm_mon, 2);
				*str++ = '/';
				str = pg_ltostr_zeropad(str, tm->tm_mday, 2);
			}
			*str++ = '/';
			str = pg_ltostr_zeropad(str,
									(tm->tm_year > 0) ? tm->tm_year : -(tm->tm_year - 1), 4);
			*str++ = ' ';
			str = pg_ltostr_zeropad(str, tm->tm_hour, 2);
			*str++ = ':';
			str = pg_ltostr_zeropad(str, tm->tm_min, 2);
			*str++ = ':';
			str = AppendTimestampSeconds(str, tm, fsec);

			/*
			 * Note: the uses of %.*s in this function would be risky if the
			 * timezone names ever contain non-ASCII characters.  However, all
			 * TZ abbreviations in the IANA database are plain ASCII.
			 */
			if (print_tz)
			{
				if (tzn)
				{
					sprintf(str, " %.*s", MAXTZLEN, tzn);
					str += strlen(str);
				}
				else
					str = EncodeTimezone(str, tz, style);
			}
			break;

		case USE_GERMAN_DATES:
			/* German variant on European style */
			str = pg_ltostr_zeropad(str, tm->tm_mday, 2);
			*str++ = '.';
			str = pg_ltostr_zeropad(str, tm->tm_mon, 2);
			*str++ = '.';
			str = pg_ltostr_zeropad(str,
									(tm->tm_year > 0) ? tm->tm_year : -(tm->tm_year - 1), 4);
			*str++ = ' ';
			str = pg_ltostr_zeropad(str, tm->tm_hour, 2);
			*str++ = ':';
			str = pg_ltostr_zeropad(str, tm->tm_min, 2);
			*str++ = ':';
			str = AppendTimestampSeconds(str, tm, fsec);

			if (print_tz)
			{
				if (tzn)
				{
					sprintf(str, " %.*s", MAXTZLEN, tzn);
					str += strlen(str);
				}
				else
					str = EncodeTimezone(str, tz, style);
			}
			break;

		case USE_POSTGRES_DATES:
		default:
			/* Backward-compatible with traditional Postgres abstime dates */
			day = date2j(tm->tm_year, tm->tm_mon, tm->tm_mday);
			tm->tm_wday = j2day(day);
			memcpy(str, days[tm->tm_wday], 3);
			str += 3;
			*str++ = ' ';
			if (DateOrder == DATEORDER_DMY)
			{
				str = pg_ltostr_zeropad(str, tm->tm_mday, 2);
				*str++ = ' ';
				memcpy(str, months[tm->tm_mon - 1], 3);
				str += 3;
			}
			else
			{
				memcpy(str, months[tm->tm_mon - 1], 3);
				str += 3;
				*str++ = ' ';
				str = pg_ltostr_zeropad(str, tm->tm_mday, 2);
			}
			*str++ = ' ';
			str = pg_ltostr_zeropad(str, tm->tm_hour, 2);
			*str++ = ':';
			str = pg_ltostr_zeropad(str, tm->tm_min, 2);
			*str++ = ':';
			str = AppendTimestampSeconds(str, tm, fsec);
			*str++ = ' ';
			str = pg_ltostr_zeropad(str,
									(tm->tm_year > 0) ? tm->tm_year : -(tm->tm_year - 1), 4);

			if (print_tz)
			{
				if (tzn)
				{
					sprintf(str, " %.*s", MAXTZLEN, tzn);
					str += strlen(str);
				}
				else
				{
					/*
					 * We have a time zone, but no string version. Use the
					 * numeric form, but be sure to include a leading space to
					 * avoid formatting something which would be rejected by
					 * the date/time parser later. - thomas 2001-10-19
					 */
					*str++ = ' ';
					str = EncodeTimezone(str, tz, style);
				}
			}
			break;
	}

	if (tm->tm_year <= 0)
	{
		memcpy(str, " BC", 3);	/* Don't copy NUL */
		str += 3;
	}
	*str = '\0';
}