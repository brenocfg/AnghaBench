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
struct state {struct arc* ins; } ;
struct nfa {TYPE_1__* v; } ;
struct arc {int /*<<< orphan*/  from; int /*<<< orphan*/  co; int /*<<< orphan*/  type; struct arc* inchain; } ;
struct TYPE_2__ {int /*<<< orphan*/  re; } ;

/* Variables and functions */
 scalar_t__ CANCEL_REQUESTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 scalar_t__ NISERR () ; 
 int /*<<< orphan*/  NOTREACHED ; 
 int /*<<< orphan*/  REG_CANCEL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  createarc (struct nfa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct state*) ; 
 int /*<<< orphan*/  qsort (struct arc**,int,int,int (*) (struct arc**,struct arc**)) ; 
 int /*<<< orphan*/  sortins (struct nfa*,struct state*) ; 
 int sortins_cmp (struct arc**,struct arc**) ; 

__attribute__((used)) static void
mergeins(struct nfa *nfa,
		 struct state *s,
		 struct arc **arcarray,
		 int arccount)
{
	struct arc *na;
	int			i;
	int			j;

	if (arccount <= 0)
		return;

	/*
	 * Because we bypass newarc() in this code path, we'd better include a
	 * cancel check.
	 */
	if (CANCEL_REQUESTED(nfa->v->re))
	{
		NERR(REG_CANCEL);
		return;
	}

	/* Sort existing inarcs as well as proposed new ones */
	sortins(nfa, s);
	if (NISERR())
		return;					/* might have failed to sort */

	qsort(arcarray, arccount, sizeof(struct arc *), sortins_cmp);

	/*
	 * arcarray very likely includes dups, so we must eliminate them.  (This
	 * could be folded into the next loop, but it's not worth the trouble.)
	 */
	j = 0;
	for (i = 1; i < arccount; i++)
	{
		switch (sortins_cmp(&arcarray[j], &arcarray[i]))
		{
			case -1:
				/* non-dup */
				arcarray[++j] = arcarray[i];
				break;
			case 0:
				/* dup */
				break;
			default:
				/* trouble */
				assert(NOTREACHED);
		}
	}
	arccount = j + 1;

	/*
	 * Now merge into s' inchain.  Note that createarc() will put new arcs
	 * onto the front of s's chain, so it does not break our walk through the
	 * sorted part of the chain.
	 */
	i = 0;
	na = s->ins;
	while (i < arccount && na != NULL)
	{
		struct arc *a = arcarray[i];

		switch (sortins_cmp(&a, &na))
		{
			case -1:
				/* s does not have anything matching a */
				createarc(nfa, a->type, a->co, a->from, s);
				i++;
				break;
			case 0:
				/* match, advance in both lists */
				i++;
				na = na->inchain;
				break;
			case +1:
				/* advance only na; array might have a match later */
				na = na->inchain;
				break;
			default:
				assert(NOTREACHED);
		}
	}
	while (i < arccount)
	{
		/* s does not have anything matching a */
		struct arc *a = arcarray[i];

		createarc(nfa, a->type, a->co, a->from, s);
		i++;
	}
}