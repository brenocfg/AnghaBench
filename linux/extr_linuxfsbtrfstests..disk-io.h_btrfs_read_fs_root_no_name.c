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
struct btrfs_root {int dummy; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 struct btrfs_root* btrfs_get_fs_root (struct btrfs_fs_info*,struct btrfs_key*,int) ; 

__attribute__((used)) static inline struct btrfs_root *
btrfs_read_fs_root_no_name(struct btrfs_fs_info *fs_info,
			   struct btrfs_key *location)
{
	return btrfs_get_fs_root(fs_info, location, true);
}