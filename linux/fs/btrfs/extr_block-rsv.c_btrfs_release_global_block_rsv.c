#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_8__ {scalar_t__ reserved; scalar_t__ size; } ;
struct TYPE_7__ {scalar_t__ size; scalar_t__ reserved; } ;
struct TYPE_6__ {scalar_t__ size; scalar_t__ reserved; } ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ reserved; } ;
struct btrfs_fs_info {TYPE_4__ delayed_refs_rsv; TYPE_3__ delayed_block_rsv; TYPE_2__ chunk_block_rsv; TYPE_1__ trans_block_rsv; int /*<<< orphan*/  global_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_block_rsv_release (struct btrfs_fs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void btrfs_release_global_block_rsv(struct btrfs_fs_info *fs_info)
{
	btrfs_block_rsv_release(fs_info, &fs_info->global_block_rsv, (u64)-1);
	WARN_ON(fs_info->trans_block_rsv.size > 0);
	WARN_ON(fs_info->trans_block_rsv.reserved > 0);
	WARN_ON(fs_info->chunk_block_rsv.size > 0);
	WARN_ON(fs_info->chunk_block_rsv.reserved > 0);
	WARN_ON(fs_info->delayed_block_rsv.size > 0);
	WARN_ON(fs_info->delayed_block_rsv.reserved > 0);
	WARN_ON(fs_info->delayed_refs_rsv.reserved > 0);
	WARN_ON(fs_info->delayed_refs_rsv.size > 0);
}