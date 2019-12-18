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
struct state {int dummy; } ;
struct nfa {int dummy; } ;
struct colormap {struct colordesc* cd; } ;
struct colordesc {int flags; } ;
typedef  scalar_t__ color ;

/* Variables and functions */
 struct colordesc* CDEND (struct colormap*) ; 
 int /*<<< orphan*/  CISERR () ; 
 int /*<<< orphan*/  PLAIN ; 
 int PSEUDO ; 
 int /*<<< orphan*/  UNUSEDCOLOR (struct colordesc*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * findarc (struct state*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  newarc (struct nfa*,int,scalar_t__,struct state*,struct state*) ; 

__attribute__((used)) static void
colorcomplement(struct nfa *nfa,
				struct colormap *cm,
				int type,
				struct state *of,	/* complements of this guy's PLAIN outarcs */
				struct state *from,
				struct state *to)
{
	struct colordesc *cd;
	struct colordesc *end = CDEND(cm);
	color		co;

	assert(of != from);
	for (cd = cm->cd, co = 0; cd < end && !CISERR(); cd++, co++)
		if (!UNUSEDCOLOR(cd) && !(cd->flags & PSEUDO))
			if (findarc(of, PLAIN, co) == NULL)
				newarc(nfa, type, co, from, to);
}