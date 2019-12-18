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
struct ttinfo {int tt_isdst; long tt_utoff; } ;
struct state {int timecnt; int typecnt; scalar_t__ const* ats; int* types; struct ttinfo* ttis; scalar_t__ goahead; scalar_t__ goback; } ;
struct TYPE_3__ {struct state state; } ;
typedef  TYPE_1__ pg_tz ;
typedef  scalar_t__ pg_time_t ;
typedef  scalar_t__ int64 ;

/* Variables and functions */
 scalar_t__ AVGSECSPERYEAR ; 
 scalar_t__ YEARSPERREPEAT ; 

int
pg_next_dst_boundary(const pg_time_t *timep,
					 long int *before_gmtoff,
					 int *before_isdst,
					 pg_time_t *boundary,
					 long int *after_gmtoff,
					 int *after_isdst,
					 const pg_tz *tz)
{
	const struct state *sp;
	const struct ttinfo *ttisp;
	int			i;
	int			j;
	const pg_time_t t = *timep;

	sp = &tz->state;
	if (sp->timecnt == 0)
	{
		/* non-DST zone, use lowest-numbered standard type */
		i = 0;
		while (sp->ttis[i].tt_isdst)
			if (++i >= sp->typecnt)
			{
				i = 0;
				break;
			}
		ttisp = &sp->ttis[i];
		*before_gmtoff = ttisp->tt_utoff;
		*before_isdst = ttisp->tt_isdst;
		return 0;
	}
	if ((sp->goback && t < sp->ats[0]) ||
		(sp->goahead && t > sp->ats[sp->timecnt - 1]))
	{
		/* For values outside the transition table, extrapolate */
		pg_time_t	newt = t;
		pg_time_t	seconds;
		pg_time_t	tcycles;
		int64		icycles;
		int			result;

		if (t < sp->ats[0])
			seconds = sp->ats[0] - t;
		else
			seconds = t - sp->ats[sp->timecnt - 1];
		--seconds;
		tcycles = seconds / YEARSPERREPEAT / AVGSECSPERYEAR;
		++tcycles;
		icycles = tcycles;
		if (tcycles - icycles >= 1 || icycles - tcycles >= 1)
			return -1;
		seconds = icycles;
		seconds *= YEARSPERREPEAT;
		seconds *= AVGSECSPERYEAR;
		if (t < sp->ats[0])
			newt += seconds;
		else
			newt -= seconds;
		if (newt < sp->ats[0] ||
			newt > sp->ats[sp->timecnt - 1])
			return -1;			/* "cannot happen" */

		result = pg_next_dst_boundary(&newt, before_gmtoff,
									  before_isdst,
									  boundary,
									  after_gmtoff,
									  after_isdst,
									  tz);
		if (t < sp->ats[0])
			*boundary -= seconds;
		else
			*boundary += seconds;
		return result;
	}

	if (t >= sp->ats[sp->timecnt - 1])
	{
		/* No known transition > t, so use last known segment's type */
		i = sp->types[sp->timecnt - 1];
		ttisp = &sp->ttis[i];
		*before_gmtoff = ttisp->tt_utoff;
		*before_isdst = ttisp->tt_isdst;
		return 0;
	}
	if (t < sp->ats[0])
	{
		/* For "before", use lowest-numbered standard type */
		i = 0;
		while (sp->ttis[i].tt_isdst)
			if (++i >= sp->typecnt)
			{
				i = 0;
				break;
			}
		ttisp = &sp->ttis[i];
		*before_gmtoff = ttisp->tt_utoff;
		*before_isdst = ttisp->tt_isdst;
		*boundary = sp->ats[0];
		/* And for "after", use the first segment's type */
		i = sp->types[0];
		ttisp = &sp->ttis[i];
		*after_gmtoff = ttisp->tt_utoff;
		*after_isdst = ttisp->tt_isdst;
		return 1;
	}
	/* Else search to find the boundary following t */
	{
		int			lo = 1;
		int			hi = sp->timecnt - 1;

		while (lo < hi)
		{
			int			mid = (lo + hi) >> 1;

			if (t < sp->ats[mid])
				hi = mid;
			else
				lo = mid + 1;
		}
		i = lo;
	}
	j = sp->types[i - 1];
	ttisp = &sp->ttis[j];
	*before_gmtoff = ttisp->tt_utoff;
	*before_isdst = ttisp->tt_isdst;
	*boundary = sp->ats[i];
	j = sp->types[i];
	ttisp = &sp->ttis[j];
	*after_gmtoff = ttisp->tt_utoff;
	*after_isdst = ttisp->tt_isdst;
	return 1;
}