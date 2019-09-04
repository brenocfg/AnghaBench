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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {unsigned short s_cluster_ratio; int /*<<< orphan*/  s_sb; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  unsigned short ext4_lblk_t ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 scalar_t__ EXT4_B2C (struct ext4_sb_info*,scalar_t__) ; 
 scalar_t__ EXT4_C2B (struct ext4_sb_info*,long long) ; 
 int EXT4_FREE_BLOCKS_NOFREE_FIRST_CLUSTER ; 
 int EXT4_FREE_BLOCKS_NOFREE_LAST_CLUSTER ; 
 scalar_t__ EXT4_PBLK_COFF (struct ext4_sb_info*,scalar_t__) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,unsigned short,unsigned short,unsigned short,unsigned short) ; 
 unsigned short ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,scalar_t__,unsigned short,int) ; 
 int /*<<< orphan*/  ext_debug (char*,unsigned short,scalar_t__,long long) ; 
 int get_default_free_blocks_flags (struct inode*) ; 
 unsigned short le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_remove_blocks (struct inode*,struct ext4_extent*,unsigned short,unsigned short,long long) ; 

__attribute__((used)) static int ext4_remove_blocks(handle_t *handle, struct inode *inode,
			      struct ext4_extent *ex,
			      long long *partial_cluster,
			      ext4_lblk_t from, ext4_lblk_t to)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	unsigned short ee_len = ext4_ext_get_actual_len(ex);
	ext4_fsblk_t pblk;
	int flags = get_default_free_blocks_flags(inode);

	/*
	 * For bigalloc file systems, we never free a partial cluster
	 * at the beginning of the extent.  Instead, we make a note
	 * that we tried freeing the cluster, and check to see if we
	 * need to free it on a subsequent call to ext4_remove_blocks,
	 * or at the end of ext4_ext_rm_leaf or ext4_ext_remove_space.
	 */
	flags |= EXT4_FREE_BLOCKS_NOFREE_FIRST_CLUSTER;

	trace_ext4_remove_blocks(inode, ex, from, to, *partial_cluster);
	/*
	 * If we have a partial cluster, and it's different from the
	 * cluster of the last block, we need to explicitly free the
	 * partial cluster here.
	 */
	pblk = ext4_ext_pblock(ex) + ee_len - 1;
	if (*partial_cluster > 0 &&
	    *partial_cluster != (long long) EXT4_B2C(sbi, pblk)) {
		ext4_free_blocks(handle, inode, NULL,
				 EXT4_C2B(sbi, *partial_cluster),
				 sbi->s_cluster_ratio, flags);
		*partial_cluster = 0;
	}

#ifdef EXTENTS_STATS
	{
		struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
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
	}
#endif
	if (from >= le32_to_cpu(ex->ee_block)
	    && to == le32_to_cpu(ex->ee_block) + ee_len - 1) {
		/* tail removal */
		ext4_lblk_t num;
		long long first_cluster;

		num = le32_to_cpu(ex->ee_block) + ee_len - from;
		pblk = ext4_ext_pblock(ex) + ee_len - num;
		/*
		 * Usually we want to free partial cluster at the end of the
		 * extent, except for the situation when the cluster is still
		 * used by any other extent (partial_cluster is negative).
		 */
		if (*partial_cluster < 0 &&
		    *partial_cluster == -(long long) EXT4_B2C(sbi, pblk+num-1))
			flags |= EXT4_FREE_BLOCKS_NOFREE_LAST_CLUSTER;

		ext_debug("free last %u blocks starting %llu partial %lld\n",
			  num, pblk, *partial_cluster);
		ext4_free_blocks(handle, inode, NULL, pblk, num, flags);
		/*
		 * If the block range to be freed didn't start at the
		 * beginning of a cluster, and we removed the entire
		 * extent and the cluster is not used by any other extent,
		 * save the partial cluster here, since we might need to
		 * delete if we determine that the truncate or punch hole
		 * operation has removed all of the blocks in the cluster.
		 * If that cluster is used by another extent, preserve its
		 * negative value so it isn't freed later on.
		 *
		 * If the whole extent wasn't freed, we've reached the
		 * start of the truncated/punched region and have finished
		 * removing blocks.  If there's a partial cluster here it's
		 * shared with the remainder of the extent and is no longer
		 * a candidate for removal.
		 */
		if (EXT4_PBLK_COFF(sbi, pblk) && ee_len == num) {
			first_cluster = (long long) EXT4_B2C(sbi, pblk);
			if (first_cluster != -*partial_cluster)
				*partial_cluster = first_cluster;
		} else {
			*partial_cluster = 0;
		}
	} else
		ext4_error(sbi->s_sb, "strange request: removal(2) "
			   "%u-%u from %u:%u",
			   from, to, le32_to_cpu(ex->ee_block), ee_len);
	return 0;
}