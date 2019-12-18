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
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long EPERM ; 
 long btrfs_scrub_cancel (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long btrfs_ioctl_scrub_cancel(struct btrfs_fs_info *fs_info)
{
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	return btrfs_scrub_cancel(fs_info);
}