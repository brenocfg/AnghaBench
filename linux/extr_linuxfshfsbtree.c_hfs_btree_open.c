#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct hfs_mdb {int /*<<< orphan*/  drCTClpSiz; int /*<<< orphan*/  drCTFlSize; int /*<<< orphan*/  drCTExtRec; int /*<<< orphan*/  drXTClpSiz; int /*<<< orphan*/  drXTFlSize; int /*<<< orphan*/  drXTExtRec; } ;
struct hfs_btree_header_rec {int /*<<< orphan*/  depth; int /*<<< orphan*/  max_key_len; int /*<<< orphan*/  node_size; int /*<<< orphan*/  attributes; int /*<<< orphan*/  free_nodes; int /*<<< orphan*/  node_count; int /*<<< orphan*/  leaf_tail; int /*<<< orphan*/  leaf_head; int /*<<< orphan*/  leaf_count; int /*<<< orphan*/  root; } ;
struct hfs_btree {int cnid; unsigned int node_size; int pages_per_bnode; TYPE_1__* inode; scalar_t__ node_size_shift; void* max_key_len; void* node_count; void* depth; void* attributes; void* free_nodes; void* leaf_tail; void* leaf_head; void* leaf_count; void* root; int /*<<< orphan*/  keycmp; struct super_block* sb; int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  tree_lock; } ;
struct hfs_bnode_desc {int dummy; } ;
struct address_space {int /*<<< orphan*/ * a_ops; } ;
typedef  int /*<<< orphan*/  btree_keycmp ;
struct TYPE_10__ {int /*<<< orphan*/  first_blocks; int /*<<< orphan*/  alloc_blocks; int /*<<< orphan*/  extents_lock; scalar_t__ flags; } ;
struct TYPE_9__ {struct hfs_mdb* mdb; } ;
struct TYPE_8__ {int i_state; struct address_space* i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HFS_CAT_CNID 129 
#define  HFS_EXT_CNID 128 
 TYPE_6__* HFS_I (TYPE_1__*) ; 
 void* HFS_MAX_CAT_KEYLEN ; 
 void* HFS_MAX_EXT_KEYLEN ; 
 TYPE_5__* HFS_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int I_NEW ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ffs (unsigned int) ; 
 int /*<<< orphan*/  hfs_aops ; 
 int /*<<< orphan*/  hfs_btree_aops ; 
 int /*<<< orphan*/  hfs_inode_read_fork (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 TYPE_1__* iget_locked (struct super_block*,int) ; 
 int /*<<< orphan*/  iput (TYPE_1__*) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct hfs_btree*) ; 
 scalar_t__ kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 struct hfs_btree* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_mapping_page (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_new_inode (TYPE_1__*) ; 

struct hfs_btree *hfs_btree_open(struct super_block *sb, u32 id, btree_keycmp keycmp)
{
	struct hfs_btree *tree;
	struct hfs_btree_header_rec *head;
	struct address_space *mapping;
	struct page *page;
	unsigned int size;

	tree = kzalloc(sizeof(*tree), GFP_KERNEL);
	if (!tree)
		return NULL;

	mutex_init(&tree->tree_lock);
	spin_lock_init(&tree->hash_lock);
	/* Set the correct compare function */
	tree->sb = sb;
	tree->cnid = id;
	tree->keycmp = keycmp;

	tree->inode = iget_locked(sb, id);
	if (!tree->inode)
		goto free_tree;
	BUG_ON(!(tree->inode->i_state & I_NEW));
	{
	struct hfs_mdb *mdb = HFS_SB(sb)->mdb;
	HFS_I(tree->inode)->flags = 0;
	mutex_init(&HFS_I(tree->inode)->extents_lock);
	switch (id) {
	case HFS_EXT_CNID:
		hfs_inode_read_fork(tree->inode, mdb->drXTExtRec, mdb->drXTFlSize,
				    mdb->drXTFlSize, be32_to_cpu(mdb->drXTClpSiz));
		if (HFS_I(tree->inode)->alloc_blocks >
					HFS_I(tree->inode)->first_blocks) {
			pr_err("invalid btree extent records\n");
			unlock_new_inode(tree->inode);
			goto free_inode;
		}

		tree->inode->i_mapping->a_ops = &hfs_btree_aops;
		break;
	case HFS_CAT_CNID:
		hfs_inode_read_fork(tree->inode, mdb->drCTExtRec, mdb->drCTFlSize,
				    mdb->drCTFlSize, be32_to_cpu(mdb->drCTClpSiz));

		if (!HFS_I(tree->inode)->first_blocks) {
			pr_err("invalid btree extent records (0 size)\n");
			unlock_new_inode(tree->inode);
			goto free_inode;
		}

		tree->inode->i_mapping->a_ops = &hfs_btree_aops;
		break;
	default:
		BUG();
	}
	}
	unlock_new_inode(tree->inode);

	mapping = tree->inode->i_mapping;
	page = read_mapping_page(mapping, 0, NULL);
	if (IS_ERR(page))
		goto free_inode;

	/* Load the header */
	head = (struct hfs_btree_header_rec *)(kmap(page) + sizeof(struct hfs_bnode_desc));
	tree->root = be32_to_cpu(head->root);
	tree->leaf_count = be32_to_cpu(head->leaf_count);
	tree->leaf_head = be32_to_cpu(head->leaf_head);
	tree->leaf_tail = be32_to_cpu(head->leaf_tail);
	tree->node_count = be32_to_cpu(head->node_count);
	tree->free_nodes = be32_to_cpu(head->free_nodes);
	tree->attributes = be32_to_cpu(head->attributes);
	tree->node_size = be16_to_cpu(head->node_size);
	tree->max_key_len = be16_to_cpu(head->max_key_len);
	tree->depth = be16_to_cpu(head->depth);

	size = tree->node_size;
	if (!is_power_of_2(size))
		goto fail_page;
	if (!tree->node_count)
		goto fail_page;
	switch (id) {
	case HFS_EXT_CNID:
		if (tree->max_key_len != HFS_MAX_EXT_KEYLEN) {
			pr_err("invalid extent max_key_len %d\n",
			       tree->max_key_len);
			goto fail_page;
		}
		break;
	case HFS_CAT_CNID:
		if (tree->max_key_len != HFS_MAX_CAT_KEYLEN) {
			pr_err("invalid catalog max_key_len %d\n",
			       tree->max_key_len);
			goto fail_page;
		}
		break;
	default:
		BUG();
	}

	tree->node_size_shift = ffs(size) - 1;
	tree->pages_per_bnode = (tree->node_size + PAGE_SIZE - 1) >> PAGE_SHIFT;

	kunmap(page);
	put_page(page);
	return tree;

fail_page:
	put_page(page);
free_inode:
	tree->inode->i_mapping->a_ops = &hfs_aops;
	iput(tree->inode);
free_tree:
	kfree(tree);
	return NULL;
}