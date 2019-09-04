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
struct btrfs_fs_info {TYPE_1__* sb; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 int SB_RDONLY ; 
 scalar_t__ btrfs_fs_closing (struct btrfs_fs_info*) ; 

__attribute__((used)) static inline int btrfs_need_cleaner_sleep(struct btrfs_fs_info *fs_info)
{
	return fs_info->sb->s_flags & SB_RDONLY || btrfs_fs_closing(fs_info);
}