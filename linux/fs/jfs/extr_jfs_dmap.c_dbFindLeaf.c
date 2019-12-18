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
struct TYPE_3__ {int* dmt_stree; int /*<<< orphan*/  dmt_leafidx; int /*<<< orphan*/  dmt_height; } ;
typedef  TYPE_1__ dmtree_t ;

/* Variables and functions */
 int ENOSPC ; 
 size_t ROOT ; 
 int /*<<< orphan*/  assert (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbFindLeaf(dmtree_t * tp, int l2nb, int *leafidx)
{
	int ti, n = 0, k, x = 0;

	/* first check the root of the tree to see if there is
	 * sufficient free space.
	 */
	if (l2nb > tp->dmt_stree[ROOT])
		return -ENOSPC;

	/* sufficient free space available. now search down the tree
	 * starting at the next level for the leftmost leaf that
	 * describes sufficient free space.
	 */
	for (k = le32_to_cpu(tp->dmt_height), ti = 1;
	     k > 0; k--, ti = ((ti + n) << 2) + 1) {
		/* search the four nodes at this level, starting from
		 * the left.
		 */
		for (x = ti, n = 0; n < 4; n++) {
			/* sufficient free space found.  move to the next
			 * level (or quit if this is the last level).
			 */
			if (l2nb <= tp->dmt_stree[x + n])
				break;
		}

		/* better have found something since the higher
		 * levels of the tree said it was here.
		 */
		assert(n < 4);
	}

	/* set the return to the leftmost leaf describing sufficient
	 * free space.
	 */
	*leafidx = x + n - le32_to_cpu(tp->dmt_leafidx);

	return (0);
}