#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_sb; } ;
struct ext4_map_blocks {int m_len; int /*<<< orphan*/  m_flags; int /*<<< orphan*/  m_pblk; int /*<<< orphan*/  m_lblk; } ;
struct buffer_head {scalar_t__ b_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ buffer_unwritten (struct buffer_head*) ; 
 int ext4_da_map_blocks (struct inode*,int /*<<< orphan*/ ,struct ext4_map_blocks*,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_update_bh_state (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 

int ext4_da_get_block_prep(struct inode *inode, sector_t iblock,
			   struct buffer_head *bh, int create)
{
	struct ext4_map_blocks map;
	int ret = 0;

	BUG_ON(create == 0);
	BUG_ON(bh->b_size != inode->i_sb->s_blocksize);

	map.m_lblk = iblock;
	map.m_len = 1;

	/*
	 * first, we need to know whether the block is allocated already
	 * preallocated blocks are unmapped but should treated
	 * the same as allocated blocks.
	 */
	ret = ext4_da_map_blocks(inode, iblock, &map, bh);
	if (ret <= 0)
		return ret;

	map_bh(bh, inode->i_sb, map.m_pblk);
	ext4_update_bh_state(bh, map.m_flags);

	if (buffer_unwritten(bh)) {
		/* A delayed write to unwritten bh should be marked
		 * new and mapped.  Mapped ensures that we don't do
		 * get_block multiple times when we write to the same
		 * offset and new ensures that we do proper zero out
		 * for partial write.
		 */
		set_buffer_new(bh);
		set_buffer_mapped(bh);
	}
	return 0;
}