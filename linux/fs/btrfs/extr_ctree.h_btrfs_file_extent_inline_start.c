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
struct btrfs_file_extent_item {int dummy; } ;

/* Variables and functions */
 unsigned long BTRFS_FILE_EXTENT_INLINE_DATA_START ; 

__attribute__((used)) static inline unsigned long
btrfs_file_extent_inline_start(const struct btrfs_file_extent_item *e)
{
	return (unsigned long)e + BTRFS_FILE_EXTENT_INLINE_DATA_START;
}