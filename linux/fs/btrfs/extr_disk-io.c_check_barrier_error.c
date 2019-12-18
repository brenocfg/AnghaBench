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
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  btrfs_check_rw_degradable (struct btrfs_fs_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_barrier_error(struct btrfs_fs_info *fs_info)
{
	if (!btrfs_check_rw_degradable(fs_info, NULL))
		return -EIO;
	return 0;
}