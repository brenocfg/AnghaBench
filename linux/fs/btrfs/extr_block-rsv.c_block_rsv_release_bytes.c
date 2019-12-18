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
struct btrfs_space_info {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_rsv {scalar_t__ size; scalar_t__ qgroup_rsv_size; scalar_t__ reserved; int full; scalar_t__ qgroup_rsv_reserved; int /*<<< orphan*/  lock; struct btrfs_space_info* space_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_space_info_free_bytes_may_use (struct btrfs_fs_info*,struct btrfs_space_info*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 block_rsv_release_bytes(struct btrfs_fs_info *fs_info,
				    struct btrfs_block_rsv *block_rsv,
				    struct btrfs_block_rsv *dest, u64 num_bytes,
				    u64 *qgroup_to_release_ret)
{
	struct btrfs_space_info *space_info = block_rsv->space_info;
	u64 qgroup_to_release = 0;
	u64 ret;

	spin_lock(&block_rsv->lock);
	if (num_bytes == (u64)-1) {
		num_bytes = block_rsv->size;
		qgroup_to_release = block_rsv->qgroup_rsv_size;
	}
	block_rsv->size -= num_bytes;
	if (block_rsv->reserved >= block_rsv->size) {
		num_bytes = block_rsv->reserved - block_rsv->size;
		block_rsv->reserved = block_rsv->size;
		block_rsv->full = 1;
	} else {
		num_bytes = 0;
	}
	if (block_rsv->qgroup_rsv_reserved >= block_rsv->qgroup_rsv_size) {
		qgroup_to_release = block_rsv->qgroup_rsv_reserved -
				    block_rsv->qgroup_rsv_size;
		block_rsv->qgroup_rsv_reserved = block_rsv->qgroup_rsv_size;
	} else {
		qgroup_to_release = 0;
	}
	spin_unlock(&block_rsv->lock);

	ret = num_bytes;
	if (num_bytes > 0) {
		if (dest) {
			spin_lock(&dest->lock);
			if (!dest->full) {
				u64 bytes_to_add;

				bytes_to_add = dest->size - dest->reserved;
				bytes_to_add = min(num_bytes, bytes_to_add);
				dest->reserved += bytes_to_add;
				if (dest->reserved >= dest->size)
					dest->full = 1;
				num_bytes -= bytes_to_add;
			}
			spin_unlock(&dest->lock);
		}
		if (num_bytes)
			btrfs_space_info_free_bytes_may_use(fs_info,
							    space_info,
							    num_bytes);
	}
	if (qgroup_to_release_ret)
		*qgroup_to_release_ret = qgroup_to_release;
	return ret;
}