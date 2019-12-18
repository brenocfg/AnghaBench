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
struct vars {int /*<<< orphan*/  cm; int /*<<< orphan*/  nfa; } ;
struct state {int dummy; } ;

/* Variables and functions */
 char EOS ; 
 scalar_t__ ISERR () ; 
 int /*<<< orphan*/  NEXT () ; 
 int SEE (char) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  brackpart (struct vars*,struct state*,struct state*) ; 
 int /*<<< orphan*/  okcolors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bracket(struct vars *v,
		struct state *lp,
		struct state *rp)
{
	assert(SEE('['));
	NEXT();
	while (!SEE(']') && !SEE(EOS))
		brackpart(v, lp, rp);
	assert(SEE(']') || ISERR());
	okcolors(v->nfa, v->cm);
}