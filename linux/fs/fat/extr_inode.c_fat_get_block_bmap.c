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
struct super_block {unsigned long s_blocksize_bits; } ;
struct inode {unsigned long i_blkbits; struct super_block* i_sb; } ;
struct buffer_head {unsigned long b_size; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int fat_bmap (struct inode*,scalar_t__,scalar_t__*,unsigned long*,int,int) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,struct super_block*,scalar_t__) ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static int fat_get_block_bmap(struct inode *inode, sector_t iblock,
		struct buffer_head *bh_result, int create)
{
	struct super_block *sb = inode->i_sb;
	unsigned long max_blocks = bh_result->b_size >> inode->i_blkbits;
	int err;
	sector_t bmap;
	unsigned long mapped_blocks;

	BUG_ON(create != 0);

	err = fat_bmap(inode, iblock, &bmap, &mapped_blocks, create, true);
	if (err)
		return err;

	if (bmap) {
		map_bh(bh_result, sb, bmap);
		max_blocks = min(mapped_blocks, max_blocks);
	}

	bh_result->b_size = max_blocks << sb->s_blocksize_bits;

	return 0;
}