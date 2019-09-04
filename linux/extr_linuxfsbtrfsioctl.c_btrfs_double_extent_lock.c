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
typedef  int u64 ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  io_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int lock_extent_range (struct inode*,int,int,int) ; 
 int /*<<< orphan*/  swap (int,int) ; 
 int /*<<< orphan*/  unlock_extent (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int btrfs_double_extent_lock(struct inode *inode1, u64 loff1,
				    struct inode *inode2, u64 loff2, u64 len,
				    bool retry_range_locking)
{
	int ret;

	if (inode1 < inode2) {
		swap(inode1, inode2);
		swap(loff1, loff2);
	}
	ret = lock_extent_range(inode1, loff1, len, retry_range_locking);
	if (ret)
		return ret;
	ret = lock_extent_range(inode2, loff2, len, retry_range_locking);
	if (ret)
		unlock_extent(&BTRFS_I(inode1)->io_tree, loff1,
			      loff1 + len - 1);
	return ret;
}