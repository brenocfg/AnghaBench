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
struct nilfs_btree_path {struct buffer_head* bp_bh; int /*<<< orphan*/  bp_index; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_nilfs_volatile (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 struct inode* nilfs_bmap_get_dat (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_btree_commit_propagate_v (struct nilfs_bmap*,struct nilfs_btree_path*,int,int,struct buffer_head*,struct inode*) ; 
 struct nilfs_btree_node* nilfs_btree_get_node (struct nilfs_bmap*,struct nilfs_btree_path*,int,int*) ; 
 int /*<<< orphan*/  nilfs_btree_node_get_ptr (struct nilfs_btree_node*,int /*<<< orphan*/ ,int) ; 
 int nilfs_btree_prepare_propagate_v (struct nilfs_bmap*,struct nilfs_btree_path*,int,int*,struct inode*) ; 
 int nilfs_dat_mark_dirty (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_btree_propagate_v(struct nilfs_bmap *btree,
				   struct nilfs_btree_path *path,
				   int level, struct buffer_head *bh)
{
	int maxlevel = 0, ret;
	struct nilfs_btree_node *parent;
	struct inode *dat = nilfs_bmap_get_dat(btree);
	__u64 ptr;
	int ncmax;

	get_bh(bh);
	path[level].bp_bh = bh;
	ret = nilfs_btree_prepare_propagate_v(btree, path, level, &maxlevel,
					      dat);
	if (ret < 0)
		goto out;

	if (buffer_nilfs_volatile(path[level].bp_bh)) {
		parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
		ptr = nilfs_btree_node_get_ptr(parent,
					       path[level + 1].bp_index,
					       ncmax);
		ret = nilfs_dat_mark_dirty(dat, ptr);
		if (ret < 0)
			goto out;
	}

	nilfs_btree_commit_propagate_v(btree, path, level, maxlevel, bh, dat);

 out:
	brelse(path[level].bp_bh);
	path[level].bp_bh = NULL;
	return ret;
}