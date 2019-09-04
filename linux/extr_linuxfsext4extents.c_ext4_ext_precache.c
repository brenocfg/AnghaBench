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
struct inode {int dummy; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_data_sem; } ;
struct ext4_ext_path {scalar_t__ p_idx; int /*<<< orphan*/  p_hdr; struct buffer_head* p_bh; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_EX_FORCE_CACHE ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_STATE_EXT_PRECACHED ; 
 void* EXT_FIRST_INDEX (int /*<<< orphan*/ ) ; 
 scalar_t__ EXT_LAST_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ext4_ext_check (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_idx_pblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_block_hdr (struct buffer_head*) ; 
 int ext_depth (struct inode*) ; 
 int /*<<< orphan*/  ext_inode_hdr (struct inode*) ; 
 struct ext4_ext_path* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 struct buffer_head* read_extent_tree_block (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ext4_ext_precache(struct inode *inode)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	struct ext4_ext_path *path = NULL;
	struct buffer_head *bh;
	int i = 0, depth, ret = 0;

	if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		return 0;	/* not an extent-mapped inode */

	down_read(&ei->i_data_sem);
	depth = ext_depth(inode);

	path = kcalloc(depth + 1, sizeof(struct ext4_ext_path),
		       GFP_NOFS);
	if (path == NULL) {
		up_read(&ei->i_data_sem);
		return -ENOMEM;
	}

	/* Don't cache anything if there are no external extent blocks */
	if (depth == 0)
		goto out;
	path[0].p_hdr = ext_inode_hdr(inode);
	ret = ext4_ext_check(inode, path[0].p_hdr, depth, 0);
	if (ret)
		goto out;
	path[0].p_idx = EXT_FIRST_INDEX(path[0].p_hdr);
	while (i >= 0) {
		/*
		 * If this is a leaf block or we've reached the end of
		 * the index block, go up
		 */
		if ((i == depth) ||
		    path[i].p_idx > EXT_LAST_INDEX(path[i].p_hdr)) {
			brelse(path[i].p_bh);
			path[i].p_bh = NULL;
			i--;
			continue;
		}
		bh = read_extent_tree_block(inode,
					    ext4_idx_pblock(path[i].p_idx++),
					    depth - i - 1,
					    EXT4_EX_FORCE_CACHE);
		if (IS_ERR(bh)) {
			ret = PTR_ERR(bh);
			break;
		}
		i++;
		path[i].p_bh = bh;
		path[i].p_hdr = ext_block_hdr(bh);
		path[i].p_idx = EXT_FIRST_INDEX(path[i].p_hdr);
	}
	ext4_set_inode_state(inode, EXT4_STATE_EXT_PRECACHED);
out:
	up_read(&ei->i_data_sem);
	ext4_ext_drop_refs(path);
	kfree(path);
	return ret;
}