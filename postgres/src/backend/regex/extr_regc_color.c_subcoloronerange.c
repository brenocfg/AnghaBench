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
struct vars {struct colormap* cm; } ;
struct state {int dummy; } ;
struct colormap {int numcmranges; TYPE_1__* cmranges; } ;
struct TYPE_3__ {scalar_t__ cmax; scalar_t__ cmin; int rownum; } ;
typedef  TYPE_1__ colormaprange ;
typedef  int /*<<< orphan*/  color ;
typedef  scalar_t__ chr ;

/* Variables and functions */
 int /*<<< orphan*/  CERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 scalar_t__ MALLOC (int) ; 
 scalar_t__ MAX_SIMPLE_CHR ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* newhicolorrow (struct colormap*,int) ; 
 int /*<<< orphan*/  subcoloronerow (struct vars*,int,struct state*,struct state*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
subcoloronerange(struct vars *v,
				 chr from,
				 chr to,
				 struct state *lp,
				 struct state *rp,
				 color *lastsubcolor)
{
	struct colormap *cm = v->cm;
	colormaprange *newranges;
	int			numnewranges;
	colormaprange *oldrange;
	int			oldrangen;
	int			newrow;

	/* Caller should take care of non-high-range cases */
	assert(from > MAX_SIMPLE_CHR);
	assert(from < to);

	/*
	 * Potentially, if we have N non-adjacent ranges, we could need as many as
	 * 2N+1 result ranges (consider case where new range spans 'em all).
	 */
	newranges = (colormaprange *)
		MALLOC((cm->numcmranges * 2 + 1) * sizeof(colormaprange));
	if (newranges == NULL)
	{
		CERR(REG_ESPACE);
		return;
	}
	numnewranges = 0;

	/* Ranges before target are unchanged */
	for (oldrange = cm->cmranges, oldrangen = 0;
		 oldrangen < cm->numcmranges;
		 oldrange++, oldrangen++)
	{
		if (oldrange->cmax >= from)
			break;
		newranges[numnewranges++] = *oldrange;
	}

	/*
	 * Deal with ranges that (partially) overlap the target.  As we process
	 * each such range, increase "from" to remove the dealt-with characters
	 * from the target range.
	 */
	while (oldrangen < cm->numcmranges && oldrange->cmin <= to)
	{
		if (from < oldrange->cmin)
		{
			/* Handle portion of new range that corresponds to no old range */
			newranges[numnewranges].cmin = from;
			newranges[numnewranges].cmax = oldrange->cmin - 1;
			/* row state should be cloned from the "all others" row */
			newranges[numnewranges].rownum = newrow = newhicolorrow(cm, 0);
			numnewranges++;
			/* Update colors in newrow and create arcs as needed */
			subcoloronerow(v, newrow, lp, rp, lastsubcolor);
			/* We've now fully processed the part of new range before old */
			from = oldrange->cmin;
		}

		if (from <= oldrange->cmin && to >= oldrange->cmax)
		{
			/* old range is fully contained in new, process it in-place */
			newranges[numnewranges++] = *oldrange;
			newrow = oldrange->rownum;
			from = oldrange->cmax + 1;
		}
		else
		{
			/* some part of old range does not overlap new range */
			if (from > oldrange->cmin)
			{
				/* emit portion of old range before new range */
				newranges[numnewranges].cmin = oldrange->cmin;
				newranges[numnewranges].cmax = from - 1;
				newranges[numnewranges].rownum = oldrange->rownum;
				numnewranges++;
			}
			/* emit common subrange, initially cloning from old range */
			newranges[numnewranges].cmin = from;
			newranges[numnewranges].cmax =
				(to < oldrange->cmax) ? to : oldrange->cmax;
			newranges[numnewranges].rownum = newrow =
				newhicolorrow(cm, oldrange->rownum);
			numnewranges++;
			if (to < oldrange->cmax)
			{
				/* emit portion of old range after new range */
				newranges[numnewranges].cmin = to + 1;
				newranges[numnewranges].cmax = oldrange->cmax;
				/* must clone the row if we are making two new ranges from old */
				newranges[numnewranges].rownum =
					(from > oldrange->cmin) ? newhicolorrow(cm, oldrange->rownum) :
					oldrange->rownum;
				numnewranges++;
			}
			from = oldrange->cmax + 1;
		}
		/* Update colors in newrow and create arcs as needed */
		subcoloronerow(v, newrow, lp, rp, lastsubcolor);
		/* we've now fully processed this old range */
		oldrange++, oldrangen++;
	}

	if (from <= to)
	{
		/* Handle portion of new range that corresponds to no old range */
		newranges[numnewranges].cmin = from;
		newranges[numnewranges].cmax = to;
		/* row state should be cloned from the "all others" row */
		newranges[numnewranges].rownum = newrow = newhicolorrow(cm, 0);
		numnewranges++;
		/* Update colors in newrow and create arcs as needed */
		subcoloronerow(v, newrow, lp, rp, lastsubcolor);
	}

	/* Ranges after target are unchanged */
	for (; oldrangen < cm->numcmranges; oldrange++, oldrangen++)
	{
		newranges[numnewranges++] = *oldrange;
	}

	/* Assert our original space estimate was adequate */
	assert(numnewranges <= (cm->numcmranges * 2 + 1));

	/* And finally, store back the updated list of ranges */
	if (cm->cmranges != NULL)
		FREE(cm->cmranges);
	cm->cmranges = newranges;
	cm->numcmranges = numnewranges;
}