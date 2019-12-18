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
struct state {scalar_t__ nouts; struct arc* outs; } ;
struct nfa {TYPE_1__* v; } ;
struct arc {int /*<<< orphan*/  to; int /*<<< orphan*/  co; int /*<<< orphan*/  type; struct arc* outchain; } ;
struct TYPE_2__ {int /*<<< orphan*/  re; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_ARC_OP_USE_SORT (scalar_t__,scalar_t__) ; 
 scalar_t__ CANCEL_REQUESTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 scalar_t__ NISERR () ; 
 int NOTREACHED ; 
 int /*<<< orphan*/  REG_CANCEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cparc (struct nfa*,struct arc*,struct state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  createarc (struct nfa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freearc (struct nfa*,struct arc*) ; 
 int /*<<< orphan*/  sortouts (struct nfa*,struct state*) ; 
 int sortouts_cmp (struct arc**,struct arc**) ; 

__attribute__((used)) static void
moveouts(struct nfa *nfa,
		 struct state *oldState,
		 struct state *newState)
{
	assert(oldState != newState);

	if (!BULK_ARC_OP_USE_SORT(oldState->nouts, newState->nouts))
	{
		/* With not too many arcs, just do them one at a time */
		struct arc *a;

		while ((a = oldState->outs) != NULL)
		{
			cparc(nfa, a, newState, a->to);
			freearc(nfa, a);
		}
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

		sortouts(nfa, oldState);
		sortouts(nfa, newState);
		if (NISERR())
			return;				/* might have failed to sort */
		oa = oldState->outs;
		na = newState->outs;
		while (oa != NULL && na != NULL)
		{
			struct arc *a = oa;

			switch (sortouts_cmp(&oa, &na))
			{
				case -1:
					/* newState does not have anything matching oa */
					oa = oa->outchain;
					createarc(nfa, a->type, a->co, newState, a->to);
					freearc(nfa, a);
					break;
				case 0:
					/* match, advance in both lists */
					oa = oa->outchain;
					na = na->outchain;
					/* ... and drop duplicate arc from oldState */
					freearc(nfa, a);
					break;
				case +1:
					/* advance only na; oa might have a match later */
					na = na->outchain;
					break;
				default:
					assert(NOTREACHED);
			}
		}
		while (oa != NULL)
		{
			/* newState does not have anything matching oa */
			struct arc *a = oa;

			oa = oa->outchain;
			createarc(nfa, a->type, a->co, newState, a->to);
			freearc(nfa, a);
		}
	}

	assert(oldState->nouts == 0);
	assert(oldState->outs == NULL);
}