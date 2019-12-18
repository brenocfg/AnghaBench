#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct partial_cluster {scalar_t__ state; scalar_t__ lblk; void* pclu; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {int s_cluster_ratio; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {int p_maxdepth; int p_depth; TYPE_1__* p_hdr; struct ext4_ext_path* p_bh; void* p_block; scalar_t__ p_idx; struct ext4_extent* p_ext; } ;
struct buffer_head {int p_maxdepth; int p_depth; TYPE_1__* p_hdr; struct buffer_head* p_bh; void* p_block; scalar_t__ p_idx; struct ext4_extent* p_ext; } ;
typedef  struct ext4_ext_path handle_t ;
typedef  int ext4_lblk_t ;
typedef  int ext4_fsblk_t ;
struct TYPE_6__ {scalar_t__ eh_entries; int /*<<< orphan*/  eh_max; scalar_t__ eh_depth; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFSCORRUPTED ; 
 int ENOMEM ; 
 void* EXT4_B2C (struct ext4_sb_info*,int) ; 
 int /*<<< orphan*/  EXT4_C2B (struct ext4_sb_info*,void*) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,int) ; 
 int /*<<< orphan*/  EXT4_EX_NOCACHE ; 
 int EXT4_FREE_BLOCKS_RERESERVE_CLUSTER ; 
 int /*<<< orphan*/  EXT4_HT_TRUNCATE ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT_FIRST_INDEX (TYPE_1__*) ; 
 scalar_t__ EXT_LAST_INDEX (TYPE_1__*) ; 
 int EXT_MAX_BLOCKS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  brelse (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_ext_check (struct inode*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int ext4_ext_dirty (struct ext4_ext_path*,struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int ext4_ext_get_access (struct ext4_ext_path*,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_more_to_rm (struct ext4_ext_path*) ; 
 int ext4_ext_pblock (struct ext4_extent*) ; 
 int ext4_ext_rm_idx (struct ext4_ext_path*,struct inode*,struct ext4_ext_path*,int) ; 
 int ext4_ext_rm_leaf (struct ext4_ext_path*,struct inode*,struct ext4_ext_path*,struct partial_cluster*,int,int) ; 
 int ext4_ext_search_right (struct inode*,struct ext4_ext_path*,int*,int*,struct ext4_extent**) ; 
 int /*<<< orphan*/  ext4_ext_space_root (struct inode*,int /*<<< orphan*/ ) ; 
 struct ext4_ext_path* ext4_find_extent (struct inode*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ext4_force_split_extent_at (struct ext4_ext_path*,struct inode*,struct ext4_ext_path**,int,int) ; 
 int /*<<< orphan*/  ext4_free_blocks (struct ext4_ext_path*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ext4_idx_pblock (scalar_t__) ; 
 scalar_t__ ext4_is_pending (struct inode*,scalar_t__) ; 
 struct ext4_ext_path* ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_rereserve_cluster (struct inode*,scalar_t__) ; 
 TYPE_1__* ext_block_hdr (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext_debug (char*,...) ; 
 int ext_depth (struct inode*) ; 
 TYPE_1__* ext_inode_hdr (struct inode*) ; 
 int get_default_free_blocks_flags (struct inode*) ; 
 scalar_t__ initial ; 
 struct ext4_ext_path* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 void* le16_to_cpu (scalar_t__) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ext4_ext_path*,int /*<<< orphan*/ ,int) ; 
 void* nofree ; 
 struct ext4_ext_path* read_extent_tree_block (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ tofree ; 
 int /*<<< orphan*/  trace_ext4_ext_remove_space (struct inode*,int,int,int) ; 
 int /*<<< orphan*/  trace_ext4_ext_remove_space_done (struct inode*,int,int,int,struct partial_cluster*,scalar_t__) ; 

int ext4_ext_remove_space(struct inode *inode, ext4_lblk_t start,
			  ext4_lblk_t end)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	int depth = ext_depth(inode);
	struct ext4_ext_path *path = NULL;
	struct partial_cluster partial;
	handle_t *handle;
	int i = 0, err = 0;

	partial.pclu = 0;
	partial.lblk = 0;
	partial.state = initial;

	ext_debug("truncate since %u to %u\n", start, end);

	/* probably first extent we're gonna free will be last in block */
	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE, depth + 1);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

again:
	trace_ext4_ext_remove_space(inode, start, end, depth);

	/*
	 * Check if we are removing extents inside the extent tree. If that
	 * is the case, we are going to punch a hole inside the extent tree
	 * so we have to check whether we need to split the extent covering
	 * the last block to remove so we can easily remove the part of it
	 * in ext4_ext_rm_leaf().
	 */
	if (end < EXT_MAX_BLOCKS - 1) {
		struct ext4_extent *ex;
		ext4_lblk_t ee_block, ex_end, lblk;
		ext4_fsblk_t pblk;

		/* find extent for or closest extent to this block */
		path = ext4_find_extent(inode, end, NULL, EXT4_EX_NOCACHE);
		if (IS_ERR(path)) {
			ext4_journal_stop(handle);
			return PTR_ERR(path);
		}
		depth = ext_depth(inode);
		/* Leaf not may not exist only if inode has no blocks at all */
		ex = path[depth].p_ext;
		if (!ex) {
			if (depth) {
				EXT4_ERROR_INODE(inode,
						 "path[%d].p_hdr == NULL",
						 depth);
				err = -EFSCORRUPTED;
			}
			goto out;
		}

		ee_block = le32_to_cpu(ex->ee_block);
		ex_end = ee_block + ext4_ext_get_actual_len(ex) - 1;

		/*
		 * See if the last block is inside the extent, if so split
		 * the extent at 'end' block so we can easily remove the
		 * tail of the first part of the split extent in
		 * ext4_ext_rm_leaf().
		 */
		if (end >= ee_block && end < ex_end) {

			/*
			 * If we're going to split the extent, note that
			 * the cluster containing the block after 'end' is
			 * in use to avoid freeing it when removing blocks.
			 */
			if (sbi->s_cluster_ratio > 1) {
				pblk = ext4_ext_pblock(ex) + end - ee_block + 2;
				partial.pclu = EXT4_B2C(sbi, pblk);
				partial.state = nofree;
			}

			/*
			 * Split the extent in two so that 'end' is the last
			 * block in the first new extent. Also we should not
			 * fail removing space due to ENOSPC so try to use
			 * reserved block if that happens.
			 */
			err = ext4_force_split_extent_at(handle, inode, &path,
							 end + 1, 1);
			if (err < 0)
				goto out;

		} else if (sbi->s_cluster_ratio > 1 && end >= ex_end &&
			   partial.state == initial) {
			/*
			 * If we're punching, there's an extent to the right.
			 * If the partial cluster hasn't been set, set it to
			 * that extent's first cluster and its state to nofree
			 * so it won't be freed should it contain blocks to be
			 * removed. If it's already set (tofree/nofree), we're
			 * retrying and keep the original partial cluster info
			 * so a cluster marked tofree as a result of earlier
			 * extent removal is not lost.
			 */
			lblk = ex_end + 1;
			err = ext4_ext_search_right(inode, path, &lblk, &pblk,
						    &ex);
			if (err)
				goto out;
			if (pblk) {
				partial.pclu = EXT4_B2C(sbi, pblk);
				partial.state = nofree;
			}
		}
	}
	/*
	 * We start scanning from right side, freeing all the blocks
	 * after i_size and walking into the tree depth-wise.
	 */
	depth = ext_depth(inode);
	if (path) {
		int k = i = depth;
		while (--k > 0)
			path[k].p_block =
				le16_to_cpu(path[k].p_hdr->eh_entries)+1;
	} else {
		path = kcalloc(depth + 1, sizeof(struct ext4_ext_path),
			       GFP_NOFS);
		if (path == NULL) {
			ext4_journal_stop(handle);
			return -ENOMEM;
		}
		path[0].p_maxdepth = path[0].p_depth = depth;
		path[0].p_hdr = ext_inode_hdr(inode);
		i = 0;

		if (ext4_ext_check(inode, path[0].p_hdr, depth, 0)) {
			err = -EFSCORRUPTED;
			goto out;
		}
	}
	err = 0;

	while (i >= 0 && err == 0) {
		if (i == depth) {
			/* this is leaf block */
			err = ext4_ext_rm_leaf(handle, inode, path,
					       &partial, start, end);
			/* root level has p_bh == NULL, brelse() eats this */
			brelse(path[i].p_bh);
			path[i].p_bh = NULL;
			i--;
			continue;
		}

		/* this is index block */
		if (!path[i].p_hdr) {
			ext_debug("initialize header\n");
			path[i].p_hdr = ext_block_hdr(path[i].p_bh);
		}

		if (!path[i].p_idx) {
			/* this level hasn't been touched yet */
			path[i].p_idx = EXT_LAST_INDEX(path[i].p_hdr);
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries)+1;
			ext_debug("init index ptr: hdr 0x%p, num %d\n",
				  path[i].p_hdr,
				  le16_to_cpu(path[i].p_hdr->eh_entries));
		} else {
			/* we were already here, see at next index */
			path[i].p_idx--;
		}

		ext_debug("level %d - index, first 0x%p, cur 0x%p\n",
				i, EXT_FIRST_INDEX(path[i].p_hdr),
				path[i].p_idx);
		if (ext4_ext_more_to_rm(path + i)) {
			struct buffer_head *bh;
			/* go to the next level */
			ext_debug("move to level %d (block %llu)\n",
				  i + 1, ext4_idx_pblock(path[i].p_idx));
			memset(path + i + 1, 0, sizeof(*path));
			bh = read_extent_tree_block(inode,
				ext4_idx_pblock(path[i].p_idx), depth - i - 1,
				EXT4_EX_NOCACHE);
			if (IS_ERR(bh)) {
				/* should we reset i_size? */
				err = PTR_ERR(bh);
				break;
			}
			/* Yield here to deal with large extent trees.
			 * Should be a no-op if we did IO above. */
			cond_resched();
			if (WARN_ON(i + 1 > depth)) {
				err = -EFSCORRUPTED;
				break;
			}
			path[i + 1].p_bh = bh;

			/* save actual number of indexes since this
			 * number is changed at the next iteration */
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries);
			i++;
		} else {
			/* we finished processing this index, go up */
			if (path[i].p_hdr->eh_entries == 0 && i > 0) {
				/* index is empty, remove it;
				 * handle must be already prepared by the
				 * truncatei_leaf() */
				err = ext4_ext_rm_idx(handle, inode, path, i);
			}
			/* root level has p_bh == NULL, brelse() eats this */
			brelse(path[i].p_bh);
			path[i].p_bh = NULL;
			i--;
			ext_debug("return to level %d\n", i);
		}
	}

	trace_ext4_ext_remove_space_done(inode, start, end, depth, &partial,
					 path->p_hdr->eh_entries);

	/*
	 * if there's a partial cluster and we have removed the first extent
	 * in the file, then we also free the partial cluster, if any
	 */
	if (partial.state == tofree && err == 0) {
		int flags = get_default_free_blocks_flags(inode);

		if (ext4_is_pending(inode, partial.lblk))
			flags |= EXT4_FREE_BLOCKS_RERESERVE_CLUSTER;
		ext4_free_blocks(handle, inode, NULL,
				 EXT4_C2B(sbi, partial.pclu),
				 sbi->s_cluster_ratio, flags);
		if (flags & EXT4_FREE_BLOCKS_RERESERVE_CLUSTER)
			ext4_rereserve_cluster(inode, partial.lblk);
		partial.state = initial;
	}

	/* TODO: flexible tree reduction should be here */
	if (path->p_hdr->eh_entries == 0) {
		/*
		 * truncate to zero freed all the tree,
		 * so we need to correct eh_depth
		 */
		err = ext4_ext_get_access(handle, inode, path);
		if (err == 0) {
			ext_inode_hdr(inode)->eh_depth = 0;
			ext_inode_hdr(inode)->eh_max =
				cpu_to_le16(ext4_ext_space_root(inode, 0));
			err = ext4_ext_dirty(handle, inode, path);
		}
	}
out:
	ext4_ext_drop_refs(path);
	kfree(path);
	path = NULL;
	if (err == -EAGAIN)
		goto again;
	ext4_journal_stop(handle);

	return err;
}