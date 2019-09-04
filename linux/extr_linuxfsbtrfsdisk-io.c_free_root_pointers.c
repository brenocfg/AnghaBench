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
struct btrfs_fs_info {int /*<<< orphan*/  free_space_root; int /*<<< orphan*/  chunk_root; int /*<<< orphan*/  uuid_root; int /*<<< orphan*/  quota_root; int /*<<< orphan*/  csum_root; int /*<<< orphan*/  extent_root; int /*<<< orphan*/  dev_root; int /*<<< orphan*/  tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_root_extent_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_root_pointers(struct btrfs_fs_info *info, int chunk_root)
{
	free_root_extent_buffers(info->tree_root);

	free_root_extent_buffers(info->dev_root);
	free_root_extent_buffers(info->extent_root);
	free_root_extent_buffers(info->csum_root);
	free_root_extent_buffers(info->quota_root);
	free_root_extent_buffers(info->uuid_root);
	if (chunk_root)
		free_root_extent_buffers(info->chunk_root);
	free_root_extent_buffers(info->free_space_root);
}