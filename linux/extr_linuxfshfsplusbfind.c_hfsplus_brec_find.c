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
typedef  scalar_t__ u32 ;
struct hfs_find_data {scalar_t__ record; struct hfs_bnode* bnode; int /*<<< orphan*/  entryoffset; struct hfs_btree* tree; } ;
struct hfs_btree {int depth; scalar_t__ root; } ;
struct hfs_bnode {int height; scalar_t__ type; scalar_t__ parent; } ;
typedef  int /*<<< orphan*/  search_strategy_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 scalar_t__ HFS_NODE_INDEX ; 
 scalar_t__ HFS_NODE_LEAF ; 
 scalar_t__ IS_ERR (struct hfs_bnode*) ; 
 int PTR_ERR (struct hfs_bnode*) ; 
 int __hfs_brec_find (struct hfs_bnode*,struct hfs_find_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct hfs_bnode* hfs_bnode_find (struct hfs_btree*,scalar_t__) ; 
 int /*<<< orphan*/  hfs_bnode_put (struct hfs_bnode*) ; 
 int /*<<< orphan*/  hfs_bnode_read (struct hfs_bnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,scalar_t__,scalar_t__,scalar_t__) ; 

int hfs_brec_find(struct hfs_find_data *fd, search_strategy_t do_key_compare)
{
	struct hfs_btree *tree;
	struct hfs_bnode *bnode;
	u32 nidx, parent;
	__be32 data;
	int height, res;

	tree = fd->tree;
	if (fd->bnode)
		hfs_bnode_put(fd->bnode);
	fd->bnode = NULL;
	nidx = tree->root;
	if (!nidx)
		return -ENOENT;
	height = tree->depth;
	res = 0;
	parent = 0;
	for (;;) {
		bnode = hfs_bnode_find(tree, nidx);
		if (IS_ERR(bnode)) {
			res = PTR_ERR(bnode);
			bnode = NULL;
			break;
		}
		if (bnode->height != height)
			goto invalid;
		if (bnode->type != (--height ? HFS_NODE_INDEX : HFS_NODE_LEAF))
			goto invalid;
		bnode->parent = parent;

		res = __hfs_brec_find(bnode, fd, do_key_compare);
		if (!height)
			break;
		if (fd->record < 0)
			goto release;

		parent = nidx;
		hfs_bnode_read(bnode, &data, fd->entryoffset, 4);
		nidx = be32_to_cpu(data);
		hfs_bnode_put(bnode);
	}
	fd->bnode = bnode;
	return res;

invalid:
	pr_err("inconsistency in B*Tree (%d,%d,%d,%u,%u)\n",
		height, bnode->height, bnode->type, nidx, parent);
	res = -EIO;
release:
	hfs_bnode_put(bnode);
	return res;
}