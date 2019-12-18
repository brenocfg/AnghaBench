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
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_rsv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfs_init_metadata_block_rsv (struct btrfs_fs_info*,struct btrfs_block_rsv*,unsigned short) ; 
 struct btrfs_block_rsv* kmalloc (int,int /*<<< orphan*/ ) ; 

struct btrfs_block_rsv *btrfs_alloc_block_rsv(struct btrfs_fs_info *fs_info,
					      unsigned short type)
{
	struct btrfs_block_rsv *block_rsv;

	block_rsv = kmalloc(sizeof(*block_rsv), GFP_NOFS);
	if (!block_rsv)
		return NULL;

	btrfs_init_metadata_block_rsv(fs_info, block_rsv, type);
	return block_rsv;
}