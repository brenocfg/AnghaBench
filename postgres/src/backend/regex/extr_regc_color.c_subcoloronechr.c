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
struct vars {int /*<<< orphan*/  nfa; struct colormap* cm; } ;
struct state {int dummy; } ;
struct colormap {int numcmranges; TYPE_1__* cmranges; } ;
struct TYPE_3__ {scalar_t__ cmax; scalar_t__ cmin; int rownum; } ;
typedef  TYPE_1__ colormaprange ;
typedef  scalar_t__ color ;
typedef  scalar_t__ chr ;

/* Variables and functions */
 int /*<<< orphan*/  CERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 scalar_t__ MALLOC (int) ; 
 scalar_t__ MAX_SIMPLE_CHR ; 
 int /*<<< orphan*/  NOERR () ; 
 int /*<<< orphan*/  PLAIN ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  newarc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct state*,struct state*) ; 
 void* newhicolorrow (struct colormap*,int) ; 
 scalar_t__ subcolor (struct colormap*,scalar_t__) ; 
 int /*<<< orphan*/  subcoloronerow (struct vars*,int,struct state*,struct state*,scalar_t__*) ; 

__attribute__((used)) static void
subcoloronechr(struct vars *v,
			   chr ch,
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

	/* Easy case for low chr codes */
	if (ch <= MAX_SIMPLE_CHR)
	{
		color		sco = subcolor(cm, ch);

		NOERR();
		if (sco != *lastsubcolor)
		{
			newarc(v->nfa, PLAIN, sco, lp, rp);
			*lastsubcolor = sco;
		}
		return;
	}

	/*
	 * Potentially, we could need two more colormapranges than we have now, if
	 * the given chr is in the middle of some existing range.
	 */
	newranges = (colormaprange *)
		MALLOC((cm->numcmranges + 2) * sizeof(colormaprange));
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
		if (oldrange->cmax >= ch)
			break;
		newranges[numnewranges++] = *oldrange;
	}

	/* Match target chr against current range */
	if (oldrangen >= cm->numcmranges || oldrange->cmin > ch)
	{
		/* chr does not belong to any existing range, make a new one */
		newranges[numnewranges].cmin = ch;
		newranges[numnewranges].cmax = ch;
		/* row state should be cloned from the "all others" row */
		newranges[numnewranges].rownum = newrow = newhicolorrow(cm, 0);
		numnewranges++;
	}
	else if (oldrange->cmin == oldrange->cmax)
	{
		/* we have an existing singleton range matching the chr */
		newranges[numnewranges++] = *oldrange;
		newrow = oldrange->rownum;
		/* we've now fully processed this old range */
		oldrange++, oldrangen++;
	}
	else
	{
		/* chr is a subset of this existing range, must split it */
		if (ch > oldrange->cmin)
		{
			/* emit portion of old range before chr */
			newranges[numnewranges].cmin = oldrange->cmin;
			newranges[numnewranges].cmax = ch - 1;
			newranges[numnewranges].rownum = oldrange->rownum;
			numnewranges++;
		}
		/* emit chr as singleton range, initially cloning from range */
		newranges[numnewranges].cmin = ch;
		newranges[numnewranges].cmax = ch;
		newranges[numnewranges].rownum = newrow =
			newhicolorrow(cm, oldrange->rownum);
		numnewranges++;
		if (ch < oldrange->cmax)
		{
			/* emit portion of old range after chr */
			newranges[numnewranges].cmin = ch + 1;
			newranges[numnewranges].cmax = oldrange->cmax;
			/* must clone the row if we are making two new ranges from old */
			newranges[numnewranges].rownum =
				(ch > oldrange->cmin) ? newhicolorrow(cm, oldrange->rownum) :
				oldrange->rownum;
			numnewranges++;
		}
		/* we've now fully processed this old range */
		oldrange++, oldrangen++;
	}

	/* Update colors in newrow and create arcs as needed */
	subcoloronerow(v, newrow, lp, rp, lastsubcolor);

	/* Ranges after target are unchanged */
	for (; oldrangen < cm->numcmranges; oldrange++, oldrangen++)
	{
		newranges[numnewranges++] = *oldrange;
	}

	/* Assert our original space estimate was adequate */
	assert(numnewranges <= (cm->numcmranges + 2));

	/* And finally, store back the updated list of ranges */
	if (cm->cmranges != NULL)
		FREE(cm->cmranges);
	cm->cmranges = newranges;
	cm->numcmranges = numnewranges;
}