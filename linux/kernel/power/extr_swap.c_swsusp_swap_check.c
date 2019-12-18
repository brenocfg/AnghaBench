#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int blkdev_get (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkdev_put (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* hib_resume_bdev ; 
 int root_swap ; 
 int set_blocksize (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int swap_type_of (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  swsusp_resume_block ; 
 int /*<<< orphan*/  swsusp_resume_device ; 

__attribute__((used)) static int swsusp_swap_check(void)
{
	int res;

	res = swap_type_of(swsusp_resume_device, swsusp_resume_block,
			&hib_resume_bdev);
	if (res < 0)
		return res;

	root_swap = res;
	res = blkdev_get(hib_resume_bdev, FMODE_WRITE, NULL);
	if (res)
		return res;

	res = set_blocksize(hib_resume_bdev, PAGE_SIZE);
	if (res < 0)
		blkdev_put(hib_resume_bdev, FMODE_WRITE);

	/*
	 * Update the resume device to the one actually used,
	 * so the test_resume mode can use it in case it is
	 * invoked from hibernate() to test the snapshot.
	 */
	swsusp_resume_device = hib_resume_bdev->bd_dev;
	return res;
}