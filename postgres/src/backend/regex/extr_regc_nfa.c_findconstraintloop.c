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
 int /*<<< orphan*/  REG_ETOOBIG ; 
 scalar_t__ STACK_TOO_DEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  breakconstraintloop (struct nfa*,struct state*) ; 
 scalar_t__ isconstraintarc (struct arc*) ; 

__attribute__((used)) static int
findconstraintloop(struct nfa *nfa, struct state *s)
{
	struct arc *a;

	/* Since this is recursive, it could be driven to stack overflow */
	if (STACK_TOO_DEEP(nfa->v->re))
	{
		NERR(REG_ETOOBIG);
		return 1;				/* to exit as quickly as possible */
	}

	if (s->tmp != NULL)
	{
		/* Already proven uninteresting? */
		if (s->tmp == s)
			return 0;
		/* Found a loop involving s */
		breakconstraintloop(nfa, s);
		/* The tmp fields have been cleaned up by breakconstraintloop */
		return 1;
	}
	for (a = s->outs; a != NULL; a = a->outchain)
	{
		if (isconstraintarc(a))
		{
			struct state *sto = a->to;

			assert(sto != s);
			s->tmp = sto;
			if (findconstraintloop(nfa, sto))
				return 1;
		}
	}

	/*
	 * If we get here, no constraint loop exists leading out from s.  Mark it
	 * with s->tmp == s so we need not rediscover that fact again later.
	 */
	s->tmp = s;
	return 0;
}