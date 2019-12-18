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
struct ext4_extent_header {int /*<<< orphan*/  eh_max; int /*<<< orphan*/  eh_entries; } ;
struct ext4_ext_path {short p_maxdepth; short p_depth; int /*<<< orphan*/ * p_ext; int /*<<< orphan*/  p_block; int /*<<< orphan*/ * p_idx; struct ext4_extent_header* p_hdr; struct buffer_head* p_bh; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 struct ext4_ext_path* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,short,short) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_ext_binsearch (struct inode*,struct ext4_ext_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_binsearch_idx (struct inode*,struct ext4_ext_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_pblock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_ext_show_path (struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_idx_pblock (int /*<<< orphan*/ *) ; 
 struct ext4_extent_header* ext_block_hdr (struct buffer_head*) ; 
 int /*<<< orphan*/  ext_debug (char*,short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 short ext_depth (struct inode*) ; 
 struct ext4_extent_header* ext_inode_hdr (struct inode*) ; 
 int /*<<< orphan*/  extents_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 struct ext4_ext_path* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* read_extent_tree_block (struct inode*,int /*<<< orphan*/ ,short,int) ; 
 scalar_t__ unlikely (int) ; 

struct ext4_ext_path *
ext4_find_extent(struct inode *inode, ext4_lblk_t block,
		struct ext4_ext_path **orig_path, int flags)
{
	struct ext4_extent_header *eh;
	struct buffer_head *bh;
	struct ext4_ext_path *path = orig_path ? *orig_path : NULL;
	short int depth, i, ppos = 0;
	int ret;

	eh = ext_inode_hdr(inode);
	depth = ext_depth(inode);

	if (path) {
		ext4_ext_drop_refs(path);
		if (depth > path[0].p_maxdepth) {
			kfree(path);
			*orig_path = path = NULL;
		}
	}
	if (!path) {
		/* account possible depth increase */
		path = kzalloc(sizeof(struct ext4_ext_path) * (depth + 2),
				GFP_NOFS);
		if (unlikely(!path))
			return ERR_PTR(-ENOMEM);
		path[0].p_maxdepth = depth + 1;
	}
	path[0].p_hdr = eh;
	path[0].p_bh = NULL;

	i = depth;
	/* walk through the tree */
	while (i) {
		ext_debug("depth %d: num %d, max %d\n",
				ppos, le16_to_cpu(eh->eh_entries), le16_to_cpu(eh->eh_max));

		ext4_ext_binsearch_idx(inode, path + ppos, block);
		path[ppos].p_block = ext4_idx_pblock(path[ppos].p_idx);
		path[ppos].p_depth = i;
		path[ppos].p_ext = NULL;

		bh = read_extent_tree_block(inode, path[ppos].p_block, --i,
				flags);
		if (unlikely(IS_ERR(bh))) {
			ret = PTR_ERR(bh);
			goto err;
		}

		eh = ext_block_hdr(bh);
		ppos++;
		if (unlikely(ppos > depth)) {
			extents_brelse(bh);
			EXT4_ERROR_INODE(inode,
					"ppos %d > depth %d", ppos, depth);
			ret = -EIO;
			goto err;
		}
		path[ppos].p_bh = bh;
		path[ppos].p_hdr = eh;
	}

	path[ppos].p_depth = i;
	path[ppos].p_ext = NULL;
	path[ppos].p_idx = NULL;

	/* find extent */
	ext4_ext_binsearch(inode, path + ppos, block);
	/* if not an empty leaf */
	if (path[ppos].p_ext)
		path[ppos].p_block = ext4_ext_pblock(path[ppos].p_ext);

	ext4_ext_show_path(inode, path);

	return path;

err:
	ext4_ext_drop_refs(path);
	if (path) {
		kfree(path);
		if (orig_path)
			*orig_path = NULL;
	}
	return ERR_PTR(ret);
}