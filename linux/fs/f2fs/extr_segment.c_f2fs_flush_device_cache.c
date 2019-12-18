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
struct f2fs_sb_info {int s_ndevs; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  dirty_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 TYPE_1__ FDEV (int) ; 
 int __submit_flush_wait (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_clear_bit (int,char*) ; 
 int /*<<< orphan*/  f2fs_is_multi_device (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_test_bit (int,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int f2fs_flush_device_cache(struct f2fs_sb_info *sbi)
{
	int ret = 0, i;

	if (!f2fs_is_multi_device(sbi))
		return 0;

	for (i = 1; i < sbi->s_ndevs; i++) {
		if (!f2fs_test_bit(i, (char *)&sbi->dirty_device))
			continue;
		ret = __submit_flush_wait(sbi, FDEV(i).bdev);
		if (ret)
			break;

		spin_lock(&sbi->dev_lock);
		f2fs_clear_bit(i, (char *)&sbi->dirty_device);
		spin_unlock(&sbi->dev_lock);
	}

	return ret;
}