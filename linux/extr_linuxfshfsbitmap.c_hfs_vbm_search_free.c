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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct TYPE_2__ {scalar_t__ fs_ablocks; int /*<<< orphan*/  bitmap_lock; int /*<<< orphan*/  free_ablocks; void* bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP ; 
 TYPE_1__* HFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  hfs_bitmap_dirty (struct super_block*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ hfs_find_set_zero_bits (void*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

u32 hfs_vbm_search_free(struct super_block *sb, u32 goal, u32 *num_bits)
{
	void *bitmap;
	u32 pos;

	/* make sure we have actual work to perform */
	if (!*num_bits)
		return 0;

	mutex_lock(&HFS_SB(sb)->bitmap_lock);
	bitmap = HFS_SB(sb)->bitmap;

	pos = hfs_find_set_zero_bits(bitmap, HFS_SB(sb)->fs_ablocks, goal, num_bits);
	if (pos >= HFS_SB(sb)->fs_ablocks) {
		if (goal)
			pos = hfs_find_set_zero_bits(bitmap, goal, 0, num_bits);
		if (pos >= HFS_SB(sb)->fs_ablocks) {
			*num_bits = pos = 0;
			goto out;
		}
	}

	hfs_dbg(BITMAP, "alloc_bits: %u,%u\n", pos, *num_bits);
	HFS_SB(sb)->free_ablocks -= *num_bits;
	hfs_bitmap_dirty(sb);
out:
	mutex_unlock(&HFS_SB(sb)->bitmap_lock);
	return pos;
}