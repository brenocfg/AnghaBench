#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* io_end; } ;
struct ext4_map_blocks {int m_flags; scalar_t__ m_len; } ;
struct mpage_da_data {TYPE_1__ io_submit; struct ext4_map_blocks map; struct inode* inode; } ;
struct inode {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * h_rsv_handle; } ;
typedef  TYPE_2__ handle_t ;
struct TYPE_9__ {int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int BH_Delay ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EXT4_GET_BLOCKS_CREATE ; 
 int EXT4_GET_BLOCKS_DELALLOC_RESERVE ; 
 int EXT4_GET_BLOCKS_IO_CREATE_EXT ; 
 int EXT4_GET_BLOCKS_IO_SUBMIT ; 
 int EXT4_GET_BLOCKS_METADATA_NOFAIL ; 
 int EXT4_MAP_UNWRITTEN ; 
 scalar_t__ ext4_handle_valid (TYPE_2__*) ; 
 int ext4_map_blocks (TYPE_2__*,struct inode*,struct ext4_map_blocks*,int) ; 
 int /*<<< orphan*/  ext4_set_io_unwritten_flag (struct inode*,TYPE_4__*) ; 
 int ext4_should_dioread_nolock (struct inode*) ; 
 int /*<<< orphan*/  trace_ext4_da_write_pages_extent (struct inode*,struct ext4_map_blocks*) ; 

__attribute__((used)) static int mpage_map_one_extent(handle_t *handle, struct mpage_da_data *mpd)
{
	struct inode *inode = mpd->inode;
	struct ext4_map_blocks *map = &mpd->map;
	int get_blocks_flags;
	int err, dioread_nolock;

	trace_ext4_da_write_pages_extent(inode, map);
	/*
	 * Call ext4_map_blocks() to allocate any delayed allocation blocks, or
	 * to convert an unwritten extent to be initialized (in the case
	 * where we have written into one or more preallocated blocks).  It is
	 * possible that we're going to need more metadata blocks than
	 * previously reserved. However we must not fail because we're in
	 * writeback and there is nothing we can do about it so it might result
	 * in data loss.  So use reserved blocks to allocate metadata if
	 * possible.
	 *
	 * We pass in the magic EXT4_GET_BLOCKS_DELALLOC_RESERVE if
	 * the blocks in question are delalloc blocks.  This indicates
	 * that the blocks and quotas has already been checked when
	 * the data was copied into the page cache.
	 */
	get_blocks_flags = EXT4_GET_BLOCKS_CREATE |
			   EXT4_GET_BLOCKS_METADATA_NOFAIL |
			   EXT4_GET_BLOCKS_IO_SUBMIT;
	dioread_nolock = ext4_should_dioread_nolock(inode);
	if (dioread_nolock)
		get_blocks_flags |= EXT4_GET_BLOCKS_IO_CREATE_EXT;
	if (map->m_flags & (1 << BH_Delay))
		get_blocks_flags |= EXT4_GET_BLOCKS_DELALLOC_RESERVE;

	err = ext4_map_blocks(handle, inode, map, get_blocks_flags);
	if (err < 0)
		return err;
	if (dioread_nolock && (map->m_flags & EXT4_MAP_UNWRITTEN)) {
		if (!mpd->io_submit.io_end->handle &&
		    ext4_handle_valid(handle)) {
			mpd->io_submit.io_end->handle = handle->h_rsv_handle;
			handle->h_rsv_handle = NULL;
		}
		ext4_set_io_unwritten_flag(inode, mpd->io_submit.io_end);
	}

	BUG_ON(map->m_len == 0);
	return 0;
}