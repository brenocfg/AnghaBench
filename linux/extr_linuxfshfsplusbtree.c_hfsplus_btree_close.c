#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hfs_btree {int /*<<< orphan*/  inode; int /*<<< orphan*/  node_hash_cnt; struct hfs_bnode** node_hash; } ;
struct hfs_bnode {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  this; TYPE_1__* tree; struct hfs_bnode* next_hash; } ;
struct TYPE_2__ {int /*<<< orphan*/  cnid; } ;

/* Variables and functions */
 int NODE_HASH_SIZE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfs_bnode_free (struct hfs_bnode*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hfs_btree*) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void hfs_btree_close(struct hfs_btree *tree)
{
	struct hfs_bnode *node;
	int i;

	if (!tree)
		return;

	for (i = 0; i < NODE_HASH_SIZE; i++) {
		while ((node = tree->node_hash[i])) {
			tree->node_hash[i] = node->next_hash;
			if (atomic_read(&node->refcnt))
				pr_crit("node %d:%d "
						"still has %d user(s)!\n",
					node->tree->cnid, node->this,
					atomic_read(&node->refcnt));
			hfs_bnode_free(node);
			tree->node_hash_cnt--;
		}
	}
	iput(tree->inode);
	kfree(tree);
}