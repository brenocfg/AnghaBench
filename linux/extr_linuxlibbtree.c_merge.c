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
struct btree_geo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bkey (struct btree_geo*,unsigned long*,int) ; 
 int /*<<< orphan*/  btree_remove_level (struct btree_head*,struct btree_geo*,int /*<<< orphan*/ ,int) ; 
 unsigned long* bval (struct btree_geo*,unsigned long*,int) ; 
 int /*<<< orphan*/  mempool_free (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setkey (struct btree_geo*,unsigned long*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setval (struct btree_geo*,unsigned long*,int,unsigned long*) ; 

__attribute__((used)) static void merge(struct btree_head *head, struct btree_geo *geo, int level,
		unsigned long *left, int lfill,
		unsigned long *right, int rfill,
		unsigned long *parent, int lpos)
{
	int i;

	for (i = 0; i < rfill; i++) {
		/* Move all keys to the left */
		setkey(geo, left, lfill + i, bkey(geo, right, i));
		setval(geo, left, lfill + i, bval(geo, right, i));
	}
	/* Exchange left and right child in parent */
	setval(geo, parent, lpos, right);
	setval(geo, parent, lpos + 1, left);
	/* Remove left (formerly right) child from parent */
	btree_remove_level(head, geo, bkey(geo, parent, lpos), level + 1);
	mempool_free(right, head->mempool);
}