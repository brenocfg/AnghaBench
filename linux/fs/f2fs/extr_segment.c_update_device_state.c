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
struct f2fs_sb_info {int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  dirty_device; } ;
struct f2fs_io_info {int /*<<< orphan*/  ino; int /*<<< orphan*/  new_blkaddr; struct f2fs_sb_info* sbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_INO ; 
 int /*<<< orphan*/  f2fs_is_multi_device (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_set_bit (unsigned int,char*) ; 
 int /*<<< orphan*/  f2fs_set_dirty_device (struct f2fs_sb_info*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int f2fs_target_device_index (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_test_bit (unsigned int,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_device_state(struct f2fs_io_info *fio)
{
	struct f2fs_sb_info *sbi = fio->sbi;
	unsigned int devidx;

	if (!f2fs_is_multi_device(sbi))
		return;

	devidx = f2fs_target_device_index(sbi, fio->new_blkaddr);

	/* update device state for fsync */
	f2fs_set_dirty_device(sbi, fio->ino, devidx, FLUSH_INO);

	/* update device state for checkpoint */
	if (!f2fs_test_bit(devidx, (char *)&sbi->dirty_device)) {
		spin_lock(&sbi->dev_lock);
		f2fs_set_bit(devidx, (char *)&sbi->dirty_device);
		spin_unlock(&sbi->dev_lock);
	}
}