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
struct btrfs_space_info {int /*<<< orphan*/  total_bytes_pinned; } ;
struct btrfs_fs_info {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct btrfs_space_info*) ; 
 scalar_t__ BTRFS_BLOCK_GROUP_DATA ; 
 scalar_t__ BTRFS_BLOCK_GROUP_METADATA ; 
 scalar_t__ BTRFS_BLOCK_GROUP_SYSTEM ; 
 scalar_t__ BTRFS_CHUNK_TREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_TOTAL_BYTES_PINNED_BATCH ; 
 struct btrfs_space_info* __find_space_info (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_pinned_bytes(struct btrfs_fs_info *fs_info, s64 num_bytes,
			     bool metadata, u64 root_objectid)
{
	struct btrfs_space_info *space_info;
	u64 flags;

	if (metadata) {
		if (root_objectid == BTRFS_CHUNK_TREE_OBJECTID)
			flags = BTRFS_BLOCK_GROUP_SYSTEM;
		else
			flags = BTRFS_BLOCK_GROUP_METADATA;
	} else {
		flags = BTRFS_BLOCK_GROUP_DATA;
	}

	space_info = __find_space_info(fs_info, flags);
	ASSERT(space_info);
	percpu_counter_add_batch(&space_info->total_bytes_pinned, num_bytes,
		    BTRFS_TOTAL_BYTES_PINNED_BATCH);
}