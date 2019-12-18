#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct ext4_ext_path {int p_depth; TYPE_1__* p_hdr; struct buffer_head* p_bh; void* p_block; scalar_t__ p_idx; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {scalar_t__ eh_entries; int /*<<< orphan*/  eh_max; scalar_t__ eh_depth; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ EXT_LAST_INDEX (TYPE_1__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_ext_check_inode (struct inode*) ; 
 int ext4_ext_dirty (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int ext4_ext_get_access (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 scalar_t__ ext4_ext_more_to_rm (struct ext4_ext_path*) ; 
 int ext4_ext_rm_idx (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_rm_leaf (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*,unsigned long) ; 
 int /*<<< orphan*/  ext4_ext_space_root (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_idx_pblock (scalar_t__) ; 
 int /*<<< orphan*/  ext4_journal_stop (void*,int /*<<< orphan*/ *) ; 
 TYPE_1__* ext_block_hdr (struct buffer_head*) ; 
 int ext_depth (struct inode*) ; 
 TYPE_1__* ext_inode_hdr (struct inode*) ; 
 int /*<<< orphan*/  extents_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 struct ext4_ext_path* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ext4_ext_path*,int /*<<< orphan*/ ,int) ; 
 struct buffer_head* read_extent_tree_block (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int ext4_ext_remove_space(void *icb, struct inode *inode, unsigned long start)
{
	struct super_block *sb = inode->i_sb;
	int depth = ext_depth(inode);
	struct ext4_ext_path *path;
	handle_t *handle = NULL;
	int i = 0, err = 0;

	/* probably first extent we're gonna free will be last in block */
	/*handle = ext4_journal_start(inode, depth + 1);*/
	/*if (IS_ERR(icb, handle))*/
	/*return PTR_ERR(icb, handle);*/

	/*
	 * we start scanning from right side freeing all the blocks
	 * after i_size and walking into the deep
	 */
	path = kmalloc(sizeof(struct ext4_ext_path) * (depth + 1), GFP_KERNEL);
	if (path == NULL) {
		ext4_journal_stop(icb, handle);
		return -ENOMEM;
	}
	memset(path, 0, sizeof(struct ext4_ext_path) * (depth + 1));
	path[0].p_hdr = ext_inode_hdr(inode);
	if (ext4_ext_check_inode(inode)) {
		err = -EIO;
		goto out;
	}
	path[0].p_depth = depth;

	while (i >= 0 && err == 0) {
		if (i == depth) {
			/* this is leaf block */
			err = ext4_ext_rm_leaf(icb, handle, inode, path, start);
			/* root level have p_bh == NULL, extents_brelse() eats this */
			extents_brelse(path[i].p_bh);
			path[i].p_bh = NULL;
			i--;
			continue;
		}

		/* this is index block */
		if (!path[i].p_hdr) {
			path[i].p_hdr = ext_block_hdr(path[i].p_bh);
		}

		if (!path[i].p_idx) {
			/* this level hasn't touched yet */
			path[i].p_idx = EXT_LAST_INDEX(path[i].p_hdr);
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries)+1;
		} else {
			/* we've already was here, see at next index */
			path[i].p_idx--;
		}

		if (ext4_ext_more_to_rm(path + i)) {
			struct buffer_head *bh;
			/* go to the next level */
			memset(path + i + 1, 0, sizeof(*path));
			bh = read_extent_tree_block(inode, ext4_idx_pblock(path[i].p_idx), path[0].p_depth - (i + 1), 0);
			if (IS_ERR(bh)) {
				/* should we reset i_size? */
				err = -EIO;
				break;
			}
			path[i+1].p_bh = bh;

			/* put actual number of indexes to know is this
			 * number got changed at the next iteration */
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries);
			i++;
		} else {
			/* we finish processing this index, go up */
			if (path[i].p_hdr->eh_entries == 0 && i > 0) {
				/* index is empty, remove it
				 * handle must be already prepared by the
				 * truncatei_leaf() */
				err = ext4_ext_rm_idx(icb, handle, inode, path + i);
			}
			/* root level have p_bh == NULL, extents_brelse() eats this */
			extents_brelse(path[i].p_bh);
			path[i].p_bh = NULL;
			i--;
		}
	}

	/* TODO: flexible tree reduction should be here */
	if (path->p_hdr->eh_entries == 0) {
		/*
		 * truncate to zero freed all the tree
		 * so, we need to correct eh_depth
		 */
		err = ext4_ext_get_access(icb, handle, inode, path);
		if (err == 0) {
			ext_inode_hdr(inode)->eh_depth = 0;
			ext_inode_hdr(inode)->eh_max =
				cpu_to_le16(ext4_ext_space_root(inode, 0));
			err = ext4_ext_dirty(icb, handle, inode, path);
		}
	}
out:
	if (path) {
		ext4_ext_drop_refs(path);
		kfree(path);
	}
	ext4_journal_stop(icb, handle);

	return err;
}