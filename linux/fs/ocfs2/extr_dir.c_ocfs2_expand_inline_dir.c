#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
typedef  int u32 ;
struct super_block {unsigned int s_blocksize_bits; scalar_t__ s_blocksize; } ;
struct ocfs2_super {struct super_block* sb; } ;
struct ocfs2_inode_info {int /*<<< orphan*/  ip_alloc_sem; int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_dyn_features; int /*<<< orphan*/  ip_la_data_resv; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_dir_lookup_result {struct buffer_head* dl_dx_root_bh; struct buffer_head* dl_dx_leaf_bh; int /*<<< orphan*/  dl_hinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  id_data; } ;
struct TYPE_5__ {TYPE_1__ i_data; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_mtime_nsec; int /*<<< orphan*/  i_ctime_nsec; void* i_mtime; void* i_ctime; void* i_size; int /*<<< orphan*/  i_dyn_features; TYPE_2__ id2; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/ * ac_resv; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct inode {struct super_block* i_sb; int /*<<< orphan*/  i_blocks; TYPE_3__ i_ctime; TYPE_3__ i_mtime; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 scalar_t__ OCFS2_SUBALLOC_ALLOC ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __ocfs2_dx_dir_new_cluster (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,struct buffer_head**,int,unsigned int*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 TYPE_3__ current_time (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int dquot_alloc_space_nodirty (struct inode*,int) ; 
 int /*<<< orphan*/  dquot_free_space_nodirty (struct inode*,int) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct buffer_head**) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_add_dir_index_credits (struct super_block*) ; 
 int ocfs2_claim_clusters (int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int,int*,int*) ; 
 int ocfs2_clusters_for_bytes (struct super_block*,unsigned int) ; 
 unsigned int ocfs2_clusters_to_blocks (struct super_block*,int) ; 
 int ocfs2_clusters_to_bytes (struct super_block*,int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_dinode_new_extent_list (struct inode*,struct ocfs2_dinode*) ; 
 scalar_t__ ocfs2_dir_resv_allowed (struct ocfs2_super*) ; 
 int ocfs2_dx_dir_attach_index (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,struct buffer_head*,struct buffer_head*,struct ocfs2_alloc_context*,int,int,struct buffer_head**) ; 
 unsigned int ocfs2_dx_dir_hash_idx (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_dx_dir_index_block (struct inode*,int /*<<< orphan*/ *,struct buffer_head**,int,int*,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_dx_dir_index_root_block (struct inode*,struct buffer_head*,struct buffer_head*) ; 
 struct buffer_head** ocfs2_dx_dir_kmalloc_leaves (struct super_block*,int*) ; 
 int ocfs2_expand_last_dirent (scalar_t__,scalar_t__,struct inode*) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_init_dir_trailer (struct inode*,struct buffer_head*,int) ; 
 int /*<<< orphan*/  ocfs2_init_dx_root_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int ocfs2_inline_to_extents_credits (struct super_block*) ; 
 int /*<<< orphan*/  ocfs2_inode_sector_count (struct inode*) ; 
 int ocfs2_insert_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_journal_access_db (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 scalar_t__ ocfs2_new_dir_wants_trailer (struct inode*) ; 
 int ocfs2_new_dx_should_be_inline (struct inode*,struct buffer_head*) ; 
 int ocfs2_reserve_clusters (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int ocfs2_reserve_new_metadata_blocks (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int) ; 
 scalar_t__ ocfs2_supports_indexed_dirs (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 struct buffer_head* sb_getblk (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_expand_inline_dir(struct inode *dir, struct buffer_head *di_bh,
				   unsigned int blocks_wanted,
				   struct ocfs2_dir_lookup_result *lookup,
				   struct buffer_head **first_block_bh)
{
	u32 alloc, dx_alloc, bit_off, len, num_dx_entries = 0;
	struct super_block *sb = dir->i_sb;
	int ret, i, num_dx_leaves = 0, dx_inline = 0,
		credits = ocfs2_inline_to_extents_credits(sb);
	u64 dx_insert_blkno, blkno,
		bytes = blocks_wanted << sb->s_blocksize_bits;
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	struct ocfs2_inode_info *oi = OCFS2_I(dir);
	struct ocfs2_alloc_context *data_ac = NULL;
	struct ocfs2_alloc_context *meta_ac = NULL;
	struct buffer_head *dirdata_bh = NULL;
	struct buffer_head *dx_root_bh = NULL;
	struct buffer_head **dx_leaves = NULL;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	handle_t *handle;
	struct ocfs2_extent_tree et;
	struct ocfs2_extent_tree dx_et;
	int did_quota = 0, bytes_allocated = 0;

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(dir), di_bh);

	alloc = ocfs2_clusters_for_bytes(sb, bytes);
	dx_alloc = 0;

	down_write(&oi->ip_alloc_sem);

	if (ocfs2_supports_indexed_dirs(osb)) {
		credits += ocfs2_add_dir_index_credits(sb);

		dx_inline = ocfs2_new_dx_should_be_inline(dir, di_bh);
		if (!dx_inline) {
			/* Add one more cluster for an index leaf */
			dx_alloc++;
			dx_leaves = ocfs2_dx_dir_kmalloc_leaves(sb,
								&num_dx_leaves);
			if (!dx_leaves) {
				ret = -ENOMEM;
				mlog_errno(ret);
				goto out;
			}
		}

		/* This gets us the dx_root */
		ret = ocfs2_reserve_new_metadata_blocks(osb, 1, &meta_ac);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	/*
	 * We should never need more than 2 clusters for the unindexed
	 * tree - maximum dirent size is far less than one block. In
	 * fact, the only time we'd need more than one cluster is if
	 * blocksize == clustersize and the dirent won't fit in the
	 * extra space that the expansion to a single block gives. As
	 * of today, that only happens on 4k/4k file systems.
	 */
	BUG_ON(alloc > 2);

	ret = ocfs2_reserve_clusters(osb, alloc + dx_alloc, &data_ac);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * Prepare for worst case allocation scenario of two separate
	 * extents in the unindexed tree.
	 */
	if (alloc == 2)
		credits += OCFS2_SUBALLOC_ALLOC;

	handle = ocfs2_start_trans(osb, credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out;
	}

	ret = dquot_alloc_space_nodirty(dir,
		ocfs2_clusters_to_bytes(osb->sb, alloc + dx_alloc));
	if (ret)
		goto out_commit;
	did_quota = 1;

	if (ocfs2_supports_indexed_dirs(osb) && !dx_inline) {
		/*
		 * Allocate our index cluster first, to maximize the
		 * possibility that unindexed leaves grow
		 * contiguously.
		 */
		ret = __ocfs2_dx_dir_new_cluster(dir, 0, handle, data_ac,
						 dx_leaves, num_dx_leaves,
						 &dx_insert_blkno);
		if (ret) {
			mlog_errno(ret);
			goto out_commit;
		}
		bytes_allocated += ocfs2_clusters_to_bytes(dir->i_sb, 1);
	}

	/*
	 * Try to claim as many clusters as the bitmap can give though
	 * if we only get one now, that's enough to continue. The rest
	 * will be claimed after the conversion to extents.
	 */
	if (ocfs2_dir_resv_allowed(osb))
		data_ac->ac_resv = &oi->ip_la_data_resv;
	ret = ocfs2_claim_clusters(handle, data_ac, 1, &bit_off, &len);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}
	bytes_allocated += ocfs2_clusters_to_bytes(dir->i_sb, 1);

	/*
	 * Operations are carefully ordered so that we set up the new
	 * data block first. The conversion from inline data to
	 * extents follows.
	 */
	blkno = ocfs2_clusters_to_blocks(dir->i_sb, bit_off);
	dirdata_bh = sb_getblk(sb, blkno);
	if (!dirdata_bh) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out_commit;
	}

	ocfs2_set_new_buffer_uptodate(INODE_CACHE(dir), dirdata_bh);

	ret = ocfs2_journal_access_db(handle, INODE_CACHE(dir), dirdata_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	memcpy(dirdata_bh->b_data, di->id2.i_data.id_data, i_size_read(dir));
	memset(dirdata_bh->b_data + i_size_read(dir), 0,
	       sb->s_blocksize - i_size_read(dir));
	i = ocfs2_expand_last_dirent(dirdata_bh->b_data, i_size_read(dir), dir);
	if (ocfs2_new_dir_wants_trailer(dir)) {
		/*
		 * Prepare the dir trailer up front. It will otherwise look
		 * like a valid dirent. Even if inserting the index fails
		 * (unlikely), then all we'll have done is given first dir
		 * block a small amount of fragmentation.
		 */
		ocfs2_init_dir_trailer(dir, dirdata_bh, i);
	}

	ocfs2_update_inode_fsync_trans(handle, dir, 1);
	ocfs2_journal_dirty(handle, dirdata_bh);

	if (ocfs2_supports_indexed_dirs(osb) && !dx_inline) {
		/*
		 * Dx dirs with an external cluster need to do this up
		 * front. Inline dx root's get handled later, after
		 * we've allocated our root block. We get passed back
		 * a total number of items so that dr_num_entries can
		 * be correctly set once the dx_root has been
		 * allocated.
		 */
		ret = ocfs2_dx_dir_index_block(dir, handle, dx_leaves,
					       num_dx_leaves, &num_dx_entries,
					       dirdata_bh);
		if (ret) {
			mlog_errno(ret);
			goto out_commit;
		}
	}

	/*
	 * Set extent, i_size, etc on the directory. After this, the
	 * inode should contain the same exact dirents as before and
	 * be fully accessible from system calls.
	 *
	 * We let the later dirent insert modify c/mtime - to the user
	 * the data hasn't changed.
	 */
	ret = ocfs2_journal_access_di(handle, INODE_CACHE(dir), di_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features &= ~OCFS2_INLINE_DATA_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	spin_unlock(&oi->ip_lock);

	ocfs2_dinode_new_extent_list(dir, di);

	i_size_write(dir, sb->s_blocksize);
	dir->i_mtime = dir->i_ctime = current_time(dir);

	di->i_size = cpu_to_le64(sb->s_blocksize);
	di->i_ctime = di->i_mtime = cpu_to_le64(dir->i_ctime.tv_sec);
	di->i_ctime_nsec = di->i_mtime_nsec = cpu_to_le32(dir->i_ctime.tv_nsec);
	ocfs2_update_inode_fsync_trans(handle, dir, 1);

	/*
	 * This should never fail as our extent list is empty and all
	 * related blocks have been journaled already.
	 */
	ret = ocfs2_insert_extent(handle, &et, 0, blkno, len,
				  0, NULL);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	/*
	 * Set i_blocks after the extent insert for the most up to
	 * date ip_clusters value.
	 */
	dir->i_blocks = ocfs2_inode_sector_count(dir);

	ocfs2_journal_dirty(handle, di_bh);

	if (ocfs2_supports_indexed_dirs(osb)) {
		ret = ocfs2_dx_dir_attach_index(osb, handle, dir, di_bh,
						dirdata_bh, meta_ac, dx_inline,
						num_dx_entries, &dx_root_bh);
		if (ret) {
			mlog_errno(ret);
			goto out_commit;
		}

		if (dx_inline) {
			ocfs2_dx_dir_index_root_block(dir, dx_root_bh,
						      dirdata_bh);
		} else {
			ocfs2_init_dx_root_extent_tree(&dx_et,
						       INODE_CACHE(dir),
						       dx_root_bh);
			ret = ocfs2_insert_extent(handle, &dx_et, 0,
						  dx_insert_blkno, 1, 0, NULL);
			if (ret)
				mlog_errno(ret);
		}
	}

	/*
	 * We asked for two clusters, but only got one in the 1st
	 * pass. Claim the 2nd cluster as a separate extent.
	 */
	if (alloc > len) {
		ret = ocfs2_claim_clusters(handle, data_ac, 1, &bit_off,
					   &len);
		if (ret) {
			mlog_errno(ret);
			goto out_commit;
		}
		blkno = ocfs2_clusters_to_blocks(dir->i_sb, bit_off);

		ret = ocfs2_insert_extent(handle, &et, 1,
					  blkno, len, 0, NULL);
		if (ret) {
			mlog_errno(ret);
			goto out_commit;
		}
		bytes_allocated += ocfs2_clusters_to_bytes(dir->i_sb, 1);
	}

	*first_block_bh = dirdata_bh;
	dirdata_bh = NULL;
	if (ocfs2_supports_indexed_dirs(osb)) {
		unsigned int off;

		if (!dx_inline) {
			/*
			 * We need to return the correct block within the
			 * cluster which should hold our entry.
			 */
			off = ocfs2_dx_dir_hash_idx(osb,
						    &lookup->dl_hinfo);
			get_bh(dx_leaves[off]);
			lookup->dl_dx_leaf_bh = dx_leaves[off];
		}
		lookup->dl_dx_root_bh = dx_root_bh;
		dx_root_bh = NULL;
	}

out_commit:
	if (ret < 0 && did_quota)
		dquot_free_space_nodirty(dir, bytes_allocated);

	ocfs2_commit_trans(osb, handle);

out:
	up_write(&oi->ip_alloc_sem);
	if (data_ac)
		ocfs2_free_alloc_context(data_ac);
	if (meta_ac)
		ocfs2_free_alloc_context(meta_ac);

	if (dx_leaves) {
		for (i = 0; i < num_dx_leaves; i++)
			brelse(dx_leaves[i]);
		kfree(dx_leaves);
	}

	brelse(dirdata_bh);
	brelse(dx_root_bh);

	return ret;
}