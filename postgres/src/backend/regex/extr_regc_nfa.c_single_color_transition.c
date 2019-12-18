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
struct state {int nouts; int nins; struct arc* outs; TYPE_1__* ins; } ;
struct arc {scalar_t__ type; struct state* to; struct arc* outchain; } ;
struct TYPE_2__ {scalar_t__ type; struct state* from; } ;

/* Variables and functions */
 scalar_t__ EMPTY ; 
 scalar_t__ PLAIN ; 

__attribute__((used)) static struct state *
single_color_transition(struct state *s1, struct state *s2)
{
	struct arc *a;

	/* Ignore leading EMPTY arc, if any */
	if (s1->nouts == 1 && s1->outs->type == EMPTY)
		s1 = s1->outs->to;
	/* Likewise for any trailing EMPTY arc */
	if (s2->nins == 1 && s2->ins->type == EMPTY)
		s2 = s2->ins->from;
	/* Perhaps we could have a single-state loop in between, if so reject */
	if (s1 == s2)
		return NULL;
	/* s1 must have at least one outarc... */
	if (s1->outs == NULL)
		return NULL;
	/* ... and they must all be PLAIN arcs to s2 */
	for (a = s1->outs; a != NULL; a = a->outchain)
	{
		if (a->type != PLAIN || a->to != s2)
			return NULL;
	}
	/* OK, return s1 as the possessor of the relevant outarcs */
	return s1;
}