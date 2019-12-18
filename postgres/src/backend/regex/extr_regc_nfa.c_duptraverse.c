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
struct state {struct state* tmp; struct arc* outs; } ;
struct nfa {TYPE_1__* v; } ;
struct arc {struct state* to; struct arc* outchain; } ;
struct TYPE_2__ {int /*<<< orphan*/  re; } ;

/* Variables and functions */
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 scalar_t__ NISERR () ; 
 int /*<<< orphan*/  REG_ETOOBIG ; 
 scalar_t__ STACK_TOO_DEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  cparc (struct nfa*,struct arc*,struct state*,struct state*) ; 
 struct state* newstate (struct nfa*) ; 

__attribute__((used)) static void
duptraverse(struct nfa *nfa,
			struct state *s,
			struct state *stmp) /* s's duplicate, or NULL */
{
	struct arc *a;

	/* Since this is recursive, it could be driven to stack overflow */
	if (STACK_TOO_DEEP(nfa->v->re))
	{
		NERR(REG_ETOOBIG);
		return;
	}

	if (s->tmp != NULL)
		return;					/* already done */

	s->tmp = (stmp == NULL) ? newstate(nfa) : stmp;
	if (s->tmp == NULL)
	{
		assert(NISERR());
		return;
	}

	for (a = s->outs; a != NULL && !NISERR(); a = a->outchain)
	{
		duptraverse(nfa, a->to, (struct state *) NULL);
		if (NISERR())
			break;
		assert(a->to->tmp != NULL);
		cparc(nfa, a, s->tmp, a->to->tmp);
	}
}