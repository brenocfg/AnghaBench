#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {scalar_t__ size; scalar_t__ reserved; } ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ reserved; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ reserved; } ;
struct btrfs_fs_info {TYPE_3__ delayed_block_rsv; TYPE_2__ chunk_block_rsv; TYPE_1__ trans_block_rsv; int /*<<< orphan*/  global_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  block_rsv_release_bytes (struct btrfs_fs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_global_block_rsv(struct btrfs_fs_info *fs_info)
{
	block_rsv_release_bytes(fs_info, &fs_info->global_block_rsv, NULL,
				(u64)-1, NULL);
	WARN_ON(fs_info->trans_block_rsv.size > 0);
	WARN_ON(fs_info->trans_block_rsv.reserved > 0);
	WARN_ON(fs_info->chunk_block_rsv.size > 0);
	WARN_ON(fs_info->chunk_block_rsv.reserved > 0);
	WARN_ON(fs_info->delayed_block_rsv.size > 0);
	WARN_ON(fs_info->delayed_block_rsv.reserved > 0);
}