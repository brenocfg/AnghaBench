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
struct vars {int cflags; int /*<<< orphan*/  nfa; int /*<<< orphan*/  cm; int /*<<< orphan*/  nlcolor; } ;
struct state {scalar_t__ nouts; scalar_t__ nins; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOERR () ; 
 int /*<<< orphan*/  PLAIN ; 
 int REG_NLSTOP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bracket (struct vars*,struct state*,struct state*) ; 
 int /*<<< orphan*/  colorcomplement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct state*,struct state*,struct state*) ; 
 int /*<<< orphan*/  dropstate (int /*<<< orphan*/ ,struct state*) ; 
 int /*<<< orphan*/  freestate (int /*<<< orphan*/ ,struct state*) ; 
 int /*<<< orphan*/  newarc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct state*,struct state*) ; 
 struct state* newstate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cbracket(struct vars *v,
		 struct state *lp,
		 struct state *rp)
{
	struct state *left = newstate(v->nfa);
	struct state *right = newstate(v->nfa);

	NOERR();
	bracket(v, left, right);
	if (v->cflags & REG_NLSTOP)
		newarc(v->nfa, PLAIN, v->nlcolor, left, right);
	NOERR();

	assert(lp->nouts == 0);		/* all outarcs will be ours */

	/*
	 * Easy part of complementing, and all there is to do since the MCCE code
	 * was removed.
	 */
	colorcomplement(v->nfa, v->cm, PLAIN, left, lp, rp);
	NOERR();
	dropstate(v->nfa, left);
	assert(right->nins == 0);
	freestate(v->nfa, right);
}