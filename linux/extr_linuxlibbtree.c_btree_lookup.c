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
 void* bval (struct btree_geo*,unsigned long*,int) ; 
 scalar_t__ keycmp (struct btree_geo*,unsigned long*,int,unsigned long*) ; 

void *btree_lookup(struct btree_head *head, struct btree_geo *geo,
		unsigned long *key)
{
	int i, height = head->height;
	unsigned long *node = head->node;

	if (height == 0)
		return NULL;

	for ( ; height > 1; height--) {
		for (i = 0; i < geo->no_pairs; i++)
			if (keycmp(geo, node, i, key) <= 0)
				break;
		if (i == geo->no_pairs)
			return NULL;
		node = bval(geo, node, i);
		if (!node)
			return NULL;
	}

	if (!node)
		return NULL;

	for (i = 0; i < geo->no_pairs; i++)
		if (keycmp(geo, node, i, key) == 0)
			return bval(geo, node, i);
	return NULL;
}