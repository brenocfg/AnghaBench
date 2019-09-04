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
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 struct extent_buffer* alloc_extent_buffer (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 struct extent_buffer* alloc_test_extent_buffer (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_is_testing (struct btrfs_fs_info*) ; 

struct extent_buffer *btrfs_find_create_tree_block(
						struct btrfs_fs_info *fs_info,
						u64 bytenr)
{
	if (btrfs_is_testing(fs_info))
		return alloc_test_extent_buffer(fs_info, bytenr);
	return alloc_extent_buffer(fs_info, bytenr);
}