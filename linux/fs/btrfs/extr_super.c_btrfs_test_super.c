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
struct super_block {int dummy; } ;
struct btrfs_fs_info {scalar_t__ fs_devices; } ;

/* Variables and functions */
 struct btrfs_fs_info* btrfs_sb (struct super_block*) ; 

__attribute__((used)) static int btrfs_test_super(struct super_block *s, void *data)
{
	struct btrfs_fs_info *p = data;
	struct btrfs_fs_info *fs_info = btrfs_sb(s);

	return fs_info->fs_devices == p->fs_devices;
}