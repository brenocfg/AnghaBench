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
typedef  scalar_t__ u64 ;
struct ufs_sb_private_info {unsigned int s_apb; int /*<<< orphan*/  s_fpb; int /*<<< orphan*/  s_bsize; } ;
struct ufs_buffer_head {int dummy; } ;
struct to_free {struct inode* inode; } ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  free_data (struct to_free*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubh_bforget (struct ufs_buffer_head*) ; 
 struct ufs_buffer_head* ubh_bread (struct super_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* ubh_get_data_ptr (struct ufs_sb_private_info*,struct ufs_buffer_head*,unsigned int) ; 
 scalar_t__ ufs_data_ptr_to_cpu (struct super_block*,void*) ; 
 int /*<<< orphan*/  ufs_free_blocks (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_full_branch(struct inode *inode, u64 ind_block, int depth)
{
	struct super_block *sb = inode->i_sb;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	struct ufs_buffer_head *ubh = ubh_bread(sb, ind_block, uspi->s_bsize);
	unsigned i;

	if (!ubh)
		return;

	if (--depth) {
		for (i = 0; i < uspi->s_apb; i++) {
			void *p = ubh_get_data_ptr(uspi, ubh, i);
			u64 block = ufs_data_ptr_to_cpu(sb, p);
			if (block)
				free_full_branch(inode, block, depth);
		}
	} else {
		struct to_free ctx = {.inode = inode};

		for (i = 0; i < uspi->s_apb; i++) {
			void *p = ubh_get_data_ptr(uspi, ubh, i);
			u64 block = ufs_data_ptr_to_cpu(sb, p);
			if (block)
				free_data(&ctx, block, uspi->s_fpb);
		}
		free_data(&ctx, 0, 0);
	}

	ubh_bforget(ubh);
	ufs_free_blocks(inode, ind_block, uspi->s_fpb);
}