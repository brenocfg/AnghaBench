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
struct f2fs_sb_info {int s_ndevs; int /*<<< orphan*/  devs; } ;
struct TYPE_2__ {int /*<<< orphan*/  blkz_seq; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 TYPE_1__ FDEV (int) ; 
 int /*<<< orphan*/  FMODE_EXCL ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_device_list(struct f2fs_sb_info *sbi)
{
	int i;

	for (i = 0; i < sbi->s_ndevs; i++) {
		blkdev_put(FDEV(i).bdev, FMODE_EXCL);
#ifdef CONFIG_BLK_DEV_ZONED
		kvfree(FDEV(i).blkz_seq);
#endif
	}
	kvfree(sbi->devs);
}