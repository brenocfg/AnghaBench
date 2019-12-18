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
struct state {scalar_t__ nouts; scalar_t__ nins; scalar_t__ no; struct state* tmp; struct arc* outs; } ;
struct nfa {TYPE_1__* v; } ;
struct arc {struct state* to; } ;
struct TYPE_2__ {int /*<<< orphan*/  re; } ;

/* Variables and functions */
 scalar_t__ FREESTATE ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 scalar_t__ NISERR () ; 
 int /*<<< orphan*/  REG_ETOOBIG ; 
 scalar_t__ STACK_TOO_DEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  freearc (struct nfa*,struct arc*) ; 
 int /*<<< orphan*/  freestate (struct nfa*,struct state*) ; 

__attribute__((used)) static void
deltraverse(struct nfa *nfa,
			struct state *leftend,
			struct state *s)
{
	struct arc *a;
	struct state *to;

	/* Since this is recursive, it could be driven to stack overflow */
	if (STACK_TOO_DEEP(nfa->v->re))
	{
		NERR(REG_ETOOBIG);
		return;
	}

	if (s->nouts == 0)
		return;					/* nothing to do */
	if (s->tmp != NULL)
		return;					/* already in progress */

	s->tmp = s;					/* mark as in progress */

	while ((a = s->outs) != NULL)
	{
		to = a->to;
		deltraverse(nfa, leftend, to);
		if (NISERR())
			return;				/* asserts might not hold after failure */
		assert(to->nouts == 0 || to->tmp != NULL);
		freearc(nfa, a);
		if (to->nins == 0 && to->tmp == NULL)
		{
			assert(to->nouts == 0);
			freestate(nfa, to);
		}
	}

	assert(s->no != FREESTATE); /* we're still here */
	assert(s == leftend || s->nins != 0);	/* and still reachable */
	assert(s->nouts == 0);		/* but have no outarcs */

	s->tmp = NULL;				/* we're done here */
}