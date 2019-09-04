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
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSHONCOMMIT ; 
 int /*<<< orphan*/  U64_MAX ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_wait_ordered_roots (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void btrfs_wait_delalloc_flush(struct btrfs_fs_info *fs_info)
{
	if (btrfs_test_opt(fs_info, FLUSHONCOMMIT))
		btrfs_wait_ordered_roots(fs_info, U64_MAX, 0, (u64)-1);
}