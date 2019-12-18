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
struct btree_head {int /*<<< orphan*/  mempool; } ;
struct btree_geo {int no_pairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  btree_remove_level (struct btree_head*,struct btree_geo*,unsigned long*,int) ; 
 unsigned long* bval (struct btree_geo*,unsigned long*,int) ; 
 unsigned long* find_level (struct btree_head*,struct btree_geo*,unsigned long*,int) ; 
 int getfill (struct btree_geo*,unsigned long*,int) ; 
 int getpos (struct btree_geo*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  mempool_free (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge (struct btree_head*,struct btree_geo*,int,unsigned long*,int,unsigned long*,int,unsigned long*,int) ; 

__attribute__((used)) static void rebalance(struct btree_head *head, struct btree_geo *geo,
		unsigned long *key, int level, unsigned long *child, int fill)
{
	unsigned long *parent, *left = NULL, *right = NULL;
	int i, no_left, no_right;

	if (fill == 0) {
		/* Because we don't steal entries from a neighbour, this case
		 * can happen.  Parent node contains a single child, this
		 * node, so merging with a sibling never happens.
		 */
		btree_remove_level(head, geo, key, level + 1);
		mempool_free(child, head->mempool);
		return;
	}

	parent = find_level(head, geo, key, level + 1);
	i = getpos(geo, parent, key);
	BUG_ON(bval(geo, parent, i) != child);

	if (i > 0) {
		left = bval(geo, parent, i - 1);
		no_left = getfill(geo, left, 0);
		if (fill + no_left <= geo->no_pairs) {
			merge(head, geo, level,
					left, no_left,
					child, fill,
					parent, i - 1);
			return;
		}
	}
	if (i + 1 < getfill(geo, parent, i)) {
		right = bval(geo, parent, i + 1);
		no_right = getfill(geo, right, 0);
		if (fill + no_right <= geo->no_pairs) {
			merge(head, geo, level,
					child, fill,
					right, no_right,
					parent, i);
			return;
		}
	}
	/*
	 * We could also try to steal one entry from the left or right
	 * neighbor.  By not doing so we changed the invariant from
	 * "all nodes are at least half full" to "no two neighboring
	 * nodes can be merged".  Which means that the average fill of
	 * all nodes is still half or better.
	 */
}