#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_sb; } ;
struct ext4_super_block {int /*<<< orphan*/  s_first_data_block; } ;
struct ext4_extent_header {scalar_t__ eh_depth; void* eh_max; void* eh_entries; int /*<<< orphan*/  eh_magic; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_data; } ;
struct TYPE_12__ {struct ext4_super_block* s_es; } ;
struct TYPE_11__ {int /*<<< orphan*/  ee_block; } ;
struct TYPE_10__ {int /*<<< orphan*/  ei_block; } ;
struct TYPE_9__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_EXT_MAGIC ; 
 TYPE_8__* EXT4_I (struct inode*) ; 
 unsigned int EXT4_MB_HINT_TRY_GOAL ; 
 TYPE_6__* EXT4_SB (TYPE_1__*) ; 
 TYPE_5__* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 TYPE_2__* EXT_FIRST_INDEX (struct ext4_extent_header*) ; 
 int GFP_NOFS ; 
 int __GFP_MOVABLE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (int) ; 
 int ext4_ext_space_block (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_ext_space_block_idx (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_ext_space_root_idx (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_extent_block_csum_set (struct inode*,struct ext4_extent_header*) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 scalar_t__ ext4_idx_pblock (TYPE_2__*) ; 
 int /*<<< orphan*/  ext4_idx_store_pblock (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ext4_inode_to_goal_block (struct inode*) ; 
 int ext4_journal_get_create_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_new_meta_blocks (int /*<<< orphan*/ *,struct inode*,scalar_t__,unsigned int,int /*<<< orphan*/ *,int*) ; 
 struct ext4_extent_header* ext_block_hdr (struct buffer_head*) ; 
 int /*<<< orphan*/  ext_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ext_depth (struct inode*) ; 
 struct ext4_extent_header* ext_inode_hdr (struct inode*) ; 
 int /*<<< orphan*/  le16_add_cpu (scalar_t__*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (void*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct buffer_head* sb_getblk_gfp (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int ext4_ext_grow_indepth(handle_t *handle, struct inode *inode,
				 unsigned int flags)
{
	struct ext4_extent_header *neh;
	struct buffer_head *bh;
	ext4_fsblk_t newblock, goal = 0;
	struct ext4_super_block *es = EXT4_SB(inode->i_sb)->s_es;
	int err = 0;
	size_t ext_size = 0;

	/* Try to prepend new index to old one */
	if (ext_depth(inode))
		goal = ext4_idx_pblock(EXT_FIRST_INDEX(ext_inode_hdr(inode)));
	if (goal > le32_to_cpu(es->s_first_data_block)) {
		flags |= EXT4_MB_HINT_TRY_GOAL;
		goal--;
	} else
		goal = ext4_inode_to_goal_block(inode);
	newblock = ext4_new_meta_blocks(handle, inode, goal, flags,
					NULL, &err);
	if (newblock == 0)
		return err;

	bh = sb_getblk_gfp(inode->i_sb, newblock, __GFP_MOVABLE | GFP_NOFS);
	if (unlikely(!bh))
		return -ENOMEM;
	lock_buffer(bh);

	err = ext4_journal_get_create_access(handle, bh);
	if (err) {
		unlock_buffer(bh);
		goto out;
	}

	ext_size = sizeof(EXT4_I(inode)->i_data);
	/* move top-level index/leaf into new block */
	memmove(bh->b_data, EXT4_I(inode)->i_data, ext_size);
	/* zero out unused area in the extent block */
	memset(bh->b_data + ext_size, 0, inode->i_sb->s_blocksize - ext_size);

	/* set size of new block */
	neh = ext_block_hdr(bh);
	/* old root could have indexes or leaves
	 * so calculate e_max right way */
	if (ext_depth(inode))
		neh->eh_max = cpu_to_le16(ext4_ext_space_block_idx(inode, 0));
	else
		neh->eh_max = cpu_to_le16(ext4_ext_space_block(inode, 0));
	neh->eh_magic = EXT4_EXT_MAGIC;
	ext4_extent_block_csum_set(inode, neh);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);

	err = ext4_handle_dirty_metadata(handle, inode, bh);
	if (err)
		goto out;

	/* Update top-level index: num,max,pointer */
	neh = ext_inode_hdr(inode);
	neh->eh_entries = cpu_to_le16(1);
	ext4_idx_store_pblock(EXT_FIRST_INDEX(neh), newblock);
	if (neh->eh_depth == 0) {
		/* Root extent block becomes index block */
		neh->eh_max = cpu_to_le16(ext4_ext_space_root_idx(inode, 0));
		EXT_FIRST_INDEX(neh)->ei_block =
			EXT_FIRST_EXTENT(neh)->ee_block;
	}
	ext_debug("new root: num %d(%d), lblock %d, ptr %llu\n",
		  le16_to_cpu(neh->eh_entries), le16_to_cpu(neh->eh_max),
		  le32_to_cpu(EXT_FIRST_INDEX(neh)->ei_block),
		  ext4_idx_pblock(EXT_FIRST_INDEX(neh)));

	le16_add_cpu(&neh->eh_depth, 1);
	ext4_mark_inode_dirty(handle, inode);
out:
	brelse(bh);

	return err;
}