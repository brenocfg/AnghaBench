#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vars {int eflags; scalar_t__* stop; scalar_t__* start; } ;
struct sset {int flags; scalar_t__* lastseen; struct sset** outs; } ;
struct dfa {TYPE_1__* cnfa; struct sset* ssets; struct colormap* cm; } ;
struct colormap {int dummy; } ;
typedef  size_t color ;
typedef  scalar_t__ chr ;
struct TYPE_2__ {size_t* bos; size_t* eos; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDEBUG (char*) ; 
 size_t GETCOLOR (struct colormap*,scalar_t__) ; 
 int POSTSTATE ; 
 int REG_FTRACE ; 
 int REG_NOTBOL ; 
 int REG_NOTEOL ; 
 int /*<<< orphan*/  assert (int) ; 
 struct sset* initialize (struct vars*,struct dfa*,scalar_t__*) ; 
 scalar_t__* lastcold (struct vars*,struct dfa*) ; 
 struct sset* miss (struct vars*,struct dfa*,struct sset*,size_t,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static chr *
shortest(struct vars *v,
		 struct dfa *d,
		 chr *start,			/* where the match should start */
		 chr *min,				/* match must end at or after here */
		 chr *max,				/* match must end at or before here */
		 chr **coldp,			/* store coldstart pointer here, if non-NULL */
		 int *hitstopp)			/* record whether hit v->stop, if non-NULL */
{
	chr		   *cp;
	chr		   *realmin = (min == v->stop) ? min : min + 1;
	chr		   *realmax = (max == v->stop) ? max : max + 1;
	color		co;
	struct sset *css;
	struct sset *ss;
	struct colormap *cm = d->cm;

	/* prevent "uninitialized variable" warnings */
	if (coldp != NULL)
		*coldp = NULL;
	if (hitstopp != NULL)
		*hitstopp = 0;

	/* initialize */
	css = initialize(v, d, start);
	if (css == NULL)
		return NULL;
	cp = start;

	/* startup */
	FDEBUG(("--- startup ---\n"));
	if (cp == v->start)
	{
		co = d->cnfa->bos[(v->eflags & REG_NOTBOL) ? 0 : 1];
		FDEBUG(("color %ld\n", (long) co));
	}
	else
	{
		co = GETCOLOR(cm, *(cp - 1));
		FDEBUG(("char %c, color %ld\n", (char) *(cp - 1), (long) co));
	}
	css = miss(v, d, css, co, cp, start);
	if (css == NULL)
		return NULL;
	css->lastseen = cp;
	ss = css;

	/*
	 * This is the main text-scanning loop.  It seems worth having two copies
	 * to avoid the overhead of REG_FTRACE tests here, even in REG_DEBUG
	 * builds, when you're not actively tracing.
	 */
#ifdef REG_DEBUG
	if (v->eflags & REG_FTRACE)
	{
		while (cp < realmax)
		{
			FDEBUG(("--- at c%d ---\n", (int) (css - d->ssets)));
			co = GETCOLOR(cm, *cp);
			FDEBUG(("char %c, color %ld\n", (char) *cp, (long) co));
			ss = css->outs[co];
			if (ss == NULL)
			{
				ss = miss(v, d, css, co, cp + 1, start);
				if (ss == NULL)
					break;		/* NOTE BREAK OUT */
			}
			cp++;
			ss->lastseen = cp;
			css = ss;
			if ((ss->flags & POSTSTATE) && cp >= realmin)
				break;			/* NOTE BREAK OUT */
		}
	}
	else
#endif
	{
		while (cp < realmax)
		{
			co = GETCOLOR(cm, *cp);
			ss = css->outs[co];
			if (ss == NULL)
			{
				ss = miss(v, d, css, co, cp + 1, start);
				if (ss == NULL)
					break;		/* NOTE BREAK OUT */
			}
			cp++;
			ss->lastseen = cp;
			css = ss;
			if ((ss->flags & POSTSTATE) && cp >= realmin)
				break;			/* NOTE BREAK OUT */
		}
	}

	if (ss == NULL)
		return NULL;

	if (coldp != NULL)			/* report last no-progress state set, if any */
		*coldp = lastcold(v, d);

	if ((ss->flags & POSTSTATE) && cp > min)
	{
		assert(cp >= realmin);
		cp--;
	}
	else if (cp == v->stop && max == v->stop)
	{
		co = d->cnfa->eos[(v->eflags & REG_NOTEOL) ? 0 : 1];
		FDEBUG(("color %ld\n", (long) co));
		ss = miss(v, d, css, co, cp, start);
		/* match might have ended at eol */
		if ((ss == NULL || !(ss->flags & POSTSTATE)) && hitstopp != NULL)
			*hitstopp = 1;
	}

	if (ss == NULL || !(ss->flags & POSTSTATE))
		return NULL;

	return cp;
}