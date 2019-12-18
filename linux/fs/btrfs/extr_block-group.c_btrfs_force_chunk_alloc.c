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
struct btrfs_trans_handle {int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_ALLOC_FORCE ; 
 int btrfs_chunk_alloc (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_get_alloc_profile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_force_chunk_alloc(struct btrfs_trans_handle *trans, u64 type)
{
	u64 alloc_flags = btrfs_get_alloc_profile(trans->fs_info, type);

	return btrfs_chunk_alloc(trans, alloc_flags, CHUNK_ALLOC_FORCE);
}