#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ bpr_ptr; } ;
struct nilfs_btree_path {int bp_index; TYPE_1__ bp_newreq; struct buffer_head* bp_sib_bh; void* bp_op; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap_stats {scalar_t__ bs_nblocks; } ;
struct nilfs_bmap {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 scalar_t__ NILFS_BMAP_USE_VBN (struct nilfs_bmap*) ; 
 int NILFS_BTREE_LEVEL_DATA ; 
 int NILFS_BTREE_LEVEL_NODE_MIN ; 
 int NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_bmap_abort_alloc_ptr (struct nilfs_bmap*,TYPE_1__*,struct inode*) ; 
 struct inode* nilfs_bmap_get_dat (struct nilfs_bmap*) ; 
 int nilfs_bmap_prepare_alloc_ptr (struct nilfs_bmap*,TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  nilfs_btnode_delete (struct buffer_head*) ; 
 void* nilfs_btree_carry_left ; 
 void* nilfs_btree_carry_right ; 
 void* nilfs_btree_do_insert ; 
 scalar_t__ nilfs_btree_find_target_v (struct nilfs_bmap*,struct nilfs_btree_path*,int /*<<< orphan*/ ) ; 
 int nilfs_btree_get_block (struct nilfs_bmap*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int nilfs_btree_get_new_block (struct nilfs_bmap*,scalar_t__,struct buffer_head**) ; 
 struct nilfs_btree_node* nilfs_btree_get_node (struct nilfs_bmap*,struct nilfs_btree_path*,int,int*) ; 
 struct nilfs_btree_node* nilfs_btree_get_nonroot_node (struct nilfs_btree_path*,int) ; 
 struct nilfs_btree_node* nilfs_btree_get_root (struct nilfs_bmap*) ; 
 void* nilfs_btree_grow ; 
 int nilfs_btree_height (struct nilfs_bmap*) ; 
 int nilfs_btree_nchildren_per_block (struct nilfs_bmap*) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/  nilfs_btree_node_get_ptr (struct nilfs_btree_node*,int,int) ; 
 int /*<<< orphan*/  nilfs_btree_node_init (struct nilfs_btree_node*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* nilfs_btree_split ; 

__attribute__((used)) static int nilfs_btree_prepare_insert(struct nilfs_bmap *btree,
				      struct nilfs_btree_path *path,
				      int *levelp, __u64 key, __u64 ptr,
				      struct nilfs_bmap_stats *stats)
{
	struct buffer_head *bh;
	struct nilfs_btree_node *node, *parent, *sib;
	__u64 sibptr;
	int pindex, level, ncmax, ncblk, ret;
	struct inode *dat = NULL;

	stats->bs_nblocks = 0;
	level = NILFS_BTREE_LEVEL_DATA;

	/* allocate a new ptr for data block */
	if (NILFS_BMAP_USE_VBN(btree)) {
		path[level].bp_newreq.bpr_ptr =
			nilfs_btree_find_target_v(btree, path, key);
		dat = nilfs_bmap_get_dat(btree);
	}

	ret = nilfs_bmap_prepare_alloc_ptr(btree, &path[level].bp_newreq, dat);
	if (ret < 0)
		goto err_out_data;

	ncblk = nilfs_btree_nchildren_per_block(btree);

	for (level = NILFS_BTREE_LEVEL_NODE_MIN;
	     level < nilfs_btree_height(btree) - 1;
	     level++) {
		node = nilfs_btree_get_nonroot_node(path, level);
		if (nilfs_btree_node_get_nchildren(node) < ncblk) {
			path[level].bp_op = nilfs_btree_do_insert;
			stats->bs_nblocks++;
			goto out;
		}

		parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
		pindex = path[level + 1].bp_index;

		/* left sibling */
		if (pindex > 0) {
			sibptr = nilfs_btree_node_get_ptr(parent, pindex - 1,
							  ncmax);
			ret = nilfs_btree_get_block(btree, sibptr, &bh);
			if (ret < 0)
				goto err_out_child_node;
			sib = (struct nilfs_btree_node *)bh->b_data;
			if (nilfs_btree_node_get_nchildren(sib) < ncblk) {
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_carry_left;
				stats->bs_nblocks++;
				goto out;
			} else {
				brelse(bh);
			}
		}

		/* right sibling */
		if (pindex < nilfs_btree_node_get_nchildren(parent) - 1) {
			sibptr = nilfs_btree_node_get_ptr(parent, pindex + 1,
							  ncmax);
			ret = nilfs_btree_get_block(btree, sibptr, &bh);
			if (ret < 0)
				goto err_out_child_node;
			sib = (struct nilfs_btree_node *)bh->b_data;
			if (nilfs_btree_node_get_nchildren(sib) < ncblk) {
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_carry_right;
				stats->bs_nblocks++;
				goto out;
			} else {
				brelse(bh);
			}
		}

		/* split */
		path[level].bp_newreq.bpr_ptr =
			path[level - 1].bp_newreq.bpr_ptr + 1;
		ret = nilfs_bmap_prepare_alloc_ptr(btree,
						   &path[level].bp_newreq, dat);
		if (ret < 0)
			goto err_out_child_node;
		ret = nilfs_btree_get_new_block(btree,
						path[level].bp_newreq.bpr_ptr,
						&bh);
		if (ret < 0)
			goto err_out_curr_node;

		stats->bs_nblocks++;

		sib = (struct nilfs_btree_node *)bh->b_data;
		nilfs_btree_node_init(sib, 0, level, 0, ncblk, NULL, NULL);
		path[level].bp_sib_bh = bh;
		path[level].bp_op = nilfs_btree_split;
	}

	/* root */
	node = nilfs_btree_get_root(btree);
	if (nilfs_btree_node_get_nchildren(node) <
	    NILFS_BTREE_ROOT_NCHILDREN_MAX) {
		path[level].bp_op = nilfs_btree_do_insert;
		stats->bs_nblocks++;
		goto out;
	}

	/* grow */
	path[level].bp_newreq.bpr_ptr = path[level - 1].bp_newreq.bpr_ptr + 1;
	ret = nilfs_bmap_prepare_alloc_ptr(btree, &path[level].bp_newreq, dat);
	if (ret < 0)
		goto err_out_child_node;
	ret = nilfs_btree_get_new_block(btree, path[level].bp_newreq.bpr_ptr,
					&bh);
	if (ret < 0)
		goto err_out_curr_node;

	nilfs_btree_node_init((struct nilfs_btree_node *)bh->b_data,
			      0, level, 0, ncblk, NULL, NULL);
	path[level].bp_sib_bh = bh;
	path[level].bp_op = nilfs_btree_grow;

	level++;
	path[level].bp_op = nilfs_btree_do_insert;

	/* a newly-created node block and a data block are added */
	stats->bs_nblocks += 2;

	/* success */
 out:
	*levelp = level;
	return ret;

	/* error */
 err_out_curr_node:
	nilfs_bmap_abort_alloc_ptr(btree, &path[level].bp_newreq, dat);
 err_out_child_node:
	for (level--; level > NILFS_BTREE_LEVEL_DATA; level--) {
		nilfs_btnode_delete(path[level].bp_sib_bh);
		nilfs_bmap_abort_alloc_ptr(btree, &path[level].bp_newreq, dat);

	}

	nilfs_bmap_abort_alloc_ptr(btree, &path[level].bp_newreq, dat);
 err_out_data:
	*levelp = level;
	stats->bs_nblocks = 0;
	return ret;
}