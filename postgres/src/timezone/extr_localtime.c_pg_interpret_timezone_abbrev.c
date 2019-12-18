#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttinfo {int tt_desigidx; long tt_utoff; int tt_isdst; } ;
struct state {char* chars; int charcnt; int timecnt; scalar_t__ const* ats; size_t* types; struct ttinfo* ttis; } ;
struct TYPE_3__ {struct state state; } ;
typedef  TYPE_1__ pg_tz ;
typedef  scalar_t__ pg_time_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const*) ; 

bool
pg_interpret_timezone_abbrev(const char *abbrev,
							 const pg_time_t *timep,
							 long int *gmtoff,
							 int *isdst,
							 const pg_tz *tz)
{
	const struct state *sp;
	const char *abbrs;
	const struct ttinfo *ttisp;
	int			abbrind;
	int			cutoff;
	int			i;
	const pg_time_t t = *timep;

	sp = &tz->state;

	/*
	 * Locate the abbreviation in the zone's abbreviation list.  We assume
	 * there are not duplicates in the list.
	 */
	abbrs = sp->chars;
	abbrind = 0;
	while (abbrind < sp->charcnt)
	{
		if (strcmp(abbrev, abbrs + abbrind) == 0)
			break;
		while (abbrs[abbrind] != '\0')
			abbrind++;
		abbrind++;
	}
	if (abbrind >= sp->charcnt)
		return false;			/* not there! */

	/*
	 * Unlike pg_next_dst_boundary, we needn't sweat about extrapolation
	 * (goback/goahead zones).  Finding the newest or oldest meaning of the
	 * abbreviation should get us what we want, since extrapolation would just
	 * be repeating the newest or oldest meanings.
	 *
	 * Use binary search to locate the first transition > cutoff time.
	 */
	{
		int			lo = 0;
		int			hi = sp->timecnt;

		while (lo < hi)
		{
			int			mid = (lo + hi) >> 1;

			if (t < sp->ats[mid])
				hi = mid;
			else
				lo = mid + 1;
		}
		cutoff = lo;
	}

	/*
	 * Scan backwards to find the latest interval using the given abbrev
	 * before the cutoff time.
	 */
	for (i = cutoff - 1; i >= 0; i--)
	{
		ttisp = &sp->ttis[sp->types[i]];
		if (ttisp->tt_desigidx == abbrind)
		{
			*gmtoff = ttisp->tt_utoff;
			*isdst = ttisp->tt_isdst;
			return true;
		}
	}

	/*
	 * Not there, so scan forwards to find the first one after.
	 */
	for (i = cutoff; i < sp->timecnt; i++)
	{
		ttisp = &sp->ttis[sp->types[i]];
		if (ttisp->tt_desigidx == abbrind)
		{
			*gmtoff = ttisp->tt_utoff;
			*isdst = ttisp->tt_isdst;
			return true;
		}
	}

	return false;				/* hm, not actually used in any interval? */
}