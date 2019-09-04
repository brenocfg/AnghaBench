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
struct btree_geo {int /*<<< orphan*/  keylen; } ;

/* Variables and functions */
 int /*<<< orphan*/  bkey (struct btree_geo*,unsigned long*,int /*<<< orphan*/ ) ; 
 void* bval (struct btree_geo*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longcpy (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *btree_last(struct btree_head *head, struct btree_geo *geo,
		 unsigned long *key)
{
	int height = head->height;
	unsigned long *node = head->node;

	if (height == 0)
		return NULL;

	for ( ; height > 1; height--)
		node = bval(geo, node, 0);

	longcpy(key, bkey(geo, node, 0), geo->keylen);
	return bval(geo, node, 0);
}