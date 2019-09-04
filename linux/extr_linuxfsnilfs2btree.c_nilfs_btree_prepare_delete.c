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
struct TYPE_3__ {void* bpr_ptr; } ;
struct nilfs_btree_path {int bp_index; TYPE_1__ bp_oldreq; struct buffer_head* bp_sib_bh; void* bp_op; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap_stats {scalar_t__ bs_nblocks; } ;
struct nilfs_bmap {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  void* __u64 ;

/* Variables and functions */
 int NILFS_BTREE_LEVEL_NODE_MIN ; 
 int NILFS_BTREE_NODE_NCHILDREN_MIN (int /*<<< orphan*/ ) ; 
 int NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_bmap_abort_end_ptr (struct nilfs_bmap*,TYPE_1__*,struct inode*) ; 
 int nilfs_bmap_prepare_end_ptr (struct nilfs_bmap*,TYPE_1__*,struct inode*) ; 
 void* nilfs_btree_borrow_left ; 
 void* nilfs_btree_borrow_right ; 
 void* nilfs_btree_concat_left ; 
 void* nilfs_btree_concat_right ; 
 void* nilfs_btree_do_delete ; 
 int nilfs_btree_get_block (struct nilfs_bmap*,void*,struct buffer_head**) ; 
 struct nilfs_btree_node* nilfs_btree_get_node (struct nilfs_bmap*,struct nilfs_btree_path*,int,int*) ; 
 struct nilfs_btree_node* nilfs_btree_get_nonroot_node (struct nilfs_btree_path*,int) ; 
 struct nilfs_btree_node* nilfs_btree_get_root (struct nilfs_bmap*) ; 
 int nilfs_btree_height (struct nilfs_bmap*) ; 
 int nilfs_btree_nchildren_per_block (struct nilfs_bmap*) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 void* nilfs_btree_node_get_ptr (struct nilfs_btree_node*,int,int) ; 
 int /*<<< orphan*/  nilfs_btree_node_size (struct nilfs_bmap*) ; 
 void* nilfs_btree_nop ; 
 void* nilfs_btree_shrink ; 

__attribute__((used)) static int nilfs_btree_prepare_delete(struct nilfs_bmap *btree,
				      struct nilfs_btree_path *path,
				      int *levelp,
				      struct nilfs_bmap_stats *stats,
				      struct inode *dat)
{
	struct buffer_head *bh;
	struct nilfs_btree_node *node, *parent, *sib;
	__u64 sibptr;
	int pindex, dindex, level, ncmin, ncmax, ncblk, ret;

	ret = 0;
	stats->bs_nblocks = 0;
	ncmin = NILFS_BTREE_NODE_NCHILDREN_MIN(nilfs_btree_node_size(btree));
	ncblk = nilfs_btree_nchildren_per_block(btree);

	for (level = NILFS_BTREE_LEVEL_NODE_MIN, dindex = path[level].bp_index;
	     level < nilfs_btree_height(btree) - 1;
	     level++) {
		node = nilfs_btree_get_nonroot_node(path, level);
		path[level].bp_oldreq.bpr_ptr =
			nilfs_btree_node_get_ptr(node, dindex, ncblk);
		ret = nilfs_bmap_prepare_end_ptr(btree,
						 &path[level].bp_oldreq, dat);
		if (ret < 0)
			goto err_out_child_node;

		if (nilfs_btree_node_get_nchildren(node) > ncmin) {
			path[level].bp_op = nilfs_btree_do_delete;
			stats->bs_nblocks++;
			goto out;
		}

		parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
		pindex = path[level + 1].bp_index;
		dindex = pindex;

		if (pindex > 0) {
			/* left sibling */
			sibptr = nilfs_btree_node_get_ptr(parent, pindex - 1,
							  ncmax);
			ret = nilfs_btree_get_block(btree, sibptr, &bh);
			if (ret < 0)
				goto err_out_curr_node;
			sib = (struct nilfs_btree_node *)bh->b_data;
			if (nilfs_btree_node_get_nchildren(sib) > ncmin) {
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_borrow_left;
				stats->bs_nblocks++;
				goto out;
			} else {
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_concat_left;
				stats->bs_nblocks++;
				/* continue; */
			}
		} else if (pindex <
			   nilfs_btree_node_get_nchildren(parent) - 1) {
			/* right sibling */
			sibptr = nilfs_btree_node_get_ptr(parent, pindex + 1,
							  ncmax);
			ret = nilfs_btree_get_block(btree, sibptr, &bh);
			if (ret < 0)
				goto err_out_curr_node;
			sib = (struct nilfs_btree_node *)bh->b_data;
			if (nilfs_btree_node_get_nchildren(sib) > ncmin) {
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_borrow_right;
				stats->bs_nblocks++;
				goto out;
			} else {
				path[level].bp_sib_bh = bh;
				path[level].bp_op = nilfs_btree_concat_right;
				stats->bs_nblocks++;
				/*
				 * When merging right sibling node
				 * into the current node, pointer to
				 * the right sibling node must be
				 * terminated instead.  The adjustment
				 * below is required for that.
				 */
				dindex = pindex + 1;
				/* continue; */
			}
		} else {
			/* no siblings */
			/* the only child of the root node */
			WARN_ON(level != nilfs_btree_height(btree) - 2);
			if (nilfs_btree_node_get_nchildren(node) - 1 <=
			    NILFS_BTREE_ROOT_NCHILDREN_MAX) {
				path[level].bp_op = nilfs_btree_shrink;
				stats->bs_nblocks += 2;
				level++;
				path[level].bp_op = nilfs_btree_nop;
				goto shrink_root_child;
			} else {
				path[level].bp_op = nilfs_btree_do_delete;
				stats->bs_nblocks++;
				goto out;
			}
		}
	}

	/* child of the root node is deleted */
	path[level].bp_op = nilfs_btree_do_delete;
	stats->bs_nblocks++;

shrink_root_child:
	node = nilfs_btree_get_root(btree);
	path[level].bp_oldreq.bpr_ptr =
		nilfs_btree_node_get_ptr(node, dindex,
					 NILFS_BTREE_ROOT_NCHILDREN_MAX);

	ret = nilfs_bmap_prepare_end_ptr(btree, &path[level].bp_oldreq, dat);
	if (ret < 0)
		goto err_out_child_node;

	/* success */
 out:
	*levelp = level;
	return ret;

	/* error */
 err_out_curr_node:
	nilfs_bmap_abort_end_ptr(btree, &path[level].bp_oldreq, dat);
 err_out_child_node:
	for (level--; level >= NILFS_BTREE_LEVEL_NODE_MIN; level--) {
		brelse(path[level].bp_sib_bh);
		nilfs_bmap_abort_end_ptr(btree, &path[level].bp_oldreq, dat);
	}
	*levelp = level;
	stats->bs_nblocks = 0;
	return ret;
}