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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_root_bh; int /*<<< orphan*/  et_ci; int /*<<< orphan*/  et_root_el; } ;
struct ocfs2_alloc_context {scalar_t__ ac_which; int /*<<< orphan*/  ac_bh; int /*<<< orphan*/  ac_inode; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  enum ocfs2_alloc_restarted { ____Placeholder_ocfs2_alloc_restarted } ocfs2_alloc_restarted ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOSPC ; 
 scalar_t__ OCFS2_AC_USE_LOCAL ; 
 int /*<<< orphan*/  OCFS2_EXT_UNWRITTEN ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int RESTART_META ; 
 int RESTART_NONE ; 
 int RESTART_TRANS ; 
 int __ocfs2_claim_clusters (int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int,int,int*,int*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_alloc_context_bits_left (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int) ; 
 int ocfs2_et_root_journal_access (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_extend_meta_needed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_clusters (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_free_local_alloc_bits (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int,int) ; 
 int ocfs2_insert_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 
 int ocfs2_num_free_extents (struct ocfs2_extent_tree*) ; 
 int /*<<< orphan*/  trace_ocfs2_add_clusters_in_btree (unsigned long long,int,int) ; 
 int /*<<< orphan*/  trace_ocfs2_add_clusters_in_btree_ret (int,int,int) ; 

int ocfs2_add_clusters_in_btree(handle_t *handle,
				struct ocfs2_extent_tree *et,
				u32 *logical_offset,
				u32 clusters_to_add,
				int mark_unwritten,
				struct ocfs2_alloc_context *data_ac,
				struct ocfs2_alloc_context *meta_ac,
				enum ocfs2_alloc_restarted *reason_ret)
{
	int status = 0, err = 0;
	int need_free = 0;
	int free_extents;
	enum ocfs2_alloc_restarted reason = RESTART_NONE;
	u32 bit_off, num_bits;
	u64 block;
	u8 flags = 0;
	struct ocfs2_super *osb =
		OCFS2_SB(ocfs2_metadata_cache_get_super(et->et_ci));

	BUG_ON(!clusters_to_add);

	if (mark_unwritten)
		flags = OCFS2_EXT_UNWRITTEN;

	free_extents = ocfs2_num_free_extents(et);
	if (free_extents < 0) {
		status = free_extents;
		mlog_errno(status);
		goto leave;
	}

	/* there are two cases which could cause us to EAGAIN in the
	 * we-need-more-metadata case:
	 * 1) we haven't reserved *any*
	 * 2) we are so fragmented, we've needed to add metadata too
	 *    many times. */
	if (!free_extents && !meta_ac) {
		err = -1;
		status = -EAGAIN;
		reason = RESTART_META;
		goto leave;
	} else if ((!free_extents)
		   && (ocfs2_alloc_context_bits_left(meta_ac)
		       < ocfs2_extend_meta_needed(et->et_root_el))) {
		err = -2;
		status = -EAGAIN;
		reason = RESTART_META;
		goto leave;
	}

	status = __ocfs2_claim_clusters(handle, data_ac, 1,
					clusters_to_add, &bit_off, &num_bits);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto leave;
	}

	BUG_ON(num_bits > clusters_to_add);

	/* reserve our write early -- insert_extent may update the tree root */
	status = ocfs2_et_root_journal_access(handle, et,
					      OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		need_free = 1;
		goto bail;
	}

	block = ocfs2_clusters_to_blocks(osb->sb, bit_off);
	trace_ocfs2_add_clusters_in_btree(
	     (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
	     bit_off, num_bits);
	status = ocfs2_insert_extent(handle, et, *logical_offset, block,
				     num_bits, flags, meta_ac);
	if (status < 0) {
		mlog_errno(status);
		need_free = 1;
		goto bail;
	}

	ocfs2_journal_dirty(handle, et->et_root_bh);

	clusters_to_add -= num_bits;
	*logical_offset += num_bits;

	if (clusters_to_add) {
		err = clusters_to_add;
		status = -EAGAIN;
		reason = RESTART_TRANS;
	}

bail:
	if (need_free) {
		if (data_ac->ac_which == OCFS2_AC_USE_LOCAL)
			ocfs2_free_local_alloc_bits(osb, handle, data_ac,
					bit_off, num_bits);
		else
			ocfs2_free_clusters(handle,
					data_ac->ac_inode,
					data_ac->ac_bh,
					ocfs2_clusters_to_blocks(osb->sb, bit_off),
					num_bits);
	}

leave:
	if (reason_ret)
		*reason_ret = reason;
	trace_ocfs2_add_clusters_in_btree_ret(status, reason, err);
	return status;
}