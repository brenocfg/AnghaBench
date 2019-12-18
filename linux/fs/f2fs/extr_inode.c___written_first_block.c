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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_inode {int /*<<< orphan*/ * i_addr; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_GENERIC_ENHANCE ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  __is_valid_data_blkaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 size_t offset_in_addr (struct f2fs_inode*) ; 

__attribute__((used)) static int __written_first_block(struct f2fs_sb_info *sbi,
					struct f2fs_inode *ri)
{
	block_t addr = le32_to_cpu(ri->i_addr[offset_in_addr(ri)]);

	if (!__is_valid_data_blkaddr(addr))
		return 1;
	if (!f2fs_is_valid_blkaddr(sbi, addr, DATA_GENERIC_ENHANCE))
		return -EFSCORRUPTED;
	return 0;
}