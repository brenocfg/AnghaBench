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
typedef  scalar_t__ u64 ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  fs_roots_radix_lock; int /*<<< orphan*/  fs_roots_radix; } ;

/* Variables and functions */
 struct btrfs_root* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct btrfs_root *btrfs_lookup_fs_root(struct btrfs_fs_info *fs_info,
					u64 root_id)
{
	struct btrfs_root *root;

	spin_lock(&fs_info->fs_roots_radix_lock);
	root = radix_tree_lookup(&fs_info->fs_roots_radix,
				 (unsigned long)root_id);
	spin_unlock(&fs_info->fs_roots_radix_lock);
	return root;
}