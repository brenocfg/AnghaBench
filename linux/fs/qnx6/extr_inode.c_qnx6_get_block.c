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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int qnx6_block_map (struct inode*,scalar_t__) ; 

__attribute__((used)) static int qnx6_get_block(struct inode *inode, sector_t iblock,
			struct buffer_head *bh, int create)
{
	unsigned phys;

	pr_debug("qnx6_get_block inode=[%ld] iblock=[%ld]\n",
		 inode->i_ino, (unsigned long)iblock);

	phys = qnx6_block_map(inode, iblock);
	if (phys) {
		/* logical block is before EOF */
		map_bh(bh, inode->i_sb, phys);
	}
	return 0;
}