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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
typedef  scalar_t__ ext4_lblk_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int ext4_data_block_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_pblock (struct ext4_extent*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_valid_extent(struct inode *inode, struct ext4_extent *ext)
{
	ext4_fsblk_t block = ext4_ext_pblock(ext);
	int len = ext4_ext_get_actual_len(ext);
	ext4_lblk_t lblock = le32_to_cpu(ext->ee_block);

	/*
	 * We allow neither:
	 *  - zero length
	 *  - overflow/wrap-around
	 */
	if (lblock + len <= lblock)
		return 0;
	return ext4_data_block_valid(EXT4_SB(inode->i_sb), block, len);
}