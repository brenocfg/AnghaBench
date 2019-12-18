#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cnfa {scalar_t__ ncolors; int post; struct carc** states; } ;
struct carc {scalar_t__ co; int to; } ;
struct TYPE_3__ {scalar_t__ co; int to; } ;
typedef  TYPE_1__ regex_arc_t ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COLORLESS ; 
 int /*<<< orphan*/  check_stack_depth () ; 

__attribute__((used)) static void
traverse_lacons(struct cnfa *cnfa, int st,
				int *arcs_count,
				regex_arc_t *arcs, int arcs_len)
{
	struct carc *ca;

	/*
	 * Since this function recurses, it could theoretically be driven to stack
	 * overflow.  In practice, this is mostly useful to backstop against a
	 * failure of the regex compiler to remove a loop of LACON arcs.
	 */
	check_stack_depth();

	for (ca = cnfa->states[st]; ca->co != COLORLESS; ca++)
	{
		if (ca->co < cnfa->ncolors)
		{
			/* Ordinary arc, so count and possibly emit it */
			int			ndx = (*arcs_count)++;

			if (ndx < arcs_len)
			{
				arcs[ndx].co = ca->co;
				arcs[ndx].to = ca->to;
			}
		}
		else
		{
			/* LACON arc --- assume it's satisfied and recurse... */
			/* ... but first, assert it doesn't lead directly to post state */
			Assert(ca->to != cnfa->post);

			traverse_lacons(cnfa, ca->to, arcs_count, arcs, arcs_len);
		}
	}
}