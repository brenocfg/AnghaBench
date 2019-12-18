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
typedef  int u64 ;
struct inode {int i_blkbits; int /*<<< orphan*/  i_sb; } ;
struct f2fs_map_blocks {int m_len; int m_seg_type; int m_may_create; int m_flags; int /*<<< orphan*/  m_pblk; int /*<<< orphan*/ * m_next_extent; int /*<<< orphan*/ * m_next_pgofs; int /*<<< orphan*/  m_lblk; } ;
struct buffer_head {int b_size; int b_state; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int F2FS_MAP_FLAGS ; 
 int f2fs_map_blocks (struct inode*,struct f2fs_map_blocks*,int,int) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __get_data_block(struct inode *inode, sector_t iblock,
			struct buffer_head *bh, int create, int flag,
			pgoff_t *next_pgofs, int seg_type, bool may_write)
{
	struct f2fs_map_blocks map;
	int err;

	map.m_lblk = iblock;
	map.m_len = bh->b_size >> inode->i_blkbits;
	map.m_next_pgofs = next_pgofs;
	map.m_next_extent = NULL;
	map.m_seg_type = seg_type;
	map.m_may_create = may_write;

	err = f2fs_map_blocks(inode, &map, create, flag);
	if (!err) {
		map_bh(bh, inode->i_sb, map.m_pblk);
		bh->b_state = (bh->b_state & ~F2FS_MAP_FLAGS) | map.m_flags;
		bh->b_size = (u64)map.m_len << inode->i_blkbits;
	}
	return err;
}