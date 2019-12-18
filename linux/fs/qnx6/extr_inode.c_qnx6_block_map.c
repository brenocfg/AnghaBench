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
typedef  unsigned int u32 ;
struct super_block {int dummy; } ;
struct qnx6_sb_info {int s_ptrbits; } ;
struct qnx6_inode_info {int di_filelevels; int /*<<< orphan*/ * di_block_ptr; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __fs32 ;

/* Variables and functions */
 struct qnx6_inode_info* QNX6_I (struct inode*) ; 
 int QNX6_NO_DIRECT_POINTERS ; 
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  qnx6_check_blockptr (int /*<<< orphan*/ ) ; 
 unsigned int qnx6_get_devblock (struct super_block*,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (struct super_block*,unsigned int) ; 

__attribute__((used)) static unsigned qnx6_block_map(struct inode *inode, unsigned no)
{
	struct super_block *s = inode->i_sb;
	struct qnx6_sb_info *sbi = QNX6_SB(s);
	struct qnx6_inode_info *ei = QNX6_I(inode);
	unsigned block = 0;
	struct buffer_head *bh;
	__fs32 ptr;
	int levelptr;
	int ptrbits = sbi->s_ptrbits;
	int bitdelta;
	u32 mask = (1 << ptrbits) - 1;
	int depth = ei->di_filelevels;
	int i;

	bitdelta = ptrbits * depth;
	levelptr = no >> bitdelta;

	if (levelptr > QNX6_NO_DIRECT_POINTERS - 1) {
		pr_err("Requested file block number (%u) too big.", no);
		return 0;
	}

	block = qnx6_get_devblock(s, ei->di_block_ptr[levelptr]);

	for (i = 0; i < depth; i++) {
		bh = sb_bread(s, block);
		if (!bh) {
			pr_err("Error reading block (%u)\n", block);
			return 0;
		}
		bitdelta -= ptrbits;
		levelptr = (no >> bitdelta) & mask;
		ptr = ((__fs32 *)bh->b_data)[levelptr];

		if (!qnx6_check_blockptr(ptr))
			return 0;

		block = qnx6_get_devblock(s, ptr);
		brelse(bh);
	}
	return block;
}