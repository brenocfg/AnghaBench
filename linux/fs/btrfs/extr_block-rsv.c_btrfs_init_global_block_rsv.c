#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct btrfs_space_info {int dummy; } ;
struct TYPE_15__ {struct btrfs_space_info* space_info; } ;
struct TYPE_13__ {struct btrfs_space_info* space_info; } ;
struct TYPE_21__ {struct btrfs_space_info* space_info; } ;
struct TYPE_18__ {struct btrfs_space_info* space_info; } ;
struct TYPE_17__ {struct btrfs_space_info* space_info; } ;
struct TYPE_16__ {struct btrfs_space_info* space_info; } ;
struct btrfs_fs_info {TYPE_12__ chunk_block_rsv; TYPE_11__* chunk_root; TYPE_10__ global_block_rsv; TYPE_9__* quota_root; TYPE_8__* tree_root; TYPE_7__* dev_root; TYPE_6__ delayed_refs_rsv; TYPE_5__* csum_root; TYPE_4__* extent_root; TYPE_3__ delayed_block_rsv; TYPE_2__ empty_block_rsv; TYPE_1__ trans_block_rsv; } ;
struct TYPE_24__ {TYPE_10__* block_rsv; } ;
struct TYPE_23__ {TYPE_10__* block_rsv; } ;
struct TYPE_22__ {TYPE_10__* block_rsv; } ;
struct TYPE_20__ {TYPE_6__* block_rsv; } ;
struct TYPE_19__ {TYPE_6__* block_rsv; } ;
struct TYPE_14__ {TYPE_12__* block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_METADATA ; 
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_SYSTEM ; 
 struct btrfs_space_info* btrfs_find_space_info (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_update_global_block_rsv (struct btrfs_fs_info*) ; 

void btrfs_init_global_block_rsv(struct btrfs_fs_info *fs_info)
{
	struct btrfs_space_info *space_info;

	space_info = btrfs_find_space_info(fs_info, BTRFS_BLOCK_GROUP_SYSTEM);
	fs_info->chunk_block_rsv.space_info = space_info;

	space_info = btrfs_find_space_info(fs_info, BTRFS_BLOCK_GROUP_METADATA);
	fs_info->global_block_rsv.space_info = space_info;
	fs_info->trans_block_rsv.space_info = space_info;
	fs_info->empty_block_rsv.space_info = space_info;
	fs_info->delayed_block_rsv.space_info = space_info;
	fs_info->delayed_refs_rsv.space_info = space_info;

	fs_info->extent_root->block_rsv = &fs_info->delayed_refs_rsv;
	fs_info->csum_root->block_rsv = &fs_info->delayed_refs_rsv;
	fs_info->dev_root->block_rsv = &fs_info->global_block_rsv;
	fs_info->tree_root->block_rsv = &fs_info->global_block_rsv;
	if (fs_info->quota_root)
		fs_info->quota_root->block_rsv = &fs_info->global_block_rsv;
	fs_info->chunk_root->block_rsv = &fs_info->chunk_block_rsv;

	btrfs_update_global_block_rsv(fs_info);
}