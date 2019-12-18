#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_group_desc {int /*<<< orphan*/  bg_free_bits_count; int /*<<< orphan*/  bg_bits; int /*<<< orphan*/  bg_blkno; scalar_t__ bg_bitmap; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ b_committed_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_GROUP_DESC (struct ocfs2_group_desc*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_UNDO ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 TYPE_1__* bh2jh (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_bit (unsigned int,unsigned long*) ; 
 int ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_is_cluster_bitmap (struct inode*) ; 
 int ocfs2_journal_access_gd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  trace_ocfs2_block_group_clear_bits (unsigned int,unsigned int) ; 

__attribute__((used)) static int ocfs2_block_group_clear_bits(handle_t *handle,
					struct inode *alloc_inode,
					struct ocfs2_group_desc *bg,
					struct buffer_head *group_bh,
					unsigned int bit_off,
					unsigned int num_bits,
					void (*undo_fn)(unsigned int bit,
							unsigned long *bmap))
{
	int status;
	unsigned int tmp;
	struct ocfs2_group_desc *undo_bg = NULL;

	/* The caller got this descriptor from
	 * ocfs2_read_group_descriptor().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(bg));

	trace_ocfs2_block_group_clear_bits(bit_off, num_bits);

	BUG_ON(undo_fn && !ocfs2_is_cluster_bitmap(alloc_inode));
	status = ocfs2_journal_access_gd(handle, INODE_CACHE(alloc_inode),
					 group_bh,
					 undo_fn ?
					 OCFS2_JOURNAL_ACCESS_UNDO :
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	if (undo_fn) {
		jbd_lock_bh_state(group_bh);
		undo_bg = (struct ocfs2_group_desc *)
					bh2jh(group_bh)->b_committed_data;
		BUG_ON(!undo_bg);
	}

	tmp = num_bits;
	while(tmp--) {
		ocfs2_clear_bit((bit_off + tmp),
				(unsigned long *) bg->bg_bitmap);
		if (undo_fn)
			undo_fn(bit_off + tmp,
				(unsigned long *) undo_bg->bg_bitmap);
	}
	le16_add_cpu(&bg->bg_free_bits_count, num_bits);
	if (le16_to_cpu(bg->bg_free_bits_count) > le16_to_cpu(bg->bg_bits)) {
		if (undo_fn)
			jbd_unlock_bh_state(group_bh);
		return ocfs2_error(alloc_inode->i_sb, "Group descriptor # %llu has bit count %u but claims %u are freed. num_bits %d\n",
				   (unsigned long long)le64_to_cpu(bg->bg_blkno),
				   le16_to_cpu(bg->bg_bits),
				   le16_to_cpu(bg->bg_free_bits_count),
				   num_bits);
	}

	if (undo_fn)
		jbd_unlock_bh_state(group_bh);

	ocfs2_journal_dirty(handle, group_bh);
bail:
	return status;
}