#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vars {int nmatch; int err; TYPE_3__* g; TYPE_4__* pmatch; int /*<<< orphan*/ * stop; TYPE_2__* details; int /*<<< orphan*/  dfa1; int /*<<< orphan*/ * search_start; int /*<<< orphan*/ * start; } ;
struct dfa {int dummy; } ;
struct colormap {int dummy; } ;
struct cnfa {int dummy; } ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {void* rm_eo; void* rm_so; } ;
struct TYPE_8__ {int cflags; TYPE_5__* tree; struct cnfa search; } ;
struct TYPE_6__ {void* rm_eo; void* rm_so; } ;
struct TYPE_7__ {TYPE_1__ rm_extend; } ;

/* Variables and functions */
 scalar_t__ ISERR () ; 
 int /*<<< orphan*/  LOFF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDEBUG (char*) ; 
 int /*<<< orphan*/  NOERR () ; 
 void* OFF (int /*<<< orphan*/ *) ; 
 int REG_EXPECT ; 
 int REG_NOMATCH ; 
 int REG_OKAY ; 
 int SHORTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int cdissect (struct vars*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freedfa (struct dfa*) ; 
 int /*<<< orphan*/ * longest (struct vars*,struct dfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 struct dfa* newdfa (struct vars*,struct cnfa*,struct colormap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * shortest (struct vars*,struct dfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  zapallsubs (TYPE_4__*,int) ; 

__attribute__((used)) static int
find(struct vars *v,
	 struct cnfa *cnfa,
	 struct colormap *cm)
{
	struct dfa *s;
	struct dfa *d;
	chr		   *begin;
	chr		   *end = NULL;
	chr		   *cold;
	chr		   *open;			/* open and close of range of possible starts */
	chr		   *close;
	int			hitend;
	int			shorter = (v->g->tree->flags & SHORTER) ? 1 : 0;

	/* first, a shot with the search RE */
	s = newdfa(v, &v->g->search, cm, &v->dfa1);
	assert(!(ISERR() && s != NULL));
	NOERR();
	MDEBUG(("\nsearch at %ld\n", LOFF(v->start)));
	cold = NULL;
	close = shortest(v, s, v->search_start, v->search_start, v->stop,
					 &cold, (int *) NULL);
	freedfa(s);
	NOERR();
	if (v->g->cflags & REG_EXPECT)
	{
		assert(v->details != NULL);
		if (cold != NULL)
			v->details->rm_extend.rm_so = OFF(cold);
		else
			v->details->rm_extend.rm_so = OFF(v->stop);
		v->details->rm_extend.rm_eo = OFF(v->stop); /* unknown */
	}
	if (close == NULL)			/* not found */
		return REG_NOMATCH;
	if (v->nmatch == 0)			/* found, don't need exact location */
		return REG_OKAY;

	/* find starting point and match */
	assert(cold != NULL);
	open = cold;
	cold = NULL;
	MDEBUG(("between %ld and %ld\n", LOFF(open), LOFF(close)));
	d = newdfa(v, cnfa, cm, &v->dfa1);
	assert(!(ISERR() && d != NULL));
	NOERR();
	for (begin = open; begin <= close; begin++)
	{
		MDEBUG(("\nfind trying at %ld\n", LOFF(begin)));
		if (shorter)
			end = shortest(v, d, begin, begin, v->stop,
						   (chr **) NULL, &hitend);
		else
			end = longest(v, d, begin, v->stop, &hitend);
		if (ISERR())
		{
			freedfa(d);
			return v->err;
		}
		if (hitend && cold == NULL)
			cold = begin;
		if (end != NULL)
			break;				/* NOTE BREAK OUT */
	}
	assert(end != NULL);		/* search RE succeeded so loop should */
	freedfa(d);

	/* and pin down details */
	assert(v->nmatch > 0);
	v->pmatch[0].rm_so = OFF(begin);
	v->pmatch[0].rm_eo = OFF(end);
	if (v->g->cflags & REG_EXPECT)
	{
		if (cold != NULL)
			v->details->rm_extend.rm_so = OFF(cold);
		else
			v->details->rm_extend.rm_so = OFF(v->stop);
		v->details->rm_extend.rm_eo = OFF(v->stop); /* unknown */
	}
	if (v->nmatch == 1)			/* no need for submatches */
		return REG_OKAY;

	/* find submatches */
	zapallsubs(v->pmatch, v->nmatch);
	return cdissect(v, v->g->tree, begin, end);
}