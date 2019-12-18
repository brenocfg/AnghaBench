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
struct block_device {TYPE_1__* bd_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  filemap_fdatawait_keep_errors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdatawait_one_bdev(struct block_device *bdev, void *arg)
{
	/*
	 * We keep the error status of individual mapping so that
	 * applications can catch the writeback error using fsync(2).
	 * See filemap_fdatawait_keep_errors() for details.
	 */
	filemap_fdatawait_keep_errors(bdev->bd_inode->i_mapping);
}