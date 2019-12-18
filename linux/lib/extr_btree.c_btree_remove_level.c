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
struct btree_head {int height; int /*<<< orphan*/ * node; } ;
struct btree_geo {int no_pairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bkey (struct btree_geo*,unsigned long*,int) ; 
 int /*<<< orphan*/  btree_shrink (struct btree_head*,struct btree_geo*) ; 
 void* bval (struct btree_geo*,unsigned long*,int) ; 
 int /*<<< orphan*/  clearpair (struct btree_geo*,unsigned long*,int) ; 
 unsigned long* find_level (struct btree_head*,struct btree_geo*,unsigned long*,int) ; 
 int getfill (struct btree_geo*,unsigned long*,int) ; 
 int getpos (struct btree_geo*,unsigned long*,unsigned long*) ; 
 scalar_t__ keycmp (struct btree_geo*,unsigned long*,int,unsigned long*) ; 
 int /*<<< orphan*/  rebalance (struct btree_head*,struct btree_geo*,unsigned long*,int,unsigned long*,int) ; 
 int /*<<< orphan*/  setkey (struct btree_geo*,unsigned long*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setval (struct btree_geo*,unsigned long*,int,void*) ; 

__attribute__((used)) static void *btree_remove_level(struct btree_head *head, struct btree_geo *geo,
		unsigned long *key, int level)
{
	unsigned long *node;
	int i, pos, fill;
	void *ret;

	if (level > head->height) {
		/* we recursed all the way up */
		head->height = 0;
		head->node = NULL;
		return NULL;
	}

	node = find_level(head, geo, key, level);
	pos = getpos(geo, node, key);
	fill = getfill(geo, node, pos);
	if ((level == 1) && (keycmp(geo, node, pos, key) != 0))
		return NULL;
	ret = bval(geo, node, pos);

	/* remove and shift */
	for (i = pos; i < fill - 1; i++) {
		setkey(geo, node, i, bkey(geo, node, i + 1));
		setval(geo, node, i, bval(geo, node, i + 1));
	}
	clearpair(geo, node, fill - 1);

	if (fill - 1 < geo->no_pairs / 2) {
		if (level < head->height)
			rebalance(head, geo, key, level, node, fill - 1);
		else if (fill - 1 == 1)
			btree_shrink(head, geo);
	}

	return ret;
}