#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct f2fs_sb_info {int valid_super_block; TYPE_1__* sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int EIO ; 
 int EROFS ; 
 int /*<<< orphan*/  F2FS_RAW_SUPER (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  SBI_NEED_SB_WRITE ; 
 int __f2fs_commit_super (struct buffer_head*,int /*<<< orphan*/ ) ; 
 scalar_t__ bdev_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ f2fs_readonly (TYPE_1__*) ; 
 struct buffer_head* sb_bread (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

int f2fs_commit_super(struct f2fs_sb_info *sbi, bool recover)
{
	struct buffer_head *bh;
	int err;

	if ((recover && f2fs_readonly(sbi->sb)) ||
				bdev_read_only(sbi->sb->s_bdev)) {
		set_sbi_flag(sbi, SBI_NEED_SB_WRITE);
		return -EROFS;
	}

	/* write back-up superblock first */
	bh = sb_bread(sbi->sb, sbi->valid_super_block ? 0 : 1);
	if (!bh)
		return -EIO;
	err = __f2fs_commit_super(bh, F2FS_RAW_SUPER(sbi));
	brelse(bh);

	/* if we are in recovery path, skip writing valid superblock */
	if (recover || err)
		return err;

	/* write current valid superblock */
	bh = sb_bread(sbi->sb, sbi->valid_super_block);
	if (!bh)
		return -EIO;
	err = __f2fs_commit_super(bh, F2FS_RAW_SUPER(sbi));
	brelse(bh);
	return err;
}