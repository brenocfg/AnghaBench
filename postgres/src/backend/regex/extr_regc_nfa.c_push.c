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
struct state {scalar_t__ nouts; int nins; struct state* tmp; struct arc* outs; struct arc* ins; scalar_t__ flag; } ;
struct nfa {int dummy; } ;
struct arc {struct state* to; struct state* from; struct arc* outchain; } ;

/* Variables and functions */
#define  COMPATIBLE 130 
#define  INCOMPATIBLE 129 
 scalar_t__ NISERR () ; 
 int NOTREACHED ; 
#define  SATISFIED 128 
 int /*<<< orphan*/  assert (int) ; 
 int combine (struct arc*,struct arc*) ; 
 int /*<<< orphan*/  copyouts (struct nfa*,struct state*,struct state*) ; 
 int /*<<< orphan*/  cparc (struct nfa*,struct arc*,struct state*,struct state*) ; 
 int /*<<< orphan*/  freearc (struct nfa*,struct arc*) ; 
 int /*<<< orphan*/  moveouts (struct nfa*,struct state*,struct state*) ; 
 struct state* newstate (struct nfa*) ; 

__attribute__((used)) static int
push(struct nfa *nfa,
	 struct arc *con,
	 struct state **intermediates)
{
	struct state *from = con->from;
	struct state *to = con->to;
	struct arc *a;
	struct arc *nexta;
	struct state *s;

	assert(to != from);			/* should have gotten rid of this earlier */
	if (to->flag)				/* can't push forward beyond end */
		return 0;
	if (to->nouts == 0)
	{							/* dead end */
		freearc(nfa, con);
		return 1;
	}

	/*
	 * First, clone to state if necessary to avoid other inarcs.  This may
	 * seem wasteful, but it simplifies the logic, and we'll get rid of the
	 * clone state again at the bottom.
	 */
	if (to->nins > 1)
	{
		s = newstate(nfa);
		if (NISERR())
			return 0;
		copyouts(nfa, to, s);	/* duplicate outarcs */
		cparc(nfa, con, from, s);	/* move constraint arc */
		freearc(nfa, con);
		if (NISERR())
			return 0;
		to = s;
		con = to->ins;
	}
	assert(to->nins == 1);

	/* propagate the constraint into the to state's outarcs */
	for (a = to->outs; a != NULL && !NISERR(); a = nexta)
	{
		nexta = a->outchain;
		switch (combine(con, a))
		{
			case INCOMPATIBLE:	/* destroy the arc */
				freearc(nfa, a);
				break;
			case SATISFIED:		/* no action needed */
				break;
			case COMPATIBLE:	/* swap the two arcs, more or less */
				/* need an intermediate state, but might have one already */
				for (s = *intermediates; s != NULL; s = s->tmp)
				{
					assert(s->nins > 0 && s->nouts > 0);
					if (s->ins->from == from && s->outs->to == a->to)
						break;
				}
				if (s == NULL)
				{
					s = newstate(nfa);
					if (NISERR())
						return 0;
					s->tmp = *intermediates;
					*intermediates = s;
				}
				cparc(nfa, con, s, a->to);
				cparc(nfa, a, from, s);
				freearc(nfa, a);
				break;
			default:
				assert(NOTREACHED);
				break;
		}
	}

	/* remaining outarcs, if any, incorporate the constraint */
	moveouts(nfa, to, from);
	freearc(nfa, con);
	/* to state is now useless, but we leave it to pushfwd() to clean up */
	return 1;
}