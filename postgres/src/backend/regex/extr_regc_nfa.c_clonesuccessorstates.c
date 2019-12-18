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
struct state {int no; int nins; struct state* tmp; struct arc* outs; TYPE_2__* ins; } ;
struct nfa {TYPE_1__* v; } ;
struct arc {scalar_t__ type; scalar_t__ co; struct state* to; struct arc* outchain; } ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ co; struct state* from; } ;
struct TYPE_3__ {int /*<<< orphan*/  re; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (char*) ; 
 scalar_t__ MALLOC (int) ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 int NISERR () ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  REG_ETOOBIG ; 
 scalar_t__ STACK_TOO_DEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cparc (struct nfa*,struct arc*,struct state*,struct state*) ; 
 int /*<<< orphan*/  dropstate (struct nfa*,struct state*) ; 
 scalar_t__ hasconstraintout (struct state*) ; 
 scalar_t__ isconstraintarc (struct arc*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct state* newstate (struct nfa*) ; 

__attribute__((used)) static void
clonesuccessorstates(struct nfa *nfa,
					 struct state *ssource,
					 struct state *sclone,
					 struct state *spredecessor,
					 struct arc *refarc,
					 char *curdonemap,
					 char *outerdonemap,
					 int nstates)
{
	char	   *donemap;
	struct arc *a;

	/* Since this is recursive, it could be driven to stack overflow */
	if (STACK_TOO_DEEP(nfa->v->re))
	{
		NERR(REG_ETOOBIG);
		return;
	}

	/* If this state hasn't already got a donemap, create one */
	donemap = curdonemap;
	if (donemap == NULL)
	{
		donemap = (char *) MALLOC(nstates * sizeof(char));
		if (donemap == NULL)
		{
			NERR(REG_ESPACE);
			return;
		}

		if (outerdonemap != NULL)
		{
			/*
			 * Not at outermost recursion level, so copy the outer level's
			 * donemap; this ensures that we see states in process of being
			 * visited at outer levels, or already merged into predecessor
			 * states, as ones we shouldn't traverse back to.
			 */
			memcpy(donemap, outerdonemap, nstates * sizeof(char));
		}
		else
		{
			/* At outermost level, only spredecessor is off-limits */
			memset(donemap, 0, nstates * sizeof(char));
			assert(spredecessor->no < nstates);
			donemap[spredecessor->no] = 1;
		}
	}

	/* Mark ssource as visited in the donemap */
	assert(ssource->no < nstates);
	assert(donemap[ssource->no] == 0);
	donemap[ssource->no] = 1;

	/*
	 * We proceed by first cloning all of ssource's outarcs, creating new
	 * clone states as needed but not doing more with them than that.  Then in
	 * a second pass, recurse to process the child clone states.  This allows
	 * us to have only one child clone state per reachable source state, even
	 * when there are multiple outarcs leading to the same state.  Also, when
	 * we do visit a child state, its set of inarcs is known exactly, which
	 * makes it safe to apply the constraint-is-already-checked optimization.
	 * Also, this ensures that we've merged all the states we can into the
	 * current clone before we recurse to any children, thus possibly saving
	 * them from making extra images of those states.
	 *
	 * While this function runs, child clone states of the current state are
	 * marked by setting their tmp fields to point to the original state they
	 * were cloned from.  This makes it possible to detect multiple outarcs
	 * leading to the same state, and also makes it easy to distinguish clone
	 * states from original states (which will have tmp == NULL).
	 */
	for (a = ssource->outs; a != NULL && !NISERR(); a = a->outchain)
	{
		struct state *sto = a->to;

		/*
		 * We do not consider cloning successor states that have no constraint
		 * outarcs; just link to them as-is.  They cannot be part of a
		 * constraint loop so there is no need to make copies.  In particular,
		 * this rule keeps us from trying to clone the post state, which would
		 * be a bad idea.
		 */
		if (isconstraintarc(a) && hasconstraintout(sto))
		{
			struct state *prevclone;
			int			canmerge;
			struct arc *a2;

			/*
			 * Back-link constraint arcs must not be followed.  Nor is there a
			 * need to revisit states previously merged into this clone.
			 */
			assert(sto->no < nstates);
			if (donemap[sto->no] != 0)
				continue;

			/*
			 * Check whether we already have a child clone state for this
			 * source state.
			 */
			prevclone = NULL;
			for (a2 = sclone->outs; a2 != NULL; a2 = a2->outchain)
			{
				if (a2->to->tmp == sto)
				{
					prevclone = a2->to;
					break;
				}
			}

			/*
			 * If this arc is labeled the same as refarc, or the same as any
			 * arc we must have traversed to get to sclone, then no additional
			 * constraints need to be met to get to sto, so we should just
			 * merge its outarcs into sclone.
			 */
			if (refarc && a->type == refarc->type && a->co == refarc->co)
				canmerge = 1;
			else
			{
				struct state *s;

				canmerge = 0;
				for (s = sclone; s->ins; s = s->ins->from)
				{
					if (s->nins == 1 &&
						a->type == s->ins->type && a->co == s->ins->co)
					{
						canmerge = 1;
						break;
					}
				}
			}

			if (canmerge)
			{
				/*
				 * We can merge into sclone.  If we previously made a child
				 * clone state, drop it; there's no need to visit it.  (This
				 * can happen if ssource has multiple pathways to sto, and we
				 * only just now found one that is provably a no-op.)
				 */
				if (prevclone)
					dropstate(nfa, prevclone);	/* kills our outarc, too */

				/* Recurse to merge sto's outarcs into sclone */
				clonesuccessorstates(nfa,
									 sto,
									 sclone,
									 spredecessor,
									 refarc,
									 donemap,
									 outerdonemap,
									 nstates);
				/* sto should now be marked as previously visited */
				assert(NISERR() || donemap[sto->no] == 1);
			}
			else if (prevclone)
			{
				/*
				 * We already have a clone state for this successor, so just
				 * make another arc to it.
				 */
				cparc(nfa, a, sclone, prevclone);
			}
			else
			{
				/*
				 * We need to create a new successor clone state.
				 */
				struct state *stoclone;

				stoclone = newstate(nfa);
				if (stoclone == NULL)
				{
					assert(NISERR());
					break;
				}
				/* Mark it as to what it's a clone of */
				stoclone->tmp = sto;
				/* ... and add the outarc leading to it */
				cparc(nfa, a, sclone, stoclone);
			}
		}
		else
		{
			/*
			 * Non-constraint outarcs just get copied to sclone, as do outarcs
			 * leading to states with no constraint outarc.
			 */
			cparc(nfa, a, sclone, sto);
		}
	}

	/*
	 * If we are at outer level for this clone state, recurse to all its child
	 * clone states, clearing their tmp fields as we go.  (If we're not
	 * outermost for sclone, leave this to be done by the outer call level.)
	 * Note that if we have multiple outarcs leading to the same clone state,
	 * it will only be recursed-to once.
	 */
	if (curdonemap == NULL)
	{
		for (a = sclone->outs; a != NULL && !NISERR(); a = a->outchain)
		{
			struct state *stoclone = a->to;
			struct state *sto = stoclone->tmp;

			if (sto != NULL)
			{
				stoclone->tmp = NULL;
				clonesuccessorstates(nfa,
									 sto,
									 stoclone,
									 spredecessor,
									 refarc,
									 NULL,
									 donemap,
									 nstates);
			}
		}

		/* Don't forget to free sclone's donemap when done with it */
		FREE(donemap);
	}
}