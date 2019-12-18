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
struct dmaptree {int* stree; int budmin; int /*<<< orphan*/  nleafs; int /*<<< orphan*/  leafidx; int /*<<< orphan*/  l2nleafs; } ;
typedef  int s8 ;

/* Variables and functions */
 int TREEMAX (int*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbInitTree(struct dmaptree * dtp)
{
	int l2max, l2free, bsize, nextb, i;
	int child, parent, nparent;
	s8 *tp, *cp, *cp1;

	tp = dtp->stree;

	/* Determine the maximum free string possible for the leaves */
	l2max = le32_to_cpu(dtp->l2nleafs) + dtp->budmin;

	/*
	 * configure the leaf levevl into binary buddy system
	 *
	 * Try to combine buddies starting with a buddy size of 1
	 * (i.e. two leaves). At a buddy size of 1 two buddy leaves
	 * can be combined if both buddies have a maximum free of l2min;
	 * the combination will result in the left-most buddy leaf having
	 * a maximum free of l2min+1.
	 * After processing all buddies for a given size, process buddies
	 * at the next higher buddy size (i.e. current size * 2) and
	 * the next maximum free (current free + 1).
	 * This continues until the maximum possible buddy combination
	 * yields maximum free.
	 */
	for (l2free = dtp->budmin, bsize = 1; l2free < l2max;
	     l2free++, bsize = nextb) {
		/* get next buddy size == current buddy pair size */
		nextb = bsize << 1;

		/* scan each adjacent buddy pair at current buddy size */
		for (i = 0, cp = tp + le32_to_cpu(dtp->leafidx);
		     i < le32_to_cpu(dtp->nleafs);
		     i += nextb, cp += nextb) {
			/* coalesce if both adjacent buddies are max free */
			if (*cp == l2free && *(cp + bsize) == l2free) {
				*cp = l2free + 1;	/* left take right */
				*(cp + bsize) = -1;	/* right give left */
			}
		}
	}

	/*
	 * bubble summary information of leaves up the tree.
	 *
	 * Starting at the leaf node level, the four nodes described by
	 * the higher level parent node are compared for a maximum free and
	 * this maximum becomes the value of the parent node.
	 * when all lower level nodes are processed in this fashion then
	 * move up to the next level (parent becomes a lower level node) and
	 * continue the process for that level.
	 */
	for (child = le32_to_cpu(dtp->leafidx),
	     nparent = le32_to_cpu(dtp->nleafs) >> 2;
	     nparent > 0; nparent >>= 2, child = parent) {
		/* get index of 1st node of parent level */
		parent = (child - 1) >> 2;

		/* set the value of the parent node as the maximum
		 * of the four nodes of the current level.
		 */
		for (i = 0, cp = tp + child, cp1 = tp + parent;
		     i < nparent; i++, cp += 4, cp1++)
			*cp1 = TREEMAX(cp);
	}

	return (*tp);
}