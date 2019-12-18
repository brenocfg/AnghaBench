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
struct vars {int eflags; scalar_t__* start; scalar_t__* stop; } ;
struct sset {int flags; struct sset** outs; scalar_t__* lastseen; } ;
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
 struct sset* miss (struct vars*,struct dfa*,struct sset*,size_t,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
matchuntil(struct vars *v,
		   struct dfa *d,
		   chr *probe,			/* we want to know if a match ends here */
		   struct sset **lastcss,	/* state storage across calls */
		   chr **lastcp)		/* state storage across calls */
{
	chr		   *cp = *lastcp;
	color		co;
	struct sset *css = *lastcss;
	struct sset *ss;
	struct colormap *cm = d->cm;

	/* initialize and startup, or restart, if necessary */
	if (cp == NULL || cp > probe)
	{
		cp = v->start;
		css = initialize(v, d, cp);
		if (css == NULL)
			return 0;

		FDEBUG((">>> startup >>>\n"));
		co = d->cnfa->bos[(v->eflags & REG_NOTBOL) ? 0 : 1];
		FDEBUG(("color %ld\n", (long) co));

		css = miss(v, d, css, co, cp, v->start);
		if (css == NULL)
			return 0;
		css->lastseen = cp;
	}
	else if (css == NULL)
	{
		/* we previously found that no match is possible beyond *lastcp */
		return 0;
	}
	ss = css;

	/*
	 * This is the main text-scanning loop.  It seems worth having two copies
	 * to avoid the overhead of REG_FTRACE tests here, even in REG_DEBUG
	 * builds, when you're not actively tracing.
	 */
#ifdef REG_DEBUG
	if (v->eflags & REG_FTRACE)
	{
		while (cp < probe)
		{
			FDEBUG((">>> at c%d >>>\n", (int) (css - d->ssets)));
			co = GETCOLOR(cm, *cp);
			FDEBUG(("char %c, color %ld\n", (char) *cp, (long) co));
			ss = css->outs[co];
			if (ss == NULL)
			{
				ss = miss(v, d, css, co, cp + 1, v->start);
				if (ss == NULL)
					break;		/* NOTE BREAK OUT */
			}
			cp++;
			ss->lastseen = cp;
			css = ss;
		}
	}
	else
#endif
	{
		while (cp < probe)
		{
			co = GETCOLOR(cm, *cp);
			ss = css->outs[co];
			if (ss == NULL)
			{
				ss = miss(v, d, css, co, cp + 1, v->start);
				if (ss == NULL)
					break;		/* NOTE BREAK OUT */
			}
			cp++;
			ss->lastseen = cp;
			css = ss;
		}
	}

	*lastcss = ss;
	*lastcp = cp;

	if (ss == NULL)
		return 0;				/* impossible match, or internal error */

	/* We need to process one more chr, or the EOS symbol, to check match */
	if (cp < v->stop)
	{
		FDEBUG((">>> at c%d >>>\n", (int) (css - d->ssets)));
		co = GETCOLOR(cm, *cp);
		FDEBUG(("char %c, color %ld\n", (char) *cp, (long) co));
		ss = css->outs[co];
		if (ss == NULL)
			ss = miss(v, d, css, co, cp + 1, v->start);
	}
	else
	{
		assert(cp == v->stop);
		co = d->cnfa->eos[(v->eflags & REG_NOTEOL) ? 0 : 1];
		FDEBUG(("color %ld\n", (long) co));
		ss = miss(v, d, css, co, cp, v->start);
	}

	if (ss == NULL || !(ss->flags & POSTSTATE))
		return 0;

	return 1;
}