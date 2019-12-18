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
struct btrfs_space_info {int /*<<< orphan*/  total_bytes_pinned; } ;
struct btrfs_ref {int /*<<< orphan*/  len; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct btrfs_space_info*) ; 
 int /*<<< orphan*/  BTRFS_TOTAL_BYTES_PINNED_BATCH ; 
 struct btrfs_space_info* btrfs_find_space_info (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_ref_to_space_flags (struct btrfs_ref*) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sub_pinned_bytes(struct btrfs_fs_info *fs_info,
			     struct btrfs_ref *ref)
{
	struct btrfs_space_info *space_info;
	u64 flags = generic_ref_to_space_flags(ref);

	space_info = btrfs_find_space_info(fs_info, flags);
	ASSERT(space_info);
	percpu_counter_add_batch(&space_info->total_bytes_pinned, -ref->len,
		    BTRFS_TOTAL_BYTES_PINNED_BATCH);
}