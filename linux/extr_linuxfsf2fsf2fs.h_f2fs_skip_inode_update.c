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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * inode_lock; } ;
struct TYPE_2__ {int last_disk_size; int /*<<< orphan*/  i_sem; int /*<<< orphan*/  i_crtime; scalar_t__ i_disk_time; int /*<<< orphan*/  gdirty_list; } ;

/* Variables and functions */
 size_t DIRTY_META ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_AUTO_RECOVER ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ file_keep_isize (struct inode*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timespec64_equal (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool f2fs_skip_inode_update(struct inode *inode, int dsync)
{
	bool ret;

	if (dsync) {
		struct f2fs_sb_info *sbi = F2FS_I_SB(inode);

		spin_lock(&sbi->inode_lock[DIRTY_META]);
		ret = list_empty(&F2FS_I(inode)->gdirty_list);
		spin_unlock(&sbi->inode_lock[DIRTY_META]);
		return ret;
	}
	if (!is_inode_flag_set(inode, FI_AUTO_RECOVER) ||
			file_keep_isize(inode) ||
			i_size_read(inode) & ~PAGE_MASK)
		return false;

	if (!timespec64_equal(F2FS_I(inode)->i_disk_time, &inode->i_atime))
		return false;
	if (!timespec64_equal(F2FS_I(inode)->i_disk_time + 1, &inode->i_ctime))
		return false;
	if (!timespec64_equal(F2FS_I(inode)->i_disk_time + 2, &inode->i_mtime))
		return false;
	if (!timespec64_equal(F2FS_I(inode)->i_disk_time + 3,
						&F2FS_I(inode)->i_crtime))
		return false;

	down_read(&F2FS_I(inode)->i_sem);
	ret = F2FS_I(inode)->last_disk_size == i_size_read(inode);
	up_read(&F2FS_I(inode)->i_sem);

	return ret;
}