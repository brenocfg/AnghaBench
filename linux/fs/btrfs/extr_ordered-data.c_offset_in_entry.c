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
struct btrfs_ordered_extent {scalar_t__ file_offset; scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static int offset_in_entry(struct btrfs_ordered_extent *entry, u64 file_offset)
{
	if (file_offset < entry->file_offset ||
	    entry->file_offset + entry->len <= file_offset)
		return 0;
	return 1;
}