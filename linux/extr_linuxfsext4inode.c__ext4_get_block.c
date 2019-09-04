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
struct inode {int i_blkbits; TYPE_1__* i_sb; } ;
struct ext4_map_blocks {int m_len; int /*<<< orphan*/  m_flags; int /*<<< orphan*/  m_pblk; int /*<<< orphan*/  m_lblk; } ;
struct buffer_head {int b_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_journal_current_handle () ; 
 int ext4_map_blocks (int /*<<< orphan*/ ,struct inode*,struct ext4_map_blocks*,int) ; 
 int /*<<< orphan*/  ext4_update_bh_state (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ext4_get_block(struct inode *inode, sector_t iblock,
			   struct buffer_head *bh, int flags)
{
	struct ext4_map_blocks map;
	int ret = 0;

	if (ext4_has_inline_data(inode))
		return -ERANGE;

	map.m_lblk = iblock;
	map.m_len = bh->b_size >> inode->i_blkbits;

	ret = ext4_map_blocks(ext4_journal_current_handle(), inode, &map,
			      flags);
	if (ret > 0) {
		map_bh(bh, inode->i_sb, map.m_pblk);
		ext4_update_bh_state(bh, map.m_flags);
		bh->b_size = inode->i_sb->s_blocksize * map.m_len;
		ret = 0;
	} else if (ret == 0) {
		/* hole case, need to fill in bh->b_size */
		bh->b_size = inode->i_sb->s_blocksize * map.m_len;
	}
	return ret;
}