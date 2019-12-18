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
struct the_nilfs {int ns_flushed_device; int /*<<< orphan*/  ns_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_test_opt (struct the_nilfs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static inline int nilfs_flush_device(struct the_nilfs *nilfs)
{
	int err;

	if (!nilfs_test_opt(nilfs, BARRIER) || nilfs->ns_flushed_device)
		return 0;

	nilfs->ns_flushed_device = 1;
	/*
	 * the store to ns_flushed_device must not be reordered after
	 * blkdev_issue_flush().
	 */
	smp_wmb();

	err = blkdev_issue_flush(nilfs->ns_bdev, GFP_KERNEL, NULL);
	if (err != -EIO)
		err = 0;
	return err;
}