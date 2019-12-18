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
struct state {scalar_t__ nouts; scalar_t__ nins; struct arc* ins; struct arc* outs; } ;
struct nfa {TYPE_1__* v; } ;
struct arc {scalar_t__ co; int type; struct state* from; struct arc* inchain; struct state* to; struct arc* outchain; } ;
typedef  scalar_t__ color ;
struct TYPE_2__ {int /*<<< orphan*/  re; } ;

/* Variables and functions */
 scalar_t__ CANCEL_REQUESTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CANCEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  createarc (struct nfa*,int,scalar_t__,struct state*,struct state*) ; 

__attribute__((used)) static void
newarc(struct nfa *nfa,
	   int t,
	   color co,
	   struct state *from,
	   struct state *to)
{
	struct arc *a;

	assert(from != NULL && to != NULL);

	/*
	 * This is a handy place to check for operation cancel during regex
	 * compilation, since no code path will go very long without making a new
	 * state or arc.
	 */
	if (CANCEL_REQUESTED(nfa->v->re))
	{
		NERR(REG_CANCEL);
		return;
	}

	/* check for duplicate arc, using whichever chain is shorter */
	if (from->nouts <= to->nins)
	{
		for (a = from->outs; a != NULL; a = a->outchain)
			if (a->to == to && a->co == co && a->type == t)
				return;
	}
	else
	{
		for (a = to->ins; a != NULL; a = a->inchain)
			if (a->from == from && a->co == co && a->type == t)
				return;
	}

	/* no dup, so create the arc */
	createarc(nfa, t, co, from, to);
}