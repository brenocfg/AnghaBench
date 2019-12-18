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
typedef  scalar_t__ u32 ;
struct page {int dummy; } ;
struct hfs_btree {scalar_t__ node_count; int pages_per_bnode; int node_size_shift; TYPE_1__* inode; int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  node_hash_cnt; struct hfs_bnode** node_hash; int /*<<< orphan*/  cnid; } ;
struct hfs_bnode {int page_offset; int /*<<< orphan*/  flags; struct page** page; int /*<<< orphan*/  lock_wq; struct hfs_bnode* next_hash; scalar_t__ this; struct hfs_btree* tree; int /*<<< orphan*/  refcnt; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;
struct TYPE_2__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNODE_REFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HFS_BNODE_ERROR ; 
 int /*<<< orphan*/  HFS_BNODE_NEW ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct hfs_bnode* hfs_bnode_findhash (struct hfs_btree*,scalar_t__) ; 
 int hfs_bnode_hash (scalar_t__) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hfs_bnode*) ; 
 struct hfs_bnode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_mapping_page (struct address_space*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct hfs_bnode *__hfs_bnode_create(struct hfs_btree *tree, u32 cnid)
{
	struct hfs_bnode *node, *node2;
	struct address_space *mapping;
	struct page *page;
	int size, block, i, hash;
	loff_t off;

	if (cnid >= tree->node_count) {
		pr_err("request for non-existent node %d in B*Tree\n",
		       cnid);
		return NULL;
	}

	size = sizeof(struct hfs_bnode) + tree->pages_per_bnode *
		sizeof(struct page *);
	node = kzalloc(size, GFP_KERNEL);
	if (!node)
		return NULL;
	node->tree = tree;
	node->this = cnid;
	set_bit(HFS_BNODE_NEW, &node->flags);
	atomic_set(&node->refcnt, 1);
	hfs_dbg(BNODE_REFS, "new_node(%d:%d): 1\n",
		node->tree->cnid, node->this);
	init_waitqueue_head(&node->lock_wq);
	spin_lock(&tree->hash_lock);
	node2 = hfs_bnode_findhash(tree, cnid);
	if (!node2) {
		hash = hfs_bnode_hash(cnid);
		node->next_hash = tree->node_hash[hash];
		tree->node_hash[hash] = node;
		tree->node_hash_cnt++;
	} else {
		spin_unlock(&tree->hash_lock);
		kfree(node);
		wait_event(node2->lock_wq,
			!test_bit(HFS_BNODE_NEW, &node2->flags));
		return node2;
	}
	spin_unlock(&tree->hash_lock);

	mapping = tree->inode->i_mapping;
	off = (loff_t)cnid << tree->node_size_shift;
	block = off >> PAGE_SHIFT;
	node->page_offset = off & ~PAGE_MASK;
	for (i = 0; i < tree->pages_per_bnode; block++, i++) {
		page = read_mapping_page(mapping, block, NULL);
		if (IS_ERR(page))
			goto fail;
		if (PageError(page)) {
			put_page(page);
			goto fail;
		}
		node->page[i] = page;
	}

	return node;
fail:
	set_bit(HFS_BNODE_ERROR, &node->flags);
	return node;
}