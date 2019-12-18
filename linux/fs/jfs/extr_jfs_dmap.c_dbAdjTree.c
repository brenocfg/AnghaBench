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
struct TYPE_3__ {int* dmt_stree; int /*<<< orphan*/  dmt_height; int /*<<< orphan*/  dmt_leafidx; } ;
typedef  TYPE_1__ dmtree_t ;

/* Variables and functions */
 int TREEMAX (int*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dbAdjTree(dmtree_t * tp, int leafno, int newval)
{
	int lp, pp, k;
	int max;

	/* pick up the index of the leaf for this leafno.
	 */
	lp = leafno + le32_to_cpu(tp->dmt_leafidx);

	/* is the current value the same as the old value ?  if so,
	 * there is nothing to do.
	 */
	if (tp->dmt_stree[lp] == newval)
		return;

	/* set the new value.
	 */
	tp->dmt_stree[lp] = newval;

	/* bubble the new value up the tree as required.
	 */
	for (k = 0; k < le32_to_cpu(tp->dmt_height); k++) {
		/* get the index of the first leaf of the 4 leaf
		 * group containing the specified leaf (leafno).
		 */
		lp = ((lp - 1) & ~0x03) + 1;

		/* get the index of the parent of this 4 leaf group.
		 */
		pp = (lp - 1) >> 2;

		/* determine the maximum of the 4 leaves.
		 */
		max = TREEMAX(&tp->dmt_stree[lp]);

		/* if the maximum of the 4 is the same as the
		 * parent's value, we're done.
		 */
		if (tp->dmt_stree[pp] == max)
			break;

		/* parent gets new value.
		 */
		tp->dmt_stree[pp] = max;

		/* parent becomes leaf for next go-round.
		 */
		lp = pp;
	}
}