#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int u64 ;
struct super_block {int s_flags; } ;
struct inode {int i_mode; int i_nlink; int i_generation; struct super_block* i_sb; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_rdev; } ;
struct ext4_inode_info {int i_dtime; int i_flags; int i_file_acl; int i_disksize; int i_extra_isize; int /*<<< orphan*/  i_raw_lock; void** i_data; int /*<<< orphan*/  i_orphan; int /*<<< orphan*/  i_projid; } ;
struct ext4_inode {void* i_projid; void* i_extra_isize; void* i_version_hi; void* i_disk_version; void** i_block; void* i_generation; void* i_file_acl_lo; void* i_file_acl_high; void* i_flags; void* i_dtime; void* i_links_count; void* i_gid_high; void* i_uid_high; void* i_gid_low; void* i_uid_low; void* i_mode; } ;
struct ext4_iloc {struct buffer_head* bh; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int projid_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_4__ {struct buffer_head* s_sbh; TYPE_1__* s_es; int /*<<< orphan*/  s_inode_size; } ;
struct TYPE_3__ {void* s_rev_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EXT4_DEF_PROJID ; 
 int /*<<< orphan*/  EXT4_EINODE_SET_XTIME (int /*<<< orphan*/ ,struct ext4_inode_info*,struct ext4_inode*) ; 
 scalar_t__ EXT4_FITS_IN_INODE (struct ext4_inode*,struct ext4_inode_info*,int) ; 
 scalar_t__ EXT4_GOOD_OLD_INODE_SIZE ; 
 int EXT4_GOOD_OLD_REV ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_SET_XTIME (int /*<<< orphan*/ ,struct inode*,struct ext4_inode*) ; 
 scalar_t__ EXT4_INODE_SIZE (struct super_block*) ; 
 int EXT4_N_BLOCKS ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_STATE_NEW ; 
 int /*<<< orphan*/  HURD_COMPAT ; 
 int /*<<< orphan*/  NO_UID32 ; 
 int SB_LAZYTIME ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ext4_handle_dirty_super (int /*<<< orphan*/ *,struct super_block*) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_has_feature_large_file (struct super_block*) ; 
 int /*<<< orphan*/  ext4_has_feature_project (struct super_block*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 int ext4_inode_blocks_set (int /*<<< orphan*/ *,struct ext4_inode*,struct ext4_inode_info*) ; 
 int /*<<< orphan*/  ext4_inode_csum_set (struct inode*,struct ext4_inode*,struct ext4_inode_info*) ; 
 int ext4_inode_peek_iversion (struct inode*) ; 
 int ext4_isize (struct super_block*,struct ext4_inode*) ; 
 int /*<<< orphan*/  ext4_isize_set (struct ext4_inode*,int) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 struct ext4_inode* ext4_raw_inode (struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_set_feature_large_file (struct super_block*) ; 
 int /*<<< orphan*/  ext4_std_error (struct super_block*,int) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 int /*<<< orphan*/  ext4_update_other_inodes_time (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int from_kprojid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fs_high2lowgid (int /*<<< orphan*/ ) ; 
 int fs_high2lowuid (int /*<<< orphan*/ ) ; 
 int high_16_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_atime ; 
 int /*<<< orphan*/  i_crtime ; 
 int /*<<< orphan*/  i_ctime ; 
 int /*<<< orphan*/  i_gid_read (struct inode*) ; 
 int /*<<< orphan*/  i_mtime ; 
 int /*<<< orphan*/  i_uid_read (struct inode*) ; 
 int i_version_hi ; 
 int /*<<< orphan*/  init_user_ns ; 
 scalar_t__ likely (int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int low_16_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ext4_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int new_encode_dev (int /*<<< orphan*/ ) ; 
 int old_encode_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ old_valid_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_opt2 (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_do_update_inode(handle_t *handle,
				struct inode *inode,
				struct ext4_iloc *iloc)
{
	struct ext4_inode *raw_inode = ext4_raw_inode(iloc);
	struct ext4_inode_info *ei = EXT4_I(inode);
	struct buffer_head *bh = iloc->bh;
	struct super_block *sb = inode->i_sb;
	int err = 0, rc, block;
	int need_datasync = 0, set_large_file = 0;
	uid_t i_uid;
	gid_t i_gid;
	projid_t i_projid;

	spin_lock(&ei->i_raw_lock);

	/* For fields not tracked in the in-memory inode,
	 * initialise them to zero for new inodes. */
	if (ext4_test_inode_state(inode, EXT4_STATE_NEW))
		memset(raw_inode, 0, EXT4_SB(inode->i_sb)->s_inode_size);

	raw_inode->i_mode = cpu_to_le16(inode->i_mode);
	i_uid = i_uid_read(inode);
	i_gid = i_gid_read(inode);
	i_projid = from_kprojid(&init_user_ns, ei->i_projid);
	if (!(test_opt(inode->i_sb, NO_UID32))) {
		raw_inode->i_uid_low = cpu_to_le16(low_16_bits(i_uid));
		raw_inode->i_gid_low = cpu_to_le16(low_16_bits(i_gid));
/*
 * Fix up interoperability with old kernels. Otherwise, old inodes get
 * re-used with the upper 16 bits of the uid/gid intact
 */
		if (ei->i_dtime && list_empty(&ei->i_orphan)) {
			raw_inode->i_uid_high = 0;
			raw_inode->i_gid_high = 0;
		} else {
			raw_inode->i_uid_high =
				cpu_to_le16(high_16_bits(i_uid));
			raw_inode->i_gid_high =
				cpu_to_le16(high_16_bits(i_gid));
		}
	} else {
		raw_inode->i_uid_low = cpu_to_le16(fs_high2lowuid(i_uid));
		raw_inode->i_gid_low = cpu_to_le16(fs_high2lowgid(i_gid));
		raw_inode->i_uid_high = 0;
		raw_inode->i_gid_high = 0;
	}
	raw_inode->i_links_count = cpu_to_le16(inode->i_nlink);

	EXT4_INODE_SET_XTIME(i_ctime, inode, raw_inode);
	EXT4_INODE_SET_XTIME(i_mtime, inode, raw_inode);
	EXT4_INODE_SET_XTIME(i_atime, inode, raw_inode);
	EXT4_EINODE_SET_XTIME(i_crtime, ei, raw_inode);

	err = ext4_inode_blocks_set(handle, raw_inode, ei);
	if (err) {
		spin_unlock(&ei->i_raw_lock);
		goto out_brelse;
	}
	raw_inode->i_dtime = cpu_to_le32(ei->i_dtime);
	raw_inode->i_flags = cpu_to_le32(ei->i_flags & 0xFFFFFFFF);
	if (likely(!test_opt2(inode->i_sb, HURD_COMPAT)))
		raw_inode->i_file_acl_high =
			cpu_to_le16(ei->i_file_acl >> 32);
	raw_inode->i_file_acl_lo = cpu_to_le32(ei->i_file_acl);
	if (ei->i_disksize != ext4_isize(inode->i_sb, raw_inode)) {
		ext4_isize_set(raw_inode, ei->i_disksize);
		need_datasync = 1;
	}
	if (ei->i_disksize > 0x7fffffffULL) {
		if (!ext4_has_feature_large_file(sb) ||
				EXT4_SB(sb)->s_es->s_rev_level ==
		    cpu_to_le32(EXT4_GOOD_OLD_REV))
			set_large_file = 1;
	}
	raw_inode->i_generation = cpu_to_le32(inode->i_generation);
	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) {
		if (old_valid_dev(inode->i_rdev)) {
			raw_inode->i_block[0] =
				cpu_to_le32(old_encode_dev(inode->i_rdev));
			raw_inode->i_block[1] = 0;
		} else {
			raw_inode->i_block[0] = 0;
			raw_inode->i_block[1] =
				cpu_to_le32(new_encode_dev(inode->i_rdev));
			raw_inode->i_block[2] = 0;
		}
	} else if (!ext4_has_inline_data(inode)) {
		for (block = 0; block < EXT4_N_BLOCKS; block++)
			raw_inode->i_block[block] = ei->i_data[block];
	}

	if (likely(!test_opt2(inode->i_sb, HURD_COMPAT))) {
		u64 ivers = ext4_inode_peek_iversion(inode);

		raw_inode->i_disk_version = cpu_to_le32(ivers);
		if (ei->i_extra_isize) {
			if (EXT4_FITS_IN_INODE(raw_inode, ei, i_version_hi))
				raw_inode->i_version_hi =
					cpu_to_le32(ivers >> 32);
			raw_inode->i_extra_isize =
				cpu_to_le16(ei->i_extra_isize);
		}
	}

	BUG_ON(!ext4_has_feature_project(inode->i_sb) &&
	       i_projid != EXT4_DEF_PROJID);

	if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw_inode, ei, i_projid))
		raw_inode->i_projid = cpu_to_le32(i_projid);

	ext4_inode_csum_set(inode, raw_inode, ei);
	spin_unlock(&ei->i_raw_lock);
	if (inode->i_sb->s_flags & SB_LAZYTIME)
		ext4_update_other_inodes_time(inode->i_sb, inode->i_ino,
					      bh->b_data);

	BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
	rc = ext4_handle_dirty_metadata(handle, NULL, bh);
	if (!err)
		err = rc;
	ext4_clear_inode_state(inode, EXT4_STATE_NEW);
	if (set_large_file) {
		BUFFER_TRACE(EXT4_SB(sb)->s_sbh, "get write access");
		err = ext4_journal_get_write_access(handle, EXT4_SB(sb)->s_sbh);
		if (err)
			goto out_brelse;
		ext4_set_feature_large_file(sb);
		ext4_handle_sync(handle);
		err = ext4_handle_dirty_super(handle, sb);
	}
	ext4_update_inode_fsync_trans(handle, inode, need_datasync);
out_brelse:
	brelse(bh);
	ext4_std_error(inode->i_sb, err);
	return err;
}