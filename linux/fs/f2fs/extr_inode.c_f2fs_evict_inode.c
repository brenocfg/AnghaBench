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
struct inode {scalar_t__ i_ino; scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_data; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  scalar_t__ nid_t ;
struct TYPE_2__ {scalar_t__ i_xattr_nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_INO ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ F2FS_HAS_BLOCKS (struct inode*) ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ F2FS_META_INO (struct f2fs_sb_info*) ; 
 scalar_t__ F2FS_NODE_INO (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  FAULT_EVICT_INODE ; 
 int /*<<< orphan*/  FI_APPEND_WRITE ; 
 int /*<<< orphan*/  FI_DIRTY_INODE ; 
 int /*<<< orphan*/  FI_FREE_NID ; 
 int /*<<< orphan*/  FI_NO_ALLOC ; 
 int /*<<< orphan*/  FI_UPDATE_WRITE ; 
 int /*<<< orphan*/  FLUSH_INO ; 
 int /*<<< orphan*/  NODE_MAPPING (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  SBI_QUOTA_NEED_REPAIR ; 
 int /*<<< orphan*/  UPDATE_INO ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_drop (struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 scalar_t__ dquot_initialize_needed (struct inode*) ; 
 int /*<<< orphan*/  f2fs_add_ino_entry (struct f2fs_sb_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_alloc_nid_failed (struct f2fs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_destroy_extent_tree (struct inode*) ; 
 int /*<<< orphan*/  f2fs_drop_inmem_pages (struct inode*) ; 
 int /*<<< orphan*/  f2fs_inode_synced (struct inode*) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_remove_dirty_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_remove_ino_entry (struct f2fs_sb_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int f2fs_remove_inode_page (struct inode*) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 int f2fs_truncate (struct inode*) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_update_inode_page (struct inode*) ; 
 int /*<<< orphan*/  fscrypt_put_encryption_info (struct inode*) ; 
 int /*<<< orphan*/  fsverity_cleanup_inode (struct inode*) ; 
 scalar_t__ get_dirty_pages (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_dec_inline_dir (struct inode*) ; 
 int /*<<< orphan*/  stat_dec_inline_inode (struct inode*) ; 
 int /*<<< orphan*/  stat_dec_inline_xattr (struct inode*) ; 
 scalar_t__ time_to_inject (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_evict_inode (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

void f2fs_evict_inode(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t xnid = F2FS_I(inode)->i_xattr_nid;
	int err = 0;

	/* some remained atomic pages should discarded */
	if (f2fs_is_atomic_file(inode))
		f2fs_drop_inmem_pages(inode);

	trace_f2fs_evict_inode(inode);
	truncate_inode_pages_final(&inode->i_data);

	if (inode->i_ino == F2FS_NODE_INO(sbi) ||
			inode->i_ino == F2FS_META_INO(sbi))
		goto out_clear;

	f2fs_bug_on(sbi, get_dirty_pages(inode));
	f2fs_remove_dirty_inode(inode);

	f2fs_destroy_extent_tree(inode);

	if (inode->i_nlink || is_bad_inode(inode))
		goto no_delete;

	err = dquot_initialize(inode);
	if (err) {
		err = 0;
		set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	}

	f2fs_remove_ino_entry(sbi, inode->i_ino, APPEND_INO);
	f2fs_remove_ino_entry(sbi, inode->i_ino, UPDATE_INO);
	f2fs_remove_ino_entry(sbi, inode->i_ino, FLUSH_INO);

	sb_start_intwrite(inode->i_sb);
	set_inode_flag(inode, FI_NO_ALLOC);
	i_size_write(inode, 0);
retry:
	if (F2FS_HAS_BLOCKS(inode))
		err = f2fs_truncate(inode);

	if (time_to_inject(sbi, FAULT_EVICT_INODE)) {
		f2fs_show_injection_info(FAULT_EVICT_INODE);
		err = -EIO;
	}

	if (!err) {
		f2fs_lock_op(sbi);
		err = f2fs_remove_inode_page(inode);
		f2fs_unlock_op(sbi);
		if (err == -ENOENT)
			err = 0;
	}

	/* give more chances, if ENOMEM case */
	if (err == -ENOMEM) {
		err = 0;
		goto retry;
	}

	if (err) {
		f2fs_update_inode_page(inode);
		if (dquot_initialize_needed(inode))
			set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	}
	sb_end_intwrite(inode->i_sb);
no_delete:
	dquot_drop(inode);

	stat_dec_inline_xattr(inode);
	stat_dec_inline_dir(inode);
	stat_dec_inline_inode(inode);

	if (likely(!f2fs_cp_error(sbi) &&
				!is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		f2fs_bug_on(sbi, is_inode_flag_set(inode, FI_DIRTY_INODE));
	else
		f2fs_inode_synced(inode);

	/* ino == 0, if f2fs_new_inode() was failed t*/
	if (inode->i_ino)
		invalidate_mapping_pages(NODE_MAPPING(sbi), inode->i_ino,
							inode->i_ino);
	if (xnid)
		invalidate_mapping_pages(NODE_MAPPING(sbi), xnid, xnid);
	if (inode->i_nlink) {
		if (is_inode_flag_set(inode, FI_APPEND_WRITE))
			f2fs_add_ino_entry(sbi, inode->i_ino, APPEND_INO);
		if (is_inode_flag_set(inode, FI_UPDATE_WRITE))
			f2fs_add_ino_entry(sbi, inode->i_ino, UPDATE_INO);
	}
	if (is_inode_flag_set(inode, FI_FREE_NID)) {
		f2fs_alloc_nid_failed(sbi, inode->i_ino);
		clear_inode_flag(inode, FI_FREE_NID);
	} else {
		/*
		 * If xattr nid is corrupted, we can reach out error condition,
		 * err & !f2fs_exist_written_data(sbi, inode->i_ino, ORPHAN_INO)).
		 * In that case, f2fs_check_nid_range() is enough to give a clue.
		 */
	}
out_clear:
	fscrypt_put_encryption_info(inode);
	fsverity_cleanup_inode(inode);
	clear_inode(inode);
}