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
struct inode {scalar_t__ i_blocks; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int EROFS ; 
 long efs_map_block (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,long) ; 

int efs_get_block(struct inode *inode, sector_t iblock,
		  struct buffer_head *bh_result, int create)
{
	int error = -EROFS;
	long phys;

	if (create)
		return error;
	if (iblock >= inode->i_blocks) {
#ifdef DEBUG
		/*
		 * i have no idea why this happens as often as it does
		 */
		pr_warn("%s(): block %d >= %ld (filesize %ld)\n",
			__func__, block, inode->i_blocks, inode->i_size);
#endif
		return 0;
	}
	phys = efs_map_block(inode, iblock);
	if (phys)
		map_bh(bh_result, inode->i_sb, phys);
	return 0;
}