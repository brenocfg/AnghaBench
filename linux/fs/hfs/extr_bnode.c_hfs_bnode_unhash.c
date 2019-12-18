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
struct hfs_bnode {TYPE_1__* tree; struct hfs_bnode* next_hash; int /*<<< orphan*/  this; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  node_hash_cnt; struct hfs_bnode** node_hash; int /*<<< orphan*/  cnid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNODE_REFS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 size_t hfs_bnode_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hfs_bnode_unhash(struct hfs_bnode *node)
{
	struct hfs_bnode **p;

	hfs_dbg(BNODE_REFS, "remove_node(%d:%d): %d\n",
		node->tree->cnid, node->this, atomic_read(&node->refcnt));
	for (p = &node->tree->node_hash[hfs_bnode_hash(node->this)];
	     *p && *p != node; p = &(*p)->next_hash)
		;
	BUG_ON(!*p);
	*p = node->next_hash;
	node->tree->node_hash_cnt--;
}