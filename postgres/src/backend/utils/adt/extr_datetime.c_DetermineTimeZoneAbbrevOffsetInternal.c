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
typedef  int /*<<< orphan*/  upabbr ;
typedef  int /*<<< orphan*/  pg_tz ;
typedef  int /*<<< orphan*/  pg_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  TZ_STRLEN_MAX ; 
 scalar_t__ pg_interpret_timezone_abbrev (char*,int /*<<< orphan*/ *,long*,int*,int /*<<< orphan*/ *) ; 
 unsigned char pg_toupper (unsigned char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static bool
DetermineTimeZoneAbbrevOffsetInternal(pg_time_t t, const char *abbr, pg_tz *tzp,
									  int *offset, int *isdst)
{
	char		upabbr[TZ_STRLEN_MAX + 1];
	unsigned char *p;
	long int	gmtoff;

	/* We need to force the abbrev to upper case */
	strlcpy(upabbr, abbr, sizeof(upabbr));
	for (p = (unsigned char *) upabbr; *p; p++)
		*p = pg_toupper(*p);

	/* Look up the abbrev's meaning at this time in this zone */
	if (pg_interpret_timezone_abbrev(upabbr,
									 &t,
									 &gmtoff,
									 isdst,
									 tzp))
	{
		/* Change sign to agree with DetermineTimeZoneOffset() */
		*offset = (int) -gmtoff;
		return true;
	}
	return false;
}