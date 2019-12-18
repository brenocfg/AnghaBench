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
typedef  int /*<<< orphan*/  tzname ;
typedef  int /*<<< orphan*/  text ;
struct pg_tm {int dummy; } ;
typedef  int /*<<< orphan*/  pg_tz ;

/* Variables and functions */
 int DTERR_BAD_FORMAT ; 
 int DTERR_TZDISP_OVERFLOW ; 
 int DTZ ; 
 int DYNTZ ; 
 int DecodeTimezone (char*,int*) ; 
 int DecodeTimezoneAbbrev (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ **) ; 
 int DetermineTimeZoneAbbrevOffset (struct pg_tm*,char*,int /*<<< orphan*/ *) ; 
 int DetermineTimeZoneOffset (struct pg_tm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int TZ ; 
 int /*<<< orphan*/  TZ_STRLEN_MAX ; 
 char* downcase_truncate_identifier (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/ * pg_tzset (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  text_to_cstring_buffer (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
parse_sane_timezone(struct pg_tm *tm, text *zone)
{
	char		tzname[TZ_STRLEN_MAX + 1];
	int			rt;
	int			tz;

	text_to_cstring_buffer(zone, tzname, sizeof(tzname));

	/*
	 * Look up the requested timezone.  First we try to interpret it as a
	 * numeric timezone specification; if DecodeTimezone decides it doesn't
	 * like the format, we look in the timezone abbreviation table (to handle
	 * cases like "EST"), and if that also fails, we look in the timezone
	 * database (to handle cases like "America/New_York").  (This matches the
	 * order in which timestamp input checks the cases; it's important because
	 * the timezone database unwisely uses a few zone names that are identical
	 * to offset abbreviations.)
	 *
	 * Note pg_tzset happily parses numeric input that DecodeTimezone would
	 * reject.  To avoid having it accept input that would otherwise be seen
	 * as invalid, it's enough to disallow having a digit in the first
	 * position of our input string.
	 */
	if (isdigit((unsigned char) *tzname))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						"numeric time zone", tzname),
				 errhint("Numeric time zones must have \"-\" or \"+\" as first character.")));

	rt = DecodeTimezone(tzname, &tz);
	if (rt != 0)
	{
		char	   *lowzone;
		int			type,
					val;
		pg_tz	   *tzp;

		if (rt == DTERR_TZDISP_OVERFLOW)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("numeric time zone \"%s\" out of range", tzname)));
		else if (rt != DTERR_BAD_FORMAT)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("time zone \"%s\" not recognized", tzname)));

		/* DecodeTimezoneAbbrev requires lowercase input */
		lowzone = downcase_truncate_identifier(tzname,
											   strlen(tzname),
											   false);
		type = DecodeTimezoneAbbrev(0, lowzone, &val, &tzp);

		if (type == TZ || type == DTZ)
		{
			/* fixed-offset abbreviation */
			tz = -val;
		}
		else if (type == DYNTZ)
		{
			/* dynamic-offset abbreviation, resolve using specified time */
			tz = DetermineTimeZoneAbbrevOffset(tm, tzname, tzp);
		}
		else
		{
			/* try it as a full zone name */
			tzp = pg_tzset(tzname);
			if (tzp)
				tz = DetermineTimeZoneOffset(tm, tzp);
			else
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("time zone \"%s\" not recognized", tzname)));
		}
	}

	return tz;
}