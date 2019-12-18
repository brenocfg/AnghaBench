#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct state {scalar_t__ nouts; scalar_t__ nins; int /*<<< orphan*/  flag; int /*<<< orphan*/ * tmp; struct state* next; struct arc* outs; } ;
struct nfa {struct state* states; } ;
struct arc {struct state* to; struct arc* outchain; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ NISERR () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dropstate (struct nfa*,struct state*) ; 
 int /*<<< orphan*/  dumpnfa (struct nfa*,int /*<<< orphan*/ *) ; 
 scalar_t__ findconstraintloop (struct nfa*,struct state*) ; 
 int /*<<< orphan*/  freearc (struct nfa*,struct arc*) ; 
 scalar_t__ isconstraintarc (struct arc*) ; 

__attribute__((used)) static void
fixconstraintloops(struct nfa *nfa,
				   FILE *f)		/* for debug output; NULL none */
{
	struct state *s;
	struct state *nexts;
	struct arc *a;
	struct arc *nexta;
	int			hasconstraints;

	/*
	 * In the trivial case of a state that loops to itself, we can just drop
	 * the constraint arc altogether.  This is worth special-casing because
	 * such loops are far more common than loops containing multiple states.
	 * While we're at it, note whether any constraint arcs survive.
	 */
	hasconstraints = 0;
	for (s = nfa->states; s != NULL && !NISERR(); s = nexts)
	{
		nexts = s->next;
		/* while we're at it, ensure tmp fields are clear for next step */
		assert(s->tmp == NULL);
		for (a = s->outs; a != NULL && !NISERR(); a = nexta)
		{
			nexta = a->outchain;
			if (isconstraintarc(a))
			{
				if (a->to == s)
					freearc(nfa, a);
				else
					hasconstraints = 1;
			}
		}
		/* If we removed all the outarcs, the state is useless. */
		if (s->nouts == 0 && !s->flag)
			dropstate(nfa, s);
	}

	/* Nothing to do if no remaining constraint arcs */
	if (NISERR() || !hasconstraints)
		return;

	/*
	 * Starting from each remaining NFA state, search outwards for a
	 * constraint loop.  If we find a loop, break the loop, then start the
	 * search over.  (We could possibly retain some state from the first scan,
	 * but it would complicate things greatly, and multi-state constraint
	 * loops are rare enough that it's not worth optimizing the case.)
	 */
restart:
	for (s = nfa->states; s != NULL && !NISERR(); s = s->next)
	{
		if (findconstraintloop(nfa, s))
			goto restart;
	}

	if (NISERR())
		return;

	/*
	 * Now remove any states that have become useless.  (This cleanup is not
	 * very thorough, and would be even less so if we tried to combine it with
	 * the previous step; but cleanup() will take care of anything we miss.)
	 *
	 * Because findconstraintloop intentionally doesn't reset all tmp fields,
	 * we have to clear them after it's done.  This is a convenient place to
	 * do that, too.
	 */
	for (s = nfa->states; s != NULL; s = nexts)
	{
		nexts = s->next;
		s->tmp = NULL;
		if ((s->nins == 0 || s->nouts == 0) && !s->flag)
			dropstate(nfa, s);
	}

	if (f != NULL)
		dumpnfa(nfa, f);
}