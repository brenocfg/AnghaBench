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
struct cnfa {int nstates; } ;
struct guts {struct cnfa search; } ;
struct TYPE_3__ {scalar_t__ re_magic; scalar_t__ re_guts; } ;
typedef  TYPE_1__ regex_t ;
typedef  int /*<<< orphan*/  regex_arc_t ;

/* Variables and functions */
 scalar_t__ REMAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  traverse_lacons (struct cnfa*,int,int*,int /*<<< orphan*/ *,int) ; 

void
pg_reg_getoutarcs(const regex_t *regex, int st,
				  regex_arc_t *arcs, int arcs_len)
{
	struct cnfa *cnfa;
	int			arcs_count;

	assert(regex != NULL && regex->re_magic == REMAGIC);
	cnfa = &((struct guts *) regex->re_guts)->search;

	if (st < 0 || st >= cnfa->nstates || arcs_len <= 0)
		return;
	arcs_count = 0;
	traverse_lacons(cnfa, st, &arcs_count, arcs, arcs_len);
}