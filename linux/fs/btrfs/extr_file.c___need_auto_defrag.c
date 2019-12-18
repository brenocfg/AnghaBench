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
 int /*<<< orphan*/  AUTO_DEFRAG ; 
 scalar_t__ btrfs_fs_closing (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __need_auto_defrag(struct btrfs_fs_info *fs_info)
{
	if (!btrfs_test_opt(fs_info, AUTO_DEFRAG))
		return 0;

	if (btrfs_fs_closing(fs_info))
		return 0;

	return 1;
}