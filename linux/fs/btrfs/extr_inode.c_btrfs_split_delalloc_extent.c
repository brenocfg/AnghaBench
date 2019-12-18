#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct inode {int dummy; } ;
struct extent_state {int state; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 scalar_t__ BTRFS_MAX_EXTENT_SIZE ; 
 int EXTENT_DELALLOC ; 
 int /*<<< orphan*/  btrfs_mod_outstanding_extents (TYPE_1__*,int) ; 
 scalar_t__ count_max_extents (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_split_delalloc_extent(struct inode *inode,
				 struct extent_state *orig, u64 split)
{
	u64 size;

	/* not delalloc, ignore it */
	if (!(orig->state & EXTENT_DELALLOC))
		return;

	size = orig->end - orig->start + 1;
	if (size > BTRFS_MAX_EXTENT_SIZE) {
		u32 num_extents;
		u64 new_size;

		/*
		 * See the explanation in btrfs_merge_delalloc_extent, the same
		 * applies here, just in reverse.
		 */
		new_size = orig->end - split + 1;
		num_extents = count_max_extents(new_size);
		new_size = split - orig->start;
		num_extents += count_max_extents(new_size);
		if (count_max_extents(size) >= num_extents)
			return;
	}

	spin_lock(&BTRFS_I(inode)->lock);
	btrfs_mod_outstanding_extents(BTRFS_I(inode), 1);
	spin_unlock(&BTRFS_I(inode)->lock);
}