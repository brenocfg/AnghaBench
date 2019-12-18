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
struct inode {int dummy; } ;
struct erofs_map_blocks {int m_la; int m_flags; int /*<<< orphan*/  m_pa; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  EROFS_GET_BLOCKS_RAW ; 
 int EROFS_MAP_MAPPED ; 
 int /*<<< orphan*/  erofs_blknr (int /*<<< orphan*/ ) ; 
 int erofs_map_blocks (struct inode*,struct erofs_map_blocks*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int erofs_get_block(struct inode *inode, sector_t iblock,
			   struct buffer_head *bh, int create)
{
	struct erofs_map_blocks map = {
		.m_la = iblock << 9,
	};
	int err;

	err = erofs_map_blocks(inode, &map, EROFS_GET_BLOCKS_RAW);
	if (err)
		return err;

	if (map.m_flags & EROFS_MAP_MAPPED)
		bh->b_blocknr = erofs_blknr(map.m_pa);

	return err;
}