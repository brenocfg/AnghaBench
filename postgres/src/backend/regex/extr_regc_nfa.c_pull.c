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
struct state {scalar_t__ nins; int nouts; struct state* tmp; struct arc* outs; struct arc* ins; scalar_t__ flag; } ;
struct nfa {int dummy; } ;
struct arc {struct state* from; struct state* to; struct arc* inchain; } ;

/* Variables and functions */
#define  COMPATIBLE 130 
#define  INCOMPATIBLE 129 
 scalar_t__ NISERR () ; 
 int NOTREACHED ; 
#define  SATISFIED 128 
 int /*<<< orphan*/  assert (int) ; 
 int combine (struct arc*,struct arc*) ; 
 int /*<<< orphan*/  copyins (struct nfa*,struct state*,struct state*) ; 
 int /*<<< orphan*/  cparc (struct nfa*,struct arc*,struct state*,struct state*) ; 
 int /*<<< orphan*/  freearc (struct nfa*,struct arc*) ; 
 int /*<<< orphan*/  moveins (struct nfa*,struct state*,struct state*) ; 
 struct state* newstate (struct nfa*) ; 

__attribute__((used)) static int
pull(struct nfa *nfa,
	 struct arc *con,
	 struct state **intermediates)
{
	struct state *from = con->from;
	struct state *to = con->to;
	struct arc *a;
	struct arc *nexta;
	struct state *s;

	assert(from != to);			/* should have gotten rid of this earlier */
	if (from->flag)				/* can't pull back beyond start */
		return 0;
	if (from->nins == 0)
	{							/* unreachable */
		freearc(nfa, con);
		return 1;
	}

	/*
	 * First, clone from state if necessary to avoid other outarcs.  This may
	 * seem wasteful, but it simplifies the logic, and we'll get rid of the
	 * clone state again at the bottom.
	 */
	if (from->nouts > 1)
	{
		s = newstate(nfa);
		if (NISERR())
			return 0;
		copyins(nfa, from, s);	/* duplicate inarcs */
		cparc(nfa, con, s, to); /* move constraint arc */
		freearc(nfa, con);
		if (NISERR())
			return 0;
		from = s;
		con = from->outs;
	}
	assert(from->nouts == 1);

	/* propagate the constraint into the from state's inarcs */
	for (a = from->ins; a != NULL && !NISERR(); a = nexta)
	{
		nexta = a->inchain;
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
					if (s->ins->from == a->from && s->outs->to == to)
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
				cparc(nfa, con, a->from, s);
				cparc(nfa, a, s, to);
				freearc(nfa, a);
				break;
			default:
				assert(NOTREACHED);
				break;
		}
	}

	/* remaining inarcs, if any, incorporate the constraint */
	moveins(nfa, from, to);
	freearc(nfa, con);
	/* from state is now useless, but we leave it to pullback() to clean up */
	return 1;
}