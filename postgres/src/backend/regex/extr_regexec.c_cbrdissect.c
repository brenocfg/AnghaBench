#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vars {size_t nmatch; TYPE_2__* g; TYPE_1__* pmatch; int /*<<< orphan*/ * start; } ;
struct subre {int subno; int min; int max; char op; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_4__ {scalar_t__ (* compare ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ;} ;
struct TYPE_3__ {int rm_so; size_t rm_eo; } ;

/* Variables and functions */
 int DUPINF ; 
 int /*<<< orphan*/  MDEBUG (char*) ; 
 int REG_NOMATCH ; 
 int REG_OKAY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int						/* regexec return code */
cbrdissect(struct vars *v,
		   struct subre *t,
		   chr *begin,			/* beginning of relevant substring */
		   chr *end)			/* end of same */
{
	int			n = t->subno;
	size_t		numreps;
	size_t		tlen;
	size_t		brlen;
	chr		   *brstring;
	chr		   *p;
	int			min = t->min;
	int			max = t->max;

	assert(t != NULL);
	assert(t->op == 'b');
	assert(n >= 0);
	assert((size_t) n < v->nmatch);

	MDEBUG(("cbackref n%d %d{%d-%d}\n", t->id, n, min, max));

	/* get the backreferenced string */
	if (v->pmatch[n].rm_so == -1)
		return REG_NOMATCH;
	brstring = v->start + v->pmatch[n].rm_so;
	brlen = v->pmatch[n].rm_eo - v->pmatch[n].rm_so;

	/* special cases for zero-length strings */
	if (brlen == 0)
	{
		/*
		 * matches only if target is zero length, but any number of
		 * repetitions can be considered to be present
		 */
		if (begin == end && min <= max)
		{
			MDEBUG(("cbackref matched trivially\n"));
			return REG_OKAY;
		}
		return REG_NOMATCH;
	}
	if (begin == end)
	{
		/* matches only if zero repetitions are okay */
		if (min == 0)
		{
			MDEBUG(("cbackref matched trivially\n"));
			return REG_OKAY;
		}
		return REG_NOMATCH;
	}

	/*
	 * check target length to see if it could possibly be an allowed number of
	 * repetitions of brstring
	 */
	assert(end > begin);
	tlen = end - begin;
	if (tlen % brlen != 0)
		return REG_NOMATCH;
	numreps = tlen / brlen;
	if (numreps < min || (numreps > max && max != DUPINF))
		return REG_NOMATCH;

	/* okay, compare the actual string contents */
	p = begin;
	while (numreps-- > 0)
	{
		if ((*v->g->compare) (brstring, p, brlen) != 0)
			return REG_NOMATCH;
		p += brlen;
	}

	MDEBUG(("cbackref matched\n"));
	return REG_OKAY;
}