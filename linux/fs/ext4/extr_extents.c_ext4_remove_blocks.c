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
struct partial_cluster {scalar_t__ state; scalar_t__ pclu; unsigned short lblk; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {unsigned short s_ext_blocks; unsigned short s_ext_min; unsigned short s_ext_max; scalar_t__ s_depth_max; unsigned short s_cluster_ratio; int /*<<< orphan*/  s_ext_stats_lock; int /*<<< orphan*/  s_ext_extents; int /*<<< orphan*/  s_sb; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  unsigned short ext4_lblk_t ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 scalar_t__ EXT4_B2C (struct ext4_sb_info*,scalar_t__) ; 
 scalar_t__ EXT4_C2B (struct ext4_sb_info*,scalar_t__) ; 
 int EXT4_FREE_BLOCKS_NOFREE_FIRST_CLUSTER ; 
 int EXT4_FREE_BLOCKS_NOFREE_LAST_CLUSTER ; 
 int EXT4_FREE_BLOCKS_RERESERVE_CLUSTER ; 
 unsigned short EXT4_LBLK_CMASK (struct ext4_sb_info*,unsigned short) ; 
 int EXT4_LBLK_COFF (struct ext4_sb_info*,unsigned short) ; 
 scalar_t__ EXT4_PBLK_CMASK (struct ext4_sb_info*,scalar_t__) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,unsigned short,unsigned short,unsigned short,unsigned short) ; 
 unsigned short ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,scalar_t__,unsigned short,int) ; 
 scalar_t__ ext4_is_pending (struct inode*,unsigned short) ; 
 int /*<<< orphan*/  ext4_rereserve_cluster (struct inode*,unsigned short) ; 
 scalar_t__ ext_depth (struct inode*) ; 
 int get_default_free_blocks_flags (struct inode*) ; 
 scalar_t__ initial ; 
 unsigned short le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ nofree ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tofree ; 
 int /*<<< orphan*/  trace_ext4_remove_blocks (struct inode*,struct ext4_extent*,unsigned short,unsigned short,struct partial_cluster*) ; 

__attribute__((used)) static int ext4_remove_blocks(handle_t *handle, struct inode *inode,
			      struct ext4_extent *ex,
			      struct partial_cluster *partial,
			      ext4_lblk_t from, ext4_lblk_t to)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	unsigned short ee_len = ext4_ext_get_actual_len(ex);
	ext4_fsblk_t last_pblk, pblk;
	ext4_lblk_t num;
	int flags;

	/* only extent tail removal is allowed */
	if (from < le32_to_cpu(ex->ee_block) ||
	    to != le32_to_cpu(ex->ee_block) + ee_len - 1) {
		ext4_error(sbi->s_sb,
			   "strange request: removal(2) %u-%u from %u:%u",
			   from, to, le32_to_cpu(ex->ee_block), ee_len);
		return 0;
	}

#ifdef EXTENTS_STATS
	spin_lock(&sbi->s_ext_stats_lock);
	sbi->s_ext_blocks += ee_len;
	sbi->s_ext_extents++;
	if (ee_len < sbi->s_ext_min)
		sbi->s_ext_min = ee_len;
	if (ee_len > sbi->s_ext_max)
		sbi->s_ext_max = ee_len;
	if (ext_depth(inode) > sbi->s_depth_max)
		sbi->s_depth_max = ext_depth(inode);
	spin_unlock(&sbi->s_ext_stats_lock);
#endif

	trace_ext4_remove_blocks(inode, ex, from, to, partial);

	/*
	 * if we have a partial cluster, and it's different from the
	 * cluster of the last block in the extent, we free it
	 */
	last_pblk = ext4_ext_pblock(ex) + ee_len - 1;

	if (partial->state != initial &&
	    partial->pclu != EXT4_B2C(sbi, last_pblk)) {
		if (partial->state == tofree) {
			flags = get_default_free_blocks_flags(inode);
			if (ext4_is_pending(inode, partial->lblk))
				flags |= EXT4_FREE_BLOCKS_RERESERVE_CLUSTER;
			ext4_free_blocks(handle, inode, NULL,
					 EXT4_C2B(sbi, partial->pclu),
					 sbi->s_cluster_ratio, flags);
			if (flags & EXT4_FREE_BLOCKS_RERESERVE_CLUSTER)
				ext4_rereserve_cluster(inode, partial->lblk);
		}
		partial->state = initial;
	}

	num = le32_to_cpu(ex->ee_block) + ee_len - from;
	pblk = ext4_ext_pblock(ex) + ee_len - num;

	/*
	 * We free the partial cluster at the end of the extent (if any),
	 * unless the cluster is used by another extent (partial_cluster
	 * state is nofree).  If a partial cluster exists here, it must be
	 * shared with the last block in the extent.
	 */
	flags = get_default_free_blocks_flags(inode);

	/* partial, left end cluster aligned, right end unaligned */
	if ((EXT4_LBLK_COFF(sbi, to) != sbi->s_cluster_ratio - 1) &&
	    (EXT4_LBLK_CMASK(sbi, to) >= from) &&
	    (partial->state != nofree)) {
		if (ext4_is_pending(inode, to))
			flags |= EXT4_FREE_BLOCKS_RERESERVE_CLUSTER;
		ext4_free_blocks(handle, inode, NULL,
				 EXT4_PBLK_CMASK(sbi, last_pblk),
				 sbi->s_cluster_ratio, flags);
		if (flags & EXT4_FREE_BLOCKS_RERESERVE_CLUSTER)
			ext4_rereserve_cluster(inode, to);
		partial->state = initial;
		flags = get_default_free_blocks_flags(inode);
	}

	flags |= EXT4_FREE_BLOCKS_NOFREE_LAST_CLUSTER;

	/*
	 * For bigalloc file systems, we never free a partial cluster
	 * at the beginning of the extent.  Instead, we check to see if we
	 * need to free it on a subsequent call to ext4_remove_blocks,
	 * or at the end of ext4_ext_rm_leaf or ext4_ext_remove_space.
	 */
	flags |= EXT4_FREE_BLOCKS_NOFREE_FIRST_CLUSTER;
	ext4_free_blocks(handle, inode, NULL, pblk, num, flags);

	/* reset the partial cluster if we've freed past it */
	if (partial->state != initial && partial->pclu != EXT4_B2C(sbi, pblk))
		partial->state = initial;

	/*
	 * If we've freed the entire extent but the beginning is not left
	 * cluster aligned and is not marked as ineligible for freeing we
	 * record the partial cluster at the beginning of the extent.  It
	 * wasn't freed by the preceding ext4_free_blocks() call, and we
	 * need to look farther to the left to determine if it's to be freed
	 * (not shared with another extent). Else, reset the partial
	 * cluster - we're either  done freeing or the beginning of the
	 * extent is left cluster aligned.
	 */
	if (EXT4_LBLK_COFF(sbi, from) && num == ee_len) {
		if (partial->state == initial) {
			partial->pclu = EXT4_B2C(sbi, pblk);
			partial->lblk = from;
			partial->state = tofree;
		}
	} else {
		partial->state = initial;
	}

	return 0;
}