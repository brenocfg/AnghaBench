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
struct state {struct arc* ins; int /*<<< orphan*/  nins; } ;
struct nfa {TYPE_1__* v; } ;
struct arc {int /*<<< orphan*/  from; int /*<<< orphan*/  co; int /*<<< orphan*/  type; struct arc* inchain; } ;
struct TYPE_2__ {int /*<<< orphan*/  re; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_ARC_OP_USE_SORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CANCEL_REQUESTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 scalar_t__ NISERR () ; 
 int NOTREACHED ; 
 int /*<<< orphan*/  REG_CANCEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cparc (struct nfa*,struct arc*,int /*<<< orphan*/ ,struct state*) ; 
 int /*<<< orphan*/  createarc (struct nfa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct state*) ; 
 int /*<<< orphan*/  sortins (struct nfa*,struct state*) ; 
 int sortins_cmp (struct arc**,struct arc**) ; 

__attribute__((used)) static void
copyins(struct nfa *nfa,
		struct state *oldState,
		struct state *newState)
{
	assert(oldState != newState);

	if (!BULK_ARC_OP_USE_SORT(oldState->nins, newState->nins))
	{
		/* With not too many arcs, just do them one at a time */
		struct arc *a;

		for (a = oldState->ins; a != NULL; a = a->inchain)
			cparc(nfa, a, a->from, newState);
	}
	else
	{
		/*
		 * With many arcs, use a sort-merge approach.  Note that createarc()
		 * will put new arcs onto the front of newState's chain, so it does
		 * not break our walk through the sorted part of the chain.
		 */
		struct arc *oa;
		struct arc *na;

		/*
		 * Because we bypass newarc() in this code path, we'd better include a
		 * cancel check.
		 */
		if (CANCEL_REQUESTED(nfa->v->re))
		{
			NERR(REG_CANCEL);
			return;
		}

		sortins(nfa, oldState);
		sortins(nfa, newState);
		if (NISERR())
			return;				/* might have failed to sort */
		oa = oldState->ins;
		na = newState->ins;
		while (oa != NULL && na != NULL)
		{
			struct arc *a = oa;

			switch (sortins_cmp(&oa, &na))
			{
				case -1:
					/* newState does not have anything matching oa */
					oa = oa->inchain;
					createarc(nfa, a->type, a->co, a->from, newState);
					break;
				case 0:
					/* match, advance in both lists */
					oa = oa->inchain;
					na = na->inchain;
					break;
				case +1:
					/* advance only na; oa might have a match later */
					na = na->inchain;
					break;
				default:
					assert(NOTREACHED);
			}
		}
		while (oa != NULL)
		{
			/* newState does not have anything matching oa */
			struct arc *a = oa;

			oa = oa->inchain;
			createarc(nfa, a->type, a->co, a->from, newState);
		}
	}
}