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
struct extent_state {int state; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 scalar_t__ BTRFS_MAX_EXTENT_SIZE ; 
 int EXTENT_DELALLOC ; 
 int /*<<< orphan*/  btrfs_mod_outstanding_extents (TYPE_1__*,int) ; 
 scalar_t__ count_max_extents (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_merge_delalloc_extent(struct inode *inode, struct extent_state *new,
				 struct extent_state *other)
{
	u64 new_size, old_size;
	u32 num_extents;

	/* not delalloc, ignore it */
	if (!(other->state & EXTENT_DELALLOC))
		return;

	if (new->start > other->start)
		new_size = new->end - other->start + 1;
	else
		new_size = other->end - new->start + 1;

	/* we're not bigger than the max, unreserve the space and go */
	if (new_size <= BTRFS_MAX_EXTENT_SIZE) {
		spin_lock(&BTRFS_I(inode)->lock);
		btrfs_mod_outstanding_extents(BTRFS_I(inode), -1);
		spin_unlock(&BTRFS_I(inode)->lock);
		return;
	}

	/*
	 * We have to add up either side to figure out how many extents were
	 * accounted for before we merged into one big extent.  If the number of
	 * extents we accounted for is <= the amount we need for the new range
	 * then we can return, otherwise drop.  Think of it like this
	 *
	 * [ 4k][MAX_SIZE]
	 *
	 * So we've grown the extent by a MAX_SIZE extent, this would mean we
	 * need 2 outstanding extents, on one side we have 1 and the other side
	 * we have 1 so they are == and we can return.  But in this case
	 *
	 * [MAX_SIZE+4k][MAX_SIZE+4k]
	 *
	 * Each range on their own accounts for 2 extents, but merged together
	 * they are only 3 extents worth of accounting, so we need to drop in
	 * this case.
	 */
	old_size = other->end - other->start + 1;
	num_extents = count_max_extents(old_size);
	old_size = new->end - new->start + 1;
	num_extents += count_max_extents(old_size);
	if (count_max_extents(new_size) >= num_extents)
		return;

	spin_lock(&BTRFS_I(inode)->lock);
	btrfs_mod_outstanding_extents(BTRFS_I(inode), -1);
	spin_unlock(&BTRFS_I(inode)->lock);
}