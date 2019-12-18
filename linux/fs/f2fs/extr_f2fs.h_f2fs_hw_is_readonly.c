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
struct f2fs_sb_info {int s_ndevs; TYPE_1__* sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 TYPE_2__ FDEV (int) ; 
 int bdev_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_is_multi_device (struct f2fs_sb_info*) ; 

__attribute__((used)) static inline bool f2fs_hw_is_readonly(struct f2fs_sb_info *sbi)
{
	int i;

	if (!f2fs_is_multi_device(sbi))
		return bdev_read_only(sbi->sb->s_bdev);

	for (i = 0; i < sbi->s_ndevs; i++)
		if (bdev_read_only(FDEV(i).bdev))
			return true;
	return false;
}