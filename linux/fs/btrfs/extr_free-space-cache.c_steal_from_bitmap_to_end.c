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
typedef  unsigned long u64 ;
struct btrfs_free_space_ctl {unsigned long unit; } ;
struct btrfs_free_space {unsigned long offset; unsigned long bytes; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BITMAP ; 
 int /*<<< orphan*/  __bitmap_clear_bits (struct btrfs_free_space_ctl*,struct btrfs_free_space*,unsigned long const,unsigned long) ; 
 int /*<<< orphan*/  bitmap_clear_bits (struct btrfs_free_space_ctl*,struct btrfs_free_space*,unsigned long const,unsigned long) ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  free_bitmap (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 
 unsigned long offset_to_bit (unsigned long,unsigned long,unsigned long const) ; 
 unsigned long offset_to_bitmap (struct btrfs_free_space_ctl*,unsigned long const) ; 
 struct btrfs_free_space* tree_search_offset (struct btrfs_free_space_ctl*,unsigned long const,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool steal_from_bitmap_to_end(struct btrfs_free_space_ctl *ctl,
				     struct btrfs_free_space *info,
				     bool update_stat)
{
	struct btrfs_free_space *bitmap;
	unsigned long i;
	unsigned long j;
	const u64 end = info->offset + info->bytes;
	const u64 bitmap_offset = offset_to_bitmap(ctl, end);
	u64 bytes;

	bitmap = tree_search_offset(ctl, bitmap_offset, 1, 0);
	if (!bitmap)
		return false;

	i = offset_to_bit(bitmap->offset, ctl->unit, end);
	j = find_next_zero_bit(bitmap->bitmap, BITS_PER_BITMAP, i);
	if (j == i)
		return false;
	bytes = (j - i) * ctl->unit;
	info->bytes += bytes;

	if (update_stat)
		bitmap_clear_bits(ctl, bitmap, end, bytes);
	else
		__bitmap_clear_bits(ctl, bitmap, end, bytes);

	if (!bitmap->bytes)
		free_bitmap(ctl, bitmap);

	return true;
}