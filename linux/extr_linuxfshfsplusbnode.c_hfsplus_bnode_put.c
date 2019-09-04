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
struct hfs_btree {int pages_per_bnode; int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  node_size; int /*<<< orphan*/  cnid; } ;
struct hfs_bnode {int /*<<< orphan*/  flags; int /*<<< orphan*/ * page; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  this; struct hfs_btree* tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNODE_REFS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HFS_BNODE_DELETED ; 
 int /*<<< orphan*/  atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfs_bmap_free (struct hfs_bnode*) ; 
 int /*<<< orphan*/  hfs_bnode_clear (struct hfs_bnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_free (struct hfs_bnode*) ; 
 scalar_t__ hfs_bnode_need_zeroout (struct hfs_btree*) ; 
 int /*<<< orphan*/  hfs_bnode_unhash (struct hfs_bnode*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_accessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hfs_bnode_put(struct hfs_bnode *node)
{
	if (node) {
		struct hfs_btree *tree = node->tree;
		int i;

		hfs_dbg(BNODE_REFS, "put_node(%d:%d): %d\n",
			node->tree->cnid, node->this,
			atomic_read(&node->refcnt));
		BUG_ON(!atomic_read(&node->refcnt));
		if (!atomic_dec_and_lock(&node->refcnt, &tree->hash_lock))
			return;
		for (i = 0; i < tree->pages_per_bnode; i++) {
			if (!node->page[i])
				continue;
			mark_page_accessed(node->page[i]);
		}

		if (test_bit(HFS_BNODE_DELETED, &node->flags)) {
			hfs_bnode_unhash(node);
			spin_unlock(&tree->hash_lock);
			if (hfs_bnode_need_zeroout(tree))
				hfs_bnode_clear(node, 0, tree->node_size);
			hfs_bmap_free(node);
			hfs_bnode_free(node);
			return;
		}
		spin_unlock(&tree->hash_lock);
	}
}