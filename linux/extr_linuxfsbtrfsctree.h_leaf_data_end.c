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
typedef  scalar_t__ u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 unsigned int BTRFS_LEAF_DATA_SIZE (struct btrfs_fs_info const*) ; 
 scalar_t__ btrfs_header_nritems (struct extent_buffer const*) ; 
 unsigned int btrfs_item_offset_nr (struct extent_buffer const*,scalar_t__) ; 

__attribute__((used)) static inline unsigned int leaf_data_end(const struct btrfs_fs_info *fs_info,
					 const struct extent_buffer *leaf)
{
	u32 nr = btrfs_header_nritems(leaf);

	if (nr == 0)
		return BTRFS_LEAF_DATA_SIZE(fs_info);
	return btrfs_item_offset_nr(leaf, nr - 1);
}