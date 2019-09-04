#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct TYPE_5__ {TYPE_1__* root; } ;
struct TYPE_4__ {int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  btrfs_debug_rl (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_ino (TYPE_2__*) ; 
 scalar_t__ i_size_read (struct inode*) ; 

__attribute__((used)) static void btrfs_check_extent_io_range(void *private_data, const char *caller,
					u64 start, u64 end)
{
	struct inode *inode = private_data;
	u64 isize;

	isize = i_size_read(inode);
	if (end >= PAGE_SIZE && (end % 2) == 0 && end != isize - 1) {
		btrfs_debug_rl(BTRFS_I(inode)->root->fs_info,
		    "%s: ino %llu isize %llu odd range [%llu,%llu]",
			caller, btrfs_ino(BTRFS_I(inode)), isize, start, end);
	}
}