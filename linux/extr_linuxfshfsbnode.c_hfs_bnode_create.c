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
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct hfs_btree {int pages_per_bnode; scalar_t__ node_size; int /*<<< orphan*/  hash_lock; } ;
struct hfs_bnode {int /*<<< orphan*/  lock_wq; int /*<<< orphan*/  flags; scalar_t__ page_offset; struct page** page; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct hfs_bnode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFS_BNODE_ERROR ; 
 int /*<<< orphan*/  HFS_BNODE_NEW ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct hfs_bnode* __hfs_bnode_create (struct hfs_btree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hfs_bnode* hfs_bnode_findhash (struct hfs_btree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_put (struct hfs_bnode*) ; 
 scalar_t__ kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ min (int,int) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

struct hfs_bnode *hfs_bnode_create(struct hfs_btree *tree, u32 num)
{
	struct hfs_bnode *node;
	struct page **pagep;
	int i;

	spin_lock(&tree->hash_lock);
	node = hfs_bnode_findhash(tree, num);
	spin_unlock(&tree->hash_lock);
	if (node) {
		pr_crit("new node %u already hashed?\n", num);
		WARN_ON(1);
		return node;
	}
	node = __hfs_bnode_create(tree, num);
	if (!node)
		return ERR_PTR(-ENOMEM);
	if (test_bit(HFS_BNODE_ERROR, &node->flags)) {
		hfs_bnode_put(node);
		return ERR_PTR(-EIO);
	}

	pagep = node->page;
	memset(kmap(*pagep) + node->page_offset, 0,
	       min((int)PAGE_SIZE, (int)tree->node_size));
	set_page_dirty(*pagep);
	kunmap(*pagep);
	for (i = 1; i < tree->pages_per_bnode; i++) {
		memset(kmap(*++pagep), 0, PAGE_SIZE);
		set_page_dirty(*pagep);
		kunmap(*pagep);
	}
	clear_bit(HFS_BNODE_NEW, &node->flags);
	wake_up(&node->lock_wq);

	return node;
}