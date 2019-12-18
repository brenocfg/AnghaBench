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
struct btree_head {int height; int /*<<< orphan*/  mempool; } ;
struct btree_geo {int no_pairs; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 unsigned long* bkey (struct btree_geo*,unsigned long*,int) ; 
 int btree_grow (struct btree_head*,struct btree_geo*,int /*<<< orphan*/ ) ; 
 unsigned long* btree_node_alloc (struct btree_head*,int /*<<< orphan*/ ) ; 
 void* bval (struct btree_geo*,unsigned long*,int) ; 
 int /*<<< orphan*/  clearpair (struct btree_geo*,unsigned long*,int) ; 
 unsigned long* find_level (struct btree_head*,struct btree_geo*,unsigned long*,int) ; 
 int getfill (struct btree_geo*,unsigned long*,int) ; 
 int getpos (struct btree_geo*,unsigned long*,unsigned long*) ; 
 scalar_t__ keycmp (struct btree_geo*,unsigned long*,int,unsigned long*) ; 
 int /*<<< orphan*/  mempool_free (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setkey (struct btree_geo*,unsigned long*,int,unsigned long*) ; 
 int /*<<< orphan*/  setval (struct btree_geo*,unsigned long*,int,void*) ; 

__attribute__((used)) static int btree_insert_level(struct btree_head *head, struct btree_geo *geo,
			      unsigned long *key, void *val, int level,
			      gfp_t gfp)
{
	unsigned long *node;
	int i, pos, fill, err;

	BUG_ON(!val);
	if (head->height < level) {
		err = btree_grow(head, geo, gfp);
		if (err)
			return err;
	}

retry:
	node = find_level(head, geo, key, level);
	pos = getpos(geo, node, key);
	fill = getfill(geo, node, pos);
	/* two identical keys are not allowed */
	BUG_ON(pos < fill && keycmp(geo, node, pos, key) == 0);

	if (fill == geo->no_pairs) {
		/* need to split node */
		unsigned long *new;

		new = btree_node_alloc(head, gfp);
		if (!new)
			return -ENOMEM;
		err = btree_insert_level(head, geo,
				bkey(geo, node, fill / 2 - 1),
				new, level + 1, gfp);
		if (err) {
			mempool_free(new, head->mempool);
			return err;
		}
		for (i = 0; i < fill / 2; i++) {
			setkey(geo, new, i, bkey(geo, node, i));
			setval(geo, new, i, bval(geo, node, i));
			setkey(geo, node, i, bkey(geo, node, i + fill / 2));
			setval(geo, node, i, bval(geo, node, i + fill / 2));
			clearpair(geo, node, i + fill / 2);
		}
		if (fill & 1) {
			setkey(geo, node, i, bkey(geo, node, fill - 1));
			setval(geo, node, i, bval(geo, node, fill - 1));
			clearpair(geo, node, fill - 1);
		}
		goto retry;
	}
	BUG_ON(fill >= geo->no_pairs);

	/* shift and insert */
	for (i = fill; i > pos; i--) {
		setkey(geo, node, i, bkey(geo, node, i - 1));
		setval(geo, node, i, bval(geo, node, i - 1));
	}
	setkey(geo, node, pos, key);
	setval(geo, node, pos, val);

	return 0;
}