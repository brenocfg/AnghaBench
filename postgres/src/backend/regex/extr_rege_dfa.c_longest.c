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
struct dfa {int nssused; struct sset* ssets; scalar_t__* lastpost; TYPE_1__* cnfa; struct colormap* cm; } ;
struct colormap {int dummy; } ;
typedef  size_t color ;
typedef  scalar_t__ chr ;
struct TYPE_2__ {size_t* bos; size_t* eos; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDEBUG (char*) ; 
 size_t GETCOLOR (struct colormap*,scalar_t__) ; 
 scalar_t__ ISERR () ; 
 int POSTSTATE ; 
 int REG_FTRACE ; 
 int REG_NOTBOL ; 
 int REG_NOTEOL ; 
 struct sset* initialize (struct vars*,struct dfa*,scalar_t__*) ; 
 struct sset* miss (struct vars*,struct dfa*,struct sset*,size_t,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static chr *
longest(struct vars *v,
		struct dfa *d,
		chr *start,				/* where the match should start */
		chr *stop,				/* match must end at or before here */
		int *hitstopp)			/* record whether hit v->stop, if non-NULL */
{
	chr		   *cp;
	chr		   *realstop = (stop == v->stop) ? stop : stop + 1;
	color		co;
	struct sset *css;
	struct sset *ss;
	chr		   *post;
	int			i;
	struct colormap *cm = d->cm;

	/* prevent "uninitialized variable" warnings */
	if (hitstopp != NULL)
		*hitstopp = 0;

	/* initialize */
	css = initialize(v, d, start);
	if (css == NULL)
		return NULL;
	cp = start;

	/* startup */
	FDEBUG(("+++ startup +++\n"));
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

	/*
	 * This is the main text-scanning loop.  It seems worth having two copies
	 * to avoid the overhead of REG_FTRACE tests here, even in REG_DEBUG
	 * builds, when you're not actively tracing.
	 */
#ifdef REG_DEBUG
	if (v->eflags & REG_FTRACE)
	{
		while (cp < realstop)
		{
			FDEBUG(("+++ at c%d +++\n", (int) (css - d->ssets)));
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
		}
	}
	else
#endif
	{
		while (cp < realstop)
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
		}
	}

	if (ISERR())
		return NULL;

	/* shutdown */
	FDEBUG(("+++ shutdown at c%d +++\n", (int) (css - d->ssets)));
	if (cp == v->stop && stop == v->stop)
	{
		if (hitstopp != NULL)
			*hitstopp = 1;
		co = d->cnfa->eos[(v->eflags & REG_NOTEOL) ? 0 : 1];
		FDEBUG(("color %ld\n", (long) co));
		ss = miss(v, d, css, co, cp, start);
		if (ISERR())
			return NULL;
		/* special case:  match ended at eol? */
		if (ss != NULL && (ss->flags & POSTSTATE))
			return cp;
		else if (ss != NULL)
			ss->lastseen = cp;	/* to be tidy */
	}

	/* find last match, if any */
	post = d->lastpost;
	for (ss = d->ssets, i = d->nssused; i > 0; ss++, i--)
		if ((ss->flags & POSTSTATE) && post != ss->lastseen &&
			(post == NULL || post < ss->lastseen))
			post = ss->lastseen;
	if (post != NULL)			/* found one */
		return post - 1;

	return NULL;
}