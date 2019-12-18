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
struct pg_tm {int tm_isdst; } ;
typedef  int /*<<< orphan*/  pg_tz ;
typedef  int /*<<< orphan*/  pg_time_t ;

/* Variables and functions */
 scalar_t__ DetermineTimeZoneAbbrevOffsetInternal (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int*,int*) ; 
 int DetermineTimeZoneOffsetInternal (struct pg_tm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
DetermineTimeZoneAbbrevOffset(struct pg_tm *tm, const char *abbr, pg_tz *tzp)
{
	pg_time_t	t;
	int			zone_offset;
	int			abbr_offset;
	int			abbr_isdst;

	/*
	 * Compute the UTC time we want to probe at.  (In event of overflow, we'll
	 * probe at the epoch, which is a bit random but probably doesn't matter.)
	 */
	zone_offset = DetermineTimeZoneOffsetInternal(tm, tzp, &t);

	/*
	 * Try to match the abbreviation to something in the zone definition.
	 */
	if (DetermineTimeZoneAbbrevOffsetInternal(t, abbr, tzp,
											  &abbr_offset, &abbr_isdst))
	{
		/* Success, so use the abbrev-specific answers. */
		tm->tm_isdst = abbr_isdst;
		return abbr_offset;
	}

	/*
	 * No match, so use the answers we already got from
	 * DetermineTimeZoneOffsetInternal.
	 */
	return zone_offset;
}