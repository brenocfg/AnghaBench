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
struct btrfs_free_space_ctl {int /*<<< orphan*/  tree_lock; } ;
struct btrfs_free_space {scalar_t__ offset; scalar_t__ bytes; int /*<<< orphan*/  bitmap; } ;
struct btrfs_block_group_cache {struct btrfs_free_space_ctl* free_space_ctl; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int btrfs_add_free_space (struct btrfs_block_group_cache*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_free_space_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_free_space*) ; 
 int link_free_space (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ offset_to_bitmap (struct btrfs_free_space_ctl*,scalar_t__) ; 
 int remove_from_bitmap (struct btrfs_free_space_ctl*,struct btrfs_free_space*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct btrfs_free_space* tree_search_offset (struct btrfs_free_space_ctl*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_free_space (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 

int btrfs_remove_free_space(struct btrfs_block_group_cache *block_group,
			    u64 offset, u64 bytes)
{
	struct btrfs_free_space_ctl *ctl = block_group->free_space_ctl;
	struct btrfs_free_space *info;
	int ret;
	bool re_search = false;

	spin_lock(&ctl->tree_lock);

again:
	ret = 0;
	if (!bytes)
		goto out_lock;

	info = tree_search_offset(ctl, offset, 0, 0);
	if (!info) {
		/*
		 * oops didn't find an extent that matched the space we wanted
		 * to remove, look for a bitmap instead
		 */
		info = tree_search_offset(ctl, offset_to_bitmap(ctl, offset),
					  1, 0);
		if (!info) {
			/*
			 * If we found a partial bit of our free space in a
			 * bitmap but then couldn't find the other part this may
			 * be a problem, so WARN about it.
			 */
			WARN_ON(re_search);
			goto out_lock;
		}
	}

	re_search = false;
	if (!info->bitmap) {
		unlink_free_space(ctl, info);
		if (offset == info->offset) {
			u64 to_free = min(bytes, info->bytes);

			info->bytes -= to_free;
			info->offset += to_free;
			if (info->bytes) {
				ret = link_free_space(ctl, info);
				WARN_ON(ret);
			} else {
				kmem_cache_free(btrfs_free_space_cachep, info);
			}

			offset += to_free;
			bytes -= to_free;
			goto again;
		} else {
			u64 old_end = info->bytes + info->offset;

			info->bytes = offset - info->offset;
			ret = link_free_space(ctl, info);
			WARN_ON(ret);
			if (ret)
				goto out_lock;

			/* Not enough bytes in this entry to satisfy us */
			if (old_end < offset + bytes) {
				bytes -= old_end - offset;
				offset = old_end;
				goto again;
			} else if (old_end == offset + bytes) {
				/* all done */
				goto out_lock;
			}
			spin_unlock(&ctl->tree_lock);

			ret = btrfs_add_free_space(block_group, offset + bytes,
						   old_end - (offset + bytes));
			WARN_ON(ret);
			goto out;
		}
	}

	ret = remove_from_bitmap(ctl, info, &offset, &bytes);
	if (ret == -EAGAIN) {
		re_search = true;
		goto again;
	}
out_lock:
	spin_unlock(&ctl->tree_lock);
out:
	return ret;
}