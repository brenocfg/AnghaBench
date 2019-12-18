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
struct vars {int /*<<< orphan*/  wordchrs; int /*<<< orphan*/  cm; int /*<<< orphan*/  nfa; } ;
struct state {int dummy; } ;

/* Variables and functions */
 int AHEAD ; 
 int BEHIND ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  colorcomplement (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct state*,struct state*) ; 
 int /*<<< orphan*/  newarc (int /*<<< orphan*/ ,int,int,struct state*,struct state*) ; 

__attribute__((used)) static void
nonword(struct vars *v,
		int dir,				/* AHEAD or BEHIND */
		struct state *lp,
		struct state *rp)
{
	int			anchor = (dir == AHEAD) ? '$' : '^';

	assert(dir == AHEAD || dir == BEHIND);
	newarc(v->nfa, anchor, 1, lp, rp);
	newarc(v->nfa, anchor, 0, lp, rp);
	colorcomplement(v->nfa, v->cm, dir, v->wordchrs, lp, rp);
	/* (no need for special attention to \n) */
}