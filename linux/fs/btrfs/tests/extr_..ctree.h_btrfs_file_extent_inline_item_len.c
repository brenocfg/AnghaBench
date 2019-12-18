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
struct btrfs_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FILE_EXTENT_INLINE_DATA_START ; 
 scalar_t__ btrfs_item_size (struct extent_buffer const*,struct btrfs_item*) ; 

__attribute__((used)) static inline u32 btrfs_file_extent_inline_item_len(
						const struct extent_buffer *eb,
						struct btrfs_item *e)
{
	return btrfs_item_size(eb, e) - BTRFS_FILE_EXTENT_INLINE_DATA_START;
}