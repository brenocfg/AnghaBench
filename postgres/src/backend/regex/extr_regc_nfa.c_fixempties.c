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
struct state {int nouts; int nins; size_t no; scalar_t__ flag; struct state* next; struct arc* outs; struct arc* ins; struct state* tmp; } ;
struct nfa {int nstates; struct state* states; } ;
struct arc {scalar_t__ type; struct arc* outchain; struct arc* inchain; struct state* from; struct state* to; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EMPTY ; 
 int /*<<< orphan*/  FREE (struct arc**) ; 
 scalar_t__ MALLOC (int) ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 scalar_t__ NISERR () ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dropstate (struct nfa*,struct state*) ; 
 int /*<<< orphan*/  dumpnfa (struct nfa*,int /*<<< orphan*/ *) ; 
 struct state* emptyreachable (struct nfa*,struct state*,struct state*,struct arc**) ; 
 int /*<<< orphan*/  freearc (struct nfa*,struct arc*) ; 
 int /*<<< orphan*/  hasnonemptyout (struct state*) ; 
 int /*<<< orphan*/  mergeins (struct nfa*,struct state*,struct arc**,int) ; 
 int /*<<< orphan*/  moveins (struct nfa*,struct state*,struct state*) ; 
 int /*<<< orphan*/  moveouts (struct nfa*,struct state*,struct state*) ; 

__attribute__((used)) static void
fixempties(struct nfa *nfa,
		   FILE *f)				/* for debug output; NULL none */
{
	struct state *s;
	struct state *s2;
	struct state *nexts;
	struct arc *a;
	struct arc *nexta;
	int			totalinarcs;
	struct arc **inarcsorig;
	struct arc **arcarray;
	int			arccount;
	int			prevnins;
	int			nskip;

	/*
	 * First, get rid of any states whose sole out-arc is an EMPTY, since
	 * they're basically just aliases for their successor.  The parsing
	 * algorithm creates enough of these that it's worth special-casing this.
	 */
	for (s = nfa->states; s != NULL && !NISERR(); s = nexts)
	{
		nexts = s->next;
		if (s->flag || s->nouts != 1)
			continue;
		a = s->outs;
		assert(a != NULL && a->outchain == NULL);
		if (a->type != EMPTY)
			continue;
		if (s != a->to)
			moveins(nfa, s, a->to);
		dropstate(nfa, s);
	}

	/*
	 * Similarly, get rid of any state with a single EMPTY in-arc, by folding
	 * it into its predecessor.
	 */
	for (s = nfa->states; s != NULL && !NISERR(); s = nexts)
	{
		nexts = s->next;
		/* while we're at it, ensure tmp fields are clear for next step */
		assert(s->tmp == NULL);
		if (s->flag || s->nins != 1)
			continue;
		a = s->ins;
		assert(a != NULL && a->inchain == NULL);
		if (a->type != EMPTY)
			continue;
		if (s != a->from)
			moveouts(nfa, s, a->from);
		dropstate(nfa, s);
	}

	if (NISERR())
		return;

	/*
	 * For each remaining NFA state, find all other states from which it is
	 * reachable by a chain of one or more EMPTY arcs.  Then generate new arcs
	 * that eliminate the need for each such chain.
	 *
	 * We could replace a chain of EMPTY arcs that leads from a "from" state
	 * to a "to" state either by pushing non-EMPTY arcs forward (linking
	 * directly from "from"'s predecessors to "to") or by pulling them back
	 * (linking directly from "from" to "to"'s successors).  We choose to
	 * always do the former; this choice is somewhat arbitrary, but the
	 * approach below requires that we uniformly do one or the other.
	 *
	 * Suppose we have a chain of N successive EMPTY arcs (where N can easily
	 * approach the size of the NFA).  All of the intermediate states must
	 * have additional inarcs and outarcs, else they'd have been removed by
	 * the steps above.  Assuming their inarcs are mostly not empties, we will
	 * add O(N^2) arcs to the NFA, since a non-EMPTY inarc leading to any one
	 * state in the chain must be duplicated to lead to all its successor
	 * states as well.  So there is no hope of doing less than O(N^2) work;
	 * however, we should endeavor to keep the big-O cost from being even
	 * worse than that, which it can easily become without care.  In
	 * particular, suppose we were to copy all S1's inarcs forward to S2, and
	 * then also to S3, and then later we consider pushing S2's inarcs forward
	 * to S3.  If we include the arcs already copied from S1 in that, we'd be
	 * doing O(N^3) work.  (The duplicate-arc elimination built into newarc()
	 * and its cohorts would get rid of the extra arcs, but not without cost.)
	 *
	 * We can avoid this cost by treating only arcs that existed at the start
	 * of this phase as candidates to be pushed forward.  To identify those,
	 * we remember the first inarc each state had to start with.  We rely on
	 * the fact that newarc() and friends put new arcs on the front of their
	 * to-states' inchains, and that this phase never deletes arcs, so that
	 * the original arcs must be the last arcs in their to-states' inchains.
	 *
	 * So the process here is that, for each state in the NFA, we gather up
	 * all non-EMPTY inarcs of states that can reach the target state via
	 * EMPTY arcs.  We then sort, de-duplicate, and merge these arcs into the
	 * target state's inchain.  (We can safely use sort-merge for this as long
	 * as we update each state's original-arcs pointer after we add arcs to
	 * it; the sort step of mergeins probably changed the order of the old
	 * arcs.)
	 *
	 * Another refinement worth making is that, because we only add non-EMPTY
	 * arcs during this phase, and all added arcs have the same from-state as
	 * the non-EMPTY arc they were cloned from, we know ahead of time that any
	 * states having only EMPTY outarcs will be useless for lack of outarcs
	 * after we drop the EMPTY arcs.  (They cannot gain non-EMPTY outarcs if
	 * they had none to start with.)  So we need not bother to update the
	 * inchains of such states at all.
	 */

	/* Remember the states' first original inarcs */
	/* ... and while at it, count how many old inarcs there are altogether */
	inarcsorig = (struct arc **) MALLOC(nfa->nstates * sizeof(struct arc *));
	if (inarcsorig == NULL)
	{
		NERR(REG_ESPACE);
		return;
	}
	totalinarcs = 0;
	for (s = nfa->states; s != NULL; s = s->next)
	{
		inarcsorig[s->no] = s->ins;
		totalinarcs += s->nins;
	}

	/*
	 * Create a workspace for accumulating the inarcs to be added to the
	 * current target state.  totalinarcs is probably a considerable
	 * overestimate of the space needed, but the NFA is unlikely to be large
	 * enough at this point to make it worth being smarter.
	 */
	arcarray = (struct arc **) MALLOC(totalinarcs * sizeof(struct arc *));
	if (arcarray == NULL)
	{
		NERR(REG_ESPACE);
		FREE(inarcsorig);
		return;
	}

	/* And iterate over the target states */
	for (s = nfa->states; s != NULL && !NISERR(); s = s->next)
	{
		/* Ignore target states without non-EMPTY outarcs, per note above */
		if (!s->flag && !hasnonemptyout(s))
			continue;

		/* Find predecessor states and accumulate their original inarcs */
		arccount = 0;
		for (s2 = emptyreachable(nfa, s, s, inarcsorig); s2 != s; s2 = nexts)
		{
			/* Add s2's original inarcs to arcarray[], but ignore empties */
			for (a = inarcsorig[s2->no]; a != NULL; a = a->inchain)
			{
				if (a->type != EMPTY)
					arcarray[arccount++] = a;
			}

			/* Reset the tmp fields as we walk back */
			nexts = s2->tmp;
			s2->tmp = NULL;
		}
		s->tmp = NULL;
		assert(arccount <= totalinarcs);

		/* Remember how many original inarcs this state has */
		prevnins = s->nins;

		/* Add non-duplicate inarcs to target state */
		mergeins(nfa, s, arcarray, arccount);

		/* Now we must update the state's inarcsorig pointer */
		nskip = s->nins - prevnins;
		a = s->ins;
		while (nskip-- > 0)
			a = a->inchain;
		inarcsorig[s->no] = a;
	}

	FREE(arcarray);
	FREE(inarcsorig);

	if (NISERR())
		return;

	/*
	 * Now remove all the EMPTY arcs, since we don't need them anymore.
	 */
	for (s = nfa->states; s != NULL; s = s->next)
	{
		for (a = s->outs; a != NULL; a = nexta)
		{
			nexta = a->outchain;
			if (a->type == EMPTY)
				freearc(nfa, a);
		}
	}

	/*
	 * And remove any states that have become useless.  (This cleanup is not
	 * very thorough, and would be even less so if we tried to combine it with
	 * the previous step; but cleanup() will take care of anything we miss.)
	 */
	for (s = nfa->states; s != NULL; s = nexts)
	{
		nexts = s->next;
		if ((s->nins == 0 || s->nouts == 0) && !s->flag)
			dropstate(nfa, s);
	}

	if (f != NULL)
		dumpnfa(nfa, f);
}