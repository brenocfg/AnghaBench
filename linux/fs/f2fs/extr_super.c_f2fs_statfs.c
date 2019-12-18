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
typedef  void* u32 ;
struct super_block {TYPE_1__* s_bdev; } ;
struct TYPE_8__ {void** val; } ;
struct kstatfs {scalar_t__ f_bfree; scalar_t__ f_bavail; scalar_t__ f_ffree; TYPE_3__ f_fsid; int /*<<< orphan*/  f_namelen; scalar_t__ f_files; scalar_t__ f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct f2fs_sb_info {scalar_t__ user_block_count; scalar_t__ current_reserved_blocks; scalar_t__ unusable_block_count; scalar_t__ total_node_count; int /*<<< orphan*/  stat_lock; int /*<<< orphan*/  blocksize; TYPE_2__* raw_super; } ;
struct dentry {int /*<<< orphan*/  d_inode; struct super_block* d_sb; } ;
typedef  scalar_t__ block_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_projid; } ;
struct TYPE_9__ {scalar_t__ root_reserved_blocks; } ;
struct TYPE_7__ {int /*<<< orphan*/  segment0_blkaddr; int /*<<< orphan*/  block_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 TYPE_5__* F2FS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F2FS_NAME_LEN ; 
 TYPE_4__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 scalar_t__ F2FS_RESERVED_NODE_NUM ; 
 struct f2fs_sb_info* F2FS_SB (struct super_block*) ; 
 int /*<<< orphan*/  F2FS_SUPER_MAGIC ; 
 int /*<<< orphan*/  FI_PROJ_INHERIT ; 
 int /*<<< orphan*/  PRJQUOTA ; 
 int /*<<< orphan*/  f2fs_statfs_project (struct super_block*,int /*<<< orphan*/ ,struct kstatfs*) ; 
 scalar_t__ huge_encode_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ is_inode_flag_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ sb_has_quota_limits_enabled (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ valid_node_count (struct f2fs_sb_info*) ; 
 scalar_t__ valid_user_blocks (struct f2fs_sb_info*) ; 

__attribute__((used)) static int f2fs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct f2fs_sb_info *sbi = F2FS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);
	block_t total_count, user_block_count, start_count;
	u64 avail_node_count;

	total_count = le64_to_cpu(sbi->raw_super->block_count);
	user_block_count = sbi->user_block_count;
	start_count = le32_to_cpu(sbi->raw_super->segment0_blkaddr);
	buf->f_type = F2FS_SUPER_MAGIC;
	buf->f_bsize = sbi->blocksize;

	buf->f_blocks = total_count - start_count;
	buf->f_bfree = user_block_count - valid_user_blocks(sbi) -
						sbi->current_reserved_blocks;

	spin_lock(&sbi->stat_lock);
	if (unlikely(buf->f_bfree <= sbi->unusable_block_count))
		buf->f_bfree = 0;
	else
		buf->f_bfree -= sbi->unusable_block_count;
	spin_unlock(&sbi->stat_lock);

	if (buf->f_bfree > F2FS_OPTION(sbi).root_reserved_blocks)
		buf->f_bavail = buf->f_bfree -
				F2FS_OPTION(sbi).root_reserved_blocks;
	else
		buf->f_bavail = 0;

	avail_node_count = sbi->total_node_count - F2FS_RESERVED_NODE_NUM;

	if (avail_node_count > user_block_count) {
		buf->f_files = user_block_count;
		buf->f_ffree = buf->f_bavail;
	} else {
		buf->f_files = avail_node_count;
		buf->f_ffree = min(avail_node_count - valid_node_count(sbi),
					buf->f_bavail);
	}

	buf->f_namelen = F2FS_NAME_LEN;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);

#ifdef CONFIG_QUOTA
	if (is_inode_flag_set(dentry->d_inode, FI_PROJ_INHERIT) &&
			sb_has_quota_limits_enabled(sb, PRJQUOTA)) {
		f2fs_statfs_project(sb, F2FS_I(dentry->d_inode)->i_projid, buf);
	}
#endif
	return 0;
}