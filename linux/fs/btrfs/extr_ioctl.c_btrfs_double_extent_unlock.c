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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  io_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  unlock_extent (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void btrfs_double_extent_unlock(struct inode *inode1, u64 loff1,
				       struct inode *inode2, u64 loff2, u64 len)
{
	unlock_extent(&BTRFS_I(inode1)->io_tree, loff1, loff1 + len - 1);
	unlock_extent(&BTRFS_I(inode2)->io_tree, loff2, loff2 + len - 1);
}