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
struct btree_head {int height; unsigned long* node; } ;
struct btree_geo {int no_pairs; } ;

/* Variables and functions */
 int ENOENT ; 
 unsigned long* bval (struct btree_geo*,unsigned long*,int) ; 
 scalar_t__ keycmp (struct btree_geo*,unsigned long*,int,unsigned long*) ; 
 int /*<<< orphan*/  setval (struct btree_geo*,unsigned long*,int,void*) ; 

int btree_update(struct btree_head *head, struct btree_geo *geo,
		 unsigned long *key, void *val)
{
	int i, height = head->height;
	unsigned long *node = head->node;

	if (height == 0)
		return -ENOENT;

	for ( ; height > 1; height--) {
		for (i = 0; i < geo->no_pairs; i++)
			if (keycmp(geo, node, i, key) <= 0)
				break;
		if (i == geo->no_pairs)
			return -ENOENT;
		node = bval(geo, node, i);
		if (!node)
			return -ENOENT;
	}

	if (!node)
		return -ENOENT;

	for (i = 0; i < geo->no_pairs; i++)
		if (keycmp(geo, node, i, key) == 0) {
			setval(geo, node, i, val);
			return 0;
		}
	return -ENOENT;
}