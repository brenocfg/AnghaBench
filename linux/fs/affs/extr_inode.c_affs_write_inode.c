#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uid_t ;
struct writeback_control {int dummy; } ;
struct super_block {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_sec; } ;
struct inode {scalar_t__ i_ino; TYPE_1__ i_mtime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlink; struct super_block* i_sb; } ;
struct buffer_head {int dummy; } ;
struct affs_tail {void* stype; void* gid; void* uid; int /*<<< orphan*/  change; void* size; void* protect; } ;
typedef  int gid_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_protect; } ;
struct TYPE_7__ {int /*<<< orphan*/  root_change; } ;
struct TYPE_6__ {scalar_t__ s_root_block; int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 TYPE_4__* AFFS_I (struct inode*) ; 
 TYPE_3__* AFFS_ROOT_TAIL (struct super_block*,struct buffer_head*) ; 
 TYPE_2__* AFFS_SB (struct super_block*) ; 
 struct affs_tail* AFFS_TAIL (struct super_block*,struct buffer_head*) ; 
 int EIO ; 
 int /*<<< orphan*/  SF_MUFS ; 
 int /*<<< orphan*/  SF_SETGID ; 
 int /*<<< orphan*/  SF_SETUID ; 
 int /*<<< orphan*/  ST_ROOT ; 
 struct buffer_head* affs_bread (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  affs_error (struct super_block*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  affs_fix_checksum (struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  affs_free_prealloc (struct inode*) ; 
 int /*<<< orphan*/  affs_secs_to_datestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ affs_test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int i_gid_read (struct inode*) ; 
 int i_uid_read (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

int
affs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	struct super_block	*sb = inode->i_sb;
	struct buffer_head	*bh;
	struct affs_tail	*tail;
	uid_t			 uid;
	gid_t			 gid;

	pr_debug("write_inode(%lu)\n", inode->i_ino);

	if (!inode->i_nlink)
		// possibly free block
		return 0;
	bh = affs_bread(sb, inode->i_ino);
	if (!bh) {
		affs_error(sb,"write_inode","Cannot read block %lu",inode->i_ino);
		return -EIO;
	}
	tail = AFFS_TAIL(sb, bh);
	if (tail->stype == cpu_to_be32(ST_ROOT)) {
		affs_secs_to_datestamp(inode->i_mtime.tv_sec,
				       &AFFS_ROOT_TAIL(sb, bh)->root_change);
	} else {
		tail->protect = cpu_to_be32(AFFS_I(inode)->i_protect);
		tail->size = cpu_to_be32(inode->i_size);
		affs_secs_to_datestamp(inode->i_mtime.tv_sec, &tail->change);
		if (!(inode->i_ino == AFFS_SB(sb)->s_root_block)) {
			uid = i_uid_read(inode);
			gid = i_gid_read(inode);
			if (affs_test_opt(AFFS_SB(sb)->s_flags, SF_MUFS)) {
				if (uid == 0 || uid == 0xFFFF)
					uid = uid ^ ~0;
				if (gid == 0 || gid == 0xFFFF)
					gid = gid ^ ~0;
			}
			if (!affs_test_opt(AFFS_SB(sb)->s_flags, SF_SETUID))
				tail->uid = cpu_to_be16(uid);
			if (!affs_test_opt(AFFS_SB(sb)->s_flags, SF_SETGID))
				tail->gid = cpu_to_be16(gid);
		}
	}
	affs_fix_checksum(sb, bh);
	mark_buffer_dirty_inode(bh, inode);
	affs_brelse(bh);
	affs_free_prealloc(inode);
	return 0;
}