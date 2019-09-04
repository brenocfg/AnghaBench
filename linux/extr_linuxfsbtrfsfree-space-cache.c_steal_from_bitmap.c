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
struct btrfs_free_space_ctl {scalar_t__ total_bitmaps; } ;
struct btrfs_free_space {int /*<<< orphan*/  offset_index; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int steal_from_bitmap_to_end (struct btrfs_free_space_ctl*,struct btrfs_free_space*,int) ; 
 int steal_from_bitmap_to_front (struct btrfs_free_space_ctl*,struct btrfs_free_space*,int) ; 
 int /*<<< orphan*/  try_merge_free_space (struct btrfs_free_space_ctl*,struct btrfs_free_space*,int) ; 

__attribute__((used)) static void steal_from_bitmap(struct btrfs_free_space_ctl *ctl,
			      struct btrfs_free_space *info,
			      bool update_stat)
{
	/*
	 * Only work with disconnected entries, as we can change their offset,
	 * and must be extent entries.
	 */
	ASSERT(!info->bitmap);
	ASSERT(RB_EMPTY_NODE(&info->offset_index));

	if (ctl->total_bitmaps > 0) {
		bool stole_end;
		bool stole_front = false;

		stole_end = steal_from_bitmap_to_end(ctl, info, update_stat);
		if (ctl->total_bitmaps > 0)
			stole_front = steal_from_bitmap_to_front(ctl, info,
								 update_stat);

		if (stole_end || stole_front)
			try_merge_free_space(ctl, info, update_stat);
	}
}