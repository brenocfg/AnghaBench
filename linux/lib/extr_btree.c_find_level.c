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
struct btree_head {unsigned long* node; int height; } ;
struct btree_geo {int no_pairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long* bval (struct btree_geo*,unsigned long*,int) ; 
 scalar_t__ keycmp (struct btree_geo*,unsigned long*,int,unsigned long*) ; 
 int /*<<< orphan*/  setkey (struct btree_geo*,unsigned long*,int,unsigned long*) ; 

__attribute__((used)) static unsigned long *find_level(struct btree_head *head, struct btree_geo *geo,
		unsigned long *key, int level)
{
	unsigned long *node = head->node;
	int i, height;

	for (height = head->height; height > level; height--) {
		for (i = 0; i < geo->no_pairs; i++)
			if (keycmp(geo, node, i, key) <= 0)
				break;

		if ((i == geo->no_pairs) || !bval(geo, node, i)) {
			/* right-most key is too large, update it */
			/* FIXME: If the right-most key on higher levels is
			 * always zero, this wouldn't be necessary. */
			i--;
			setkey(geo, node, i, key);
		}
		BUG_ON(i < 0);
		node = bval(geo, node, i);
	}
	BUG_ON(!node);
	return node;
}