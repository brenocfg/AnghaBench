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
typedef  int u64 ;
struct btrfs_space_info {int disk_total; int disk_used; int /*<<< orphan*/  lock; scalar_t__ full; int /*<<< orphan*/  bytes_readonly; int /*<<< orphan*/  bytes_used; int /*<<< orphan*/  total_bytes; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct btrfs_space_info*) ; 
 struct btrfs_space_info* __find_space_info (struct btrfs_fs_info*,int) ; 
 int btrfs_bg_type_to_factor (int) ; 
 int /*<<< orphan*/  space_info_add_new_bytes (struct btrfs_fs_info*,struct btrfs_space_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_space_info(struct btrfs_fs_info *info, u64 flags,
			     u64 total_bytes, u64 bytes_used,
			     u64 bytes_readonly,
			     struct btrfs_space_info **space_info)
{
	struct btrfs_space_info *found;
	int factor;

	factor = btrfs_bg_type_to_factor(flags);

	found = __find_space_info(info, flags);
	ASSERT(found);
	spin_lock(&found->lock);
	found->total_bytes += total_bytes;
	found->disk_total += total_bytes * factor;
	found->bytes_used += bytes_used;
	found->disk_used += bytes_used * factor;
	found->bytes_readonly += bytes_readonly;
	if (total_bytes > 0)
		found->full = 0;
	space_info_add_new_bytes(info, found, total_bytes -
				 bytes_used - bytes_readonly);
	spin_unlock(&found->lock);
	*space_info = found;
}