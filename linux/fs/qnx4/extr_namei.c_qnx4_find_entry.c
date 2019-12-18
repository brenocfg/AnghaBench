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
struct qnx4_inode_entry {int dummy; } ;
struct inode {unsigned long i_size; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {unsigned long b_size; scalar_t__ b_data; } ;

/* Variables and functions */
 unsigned long QNX4_BLOCK_SIZE ; 
 unsigned long QNX4_DIR_ENTRY_SIZE ; 
 unsigned long QNX4_INODES_PER_BLOCK ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 unsigned long qnx4_block_map (struct inode*,unsigned long) ; 
 scalar_t__ qnx4_match (int,char const*,struct buffer_head*,unsigned long*) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static struct buffer_head *qnx4_find_entry(int len, struct inode *dir,
	   const char *name, struct qnx4_inode_entry **res_dir, int *ino)
{
	unsigned long block, offset, blkofs;
	struct buffer_head *bh;

	*res_dir = NULL;
	bh = NULL;
	block = offset = blkofs = 0;
	while (blkofs * QNX4_BLOCK_SIZE + offset < dir->i_size) {
		if (!bh) {
			block = qnx4_block_map(dir, blkofs);
			if (block)
				bh = sb_bread(dir->i_sb, block);
			if (!bh) {
				blkofs++;
				continue;
			}
		}
		*res_dir = (struct qnx4_inode_entry *) (bh->b_data + offset);
		if (qnx4_match(len, name, bh, &offset)) {
			*ino = block * QNX4_INODES_PER_BLOCK +
			    (offset / QNX4_DIR_ENTRY_SIZE) - 1;
			return bh;
		}
		if (offset < bh->b_size) {
			continue;
		}
		brelse(bh);
		bh = NULL;
		offset = 0;
		blkofs++;
	}
	brelse(bh);
	*res_dir = NULL;
	return NULL;
}