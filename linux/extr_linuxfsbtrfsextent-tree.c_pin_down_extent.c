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
struct btrfs_fs_info {int /*<<< orphan*/  pinned_extents; } ;
struct btrfs_block_group_cache {TYPE_1__* space_info; int /*<<< orphan*/  lock; int /*<<< orphan*/  reserved; int /*<<< orphan*/  pinned; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_bytes_pinned; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  bytes_reserved; int /*<<< orphan*/  bytes_pinned; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_TOTAL_BYTES_PINNED_BATCH ; 
 int GFP_NOFS ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_extent_dirty (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int pin_down_extent(struct btrfs_fs_info *fs_info,
			   struct btrfs_block_group_cache *cache,
			   u64 bytenr, u64 num_bytes, int reserved)
{
	spin_lock(&cache->space_info->lock);
	spin_lock(&cache->lock);
	cache->pinned += num_bytes;
	cache->space_info->bytes_pinned += num_bytes;
	if (reserved) {
		cache->reserved -= num_bytes;
		cache->space_info->bytes_reserved -= num_bytes;
	}
	spin_unlock(&cache->lock);
	spin_unlock(&cache->space_info->lock);

	trace_btrfs_space_reservation(fs_info, "pinned",
				      cache->space_info->flags, num_bytes, 1);
	percpu_counter_add_batch(&cache->space_info->total_bytes_pinned,
		    num_bytes, BTRFS_TOTAL_BYTES_PINNED_BATCH);
	set_extent_dirty(fs_info->pinned_extents, bytenr,
			 bytenr + num_bytes - 1, GFP_NOFS | __GFP_NOFAIL);
	return 0;
}