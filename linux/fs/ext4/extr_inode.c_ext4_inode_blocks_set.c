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
typedef  unsigned int u64 ;
struct super_block {int dummy; } ;
struct inode {unsigned int i_blocks; int i_blkbits; struct super_block* i_sb; } ;
struct ext4_inode_info {struct inode vfs_inode; } ;
struct ext4_inode {void* i_blocks_high; void* i_blocks_lo; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EFBIG ; 
 int /*<<< orphan*/  EXT4_INODE_HUGE_FILE ; 
 void* cpu_to_le16 (unsigned int) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  ext4_clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_has_feature_huge_file (struct super_block*) ; 
 int /*<<< orphan*/  ext4_set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_inode_blocks_set(handle_t *handle,
				struct ext4_inode *raw_inode,
				struct ext4_inode_info *ei)
{
	struct inode *inode = &(ei->vfs_inode);
	u64 i_blocks = inode->i_blocks;
	struct super_block *sb = inode->i_sb;

	if (i_blocks <= ~0U) {
		/*
		 * i_blocks can be represented in a 32 bit variable
		 * as multiple of 512 bytes
		 */
		raw_inode->i_blocks_lo   = cpu_to_le32(i_blocks);
		raw_inode->i_blocks_high = 0;
		ext4_clear_inode_flag(inode, EXT4_INODE_HUGE_FILE);
		return 0;
	}
	if (!ext4_has_feature_huge_file(sb))
		return -EFBIG;

	if (i_blocks <= 0xffffffffffffULL) {
		/*
		 * i_blocks can be represented in a 48 bit variable
		 * as multiple of 512 bytes
		 */
		raw_inode->i_blocks_lo   = cpu_to_le32(i_blocks);
		raw_inode->i_blocks_high = cpu_to_le16(i_blocks >> 32);
		ext4_clear_inode_flag(inode, EXT4_INODE_HUGE_FILE);
	} else {
		ext4_set_inode_flag(inode, EXT4_INODE_HUGE_FILE);
		/* i_block is stored in file system block size */
		i_blocks = i_blocks >> (inode->i_blkbits - 9);
		raw_inode->i_blocks_lo   = cpu_to_le32(i_blocks);
		raw_inode->i_blocks_high = cpu_to_le16(i_blocks >> 32);
	}
	return 0;
}