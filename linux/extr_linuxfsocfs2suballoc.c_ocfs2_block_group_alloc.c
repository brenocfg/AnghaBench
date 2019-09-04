#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u16 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_bits; int /*<<< orphan*/  bg_free_bits_count; int /*<<< orphan*/  bg_blkno; int /*<<< orphan*/  bg_chain; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_total; int /*<<< orphan*/  i_used; } ;
struct TYPE_9__ {TYPE_3__ bitmap1; } ;
struct ocfs2_chain_list {int /*<<< orphan*/  cl_cpg; int /*<<< orphan*/  cl_next_free_rec; int /*<<< orphan*/  cl_count; TYPE_2__* cl_recs; } ;
struct TYPE_6__ {struct ocfs2_chain_list i_chain; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_clusters; TYPE_4__ id1; TYPE_1__ id2; } ;
struct ocfs2_alloc_context {scalar_t__ ac_last_group; } ;
struct inode {int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  struct buffer_head handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_clusters; } ;
struct TYPE_7__ {int /*<<< orphan*/  c_blkno; int /*<<< orphan*/  c_total; int /*<<< orphan*/  c_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 TYPE_5__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct buffer_head* ocfs2_block_group_alloc_contig (struct ocfs2_super*,struct buffer_head*,struct inode*,struct ocfs2_alloc_context*,struct ocfs2_chain_list*) ; 
 struct buffer_head* ocfs2_block_group_alloc_discontig (struct buffer_head*,struct inode*,struct ocfs2_alloc_context*,struct ocfs2_chain_list*) ; 
 int ocfs2_calc_group_alloc_credits (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_inode_sector_count (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_is_cluster_bitmap (struct inode*) ; 
 int ocfs2_journal_access_di (struct buffer_head*,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (struct buffer_head*,struct buffer_head*) ; 
 int ocfs2_reserve_clusters_with_limit (struct ocfs2_super*,scalar_t__,scalar_t__,int,struct ocfs2_alloc_context**) ; 
 struct buffer_head* ocfs2_start_trans (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (struct buffer_head*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_block_group_alloc (unsigned long long) ; 

__attribute__((used)) static int ocfs2_block_group_alloc(struct ocfs2_super *osb,
				   struct inode *alloc_inode,
				   struct buffer_head *bh,
				   u64 max_block,
				   u64 *last_alloc_group,
				   int flags)
{
	int status, credits;
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) bh->b_data;
	struct ocfs2_chain_list *cl;
	struct ocfs2_alloc_context *ac = NULL;
	handle_t *handle = NULL;
	u16 alloc_rec;
	struct buffer_head *bg_bh = NULL;
	struct ocfs2_group_desc *bg;

	BUG_ON(ocfs2_is_cluster_bitmap(alloc_inode));

	cl = &fe->id2.i_chain;
	status = ocfs2_reserve_clusters_with_limit(osb,
						   le16_to_cpu(cl->cl_cpg),
						   max_block, flags, &ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	credits = ocfs2_calc_group_alloc_credits(osb->sb,
						 le16_to_cpu(cl->cl_cpg));
	handle = ocfs2_start_trans(osb, credits);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto bail;
	}

	if (last_alloc_group && *last_alloc_group != 0) {
		trace_ocfs2_block_group_alloc(
				(unsigned long long)*last_alloc_group);
		ac->ac_last_group = *last_alloc_group;
	}

	bg_bh = ocfs2_block_group_alloc_contig(osb, handle, alloc_inode,
					       ac, cl);
	if (IS_ERR(bg_bh) && (PTR_ERR(bg_bh) == -ENOSPC))
		bg_bh = ocfs2_block_group_alloc_discontig(handle,
							  alloc_inode,
							  ac, cl);
	if (IS_ERR(bg_bh)) {
		status = PTR_ERR(bg_bh);
		bg_bh = NULL;
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}
	bg = (struct ocfs2_group_desc *) bg_bh->b_data;

	status = ocfs2_journal_access_di(handle, INODE_CACHE(alloc_inode),
					 bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	alloc_rec = le16_to_cpu(bg->bg_chain);
	le32_add_cpu(&cl->cl_recs[alloc_rec].c_free,
		     le16_to_cpu(bg->bg_free_bits_count));
	le32_add_cpu(&cl->cl_recs[alloc_rec].c_total,
		     le16_to_cpu(bg->bg_bits));
	cl->cl_recs[alloc_rec].c_blkno = bg->bg_blkno;
	if (le16_to_cpu(cl->cl_next_free_rec) < le16_to_cpu(cl->cl_count))
		le16_add_cpu(&cl->cl_next_free_rec, 1);

	le32_add_cpu(&fe->id1.bitmap1.i_used, le16_to_cpu(bg->bg_bits) -
					le16_to_cpu(bg->bg_free_bits_count));
	le32_add_cpu(&fe->id1.bitmap1.i_total, le16_to_cpu(bg->bg_bits));
	le32_add_cpu(&fe->i_clusters, le16_to_cpu(cl->cl_cpg));

	ocfs2_journal_dirty(handle, bh);

	spin_lock(&OCFS2_I(alloc_inode)->ip_lock);
	OCFS2_I(alloc_inode)->ip_clusters = le32_to_cpu(fe->i_clusters);
	fe->i_size = cpu_to_le64(ocfs2_clusters_to_bytes(alloc_inode->i_sb,
					     le32_to_cpu(fe->i_clusters)));
	spin_unlock(&OCFS2_I(alloc_inode)->ip_lock);
	i_size_write(alloc_inode, le64_to_cpu(fe->i_size));
	alloc_inode->i_blocks = ocfs2_inode_sector_count(alloc_inode);
	ocfs2_update_inode_fsync_trans(handle, alloc_inode, 0);

	status = 0;

	/* save the new last alloc group so that the caller can cache it. */
	if (last_alloc_group)
		*last_alloc_group = ac->ac_last_group;

bail:
	if (handle)
		ocfs2_commit_trans(osb, handle);

	if (ac)
		ocfs2_free_alloc_context(ac);

	brelse(bg_bh);

	if (status)
		mlog_errno(status);
	return status;
}