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
struct vars {int /*<<< orphan*/  wordchrs; int /*<<< orphan*/  nfa; } ;
struct state {int dummy; } ;

/* Variables and functions */
 int AHEAD ; 
 int BEHIND ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cloneouts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct state*,struct state*,int) ; 

__attribute__((used)) static void
word(struct vars *v,
	 int dir,					/* AHEAD or BEHIND */
	 struct state *lp,
	 struct state *rp)
{
	assert(dir == AHEAD || dir == BEHIND);
	cloneouts(v->nfa, v->wordchrs, lp, rp, dir);
	/* (no need for special attention to \n) */
}