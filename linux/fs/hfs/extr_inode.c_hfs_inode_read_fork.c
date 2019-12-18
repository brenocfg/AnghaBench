#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct inode {int i_size; struct super_block* i_sb; } ;
struct hfs_extent {int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  hfs_extent_rec ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int phys_size; int fs_blocks; int alloc_blocks; int clump_blocks; scalar_t__ first_blocks; int /*<<< orphan*/  first_extents; } ;
struct TYPE_3__ {int alloc_blksz; int clumpablks; } ;

/* Variables and functions */
 TYPE_2__* HFS_I (struct inode*) ; 
 TYPE_1__* HFS_SB (struct super_block*) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_set_bytes (struct inode*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct hfs_extent*,int) ; 

void hfs_inode_read_fork(struct inode *inode, struct hfs_extent *ext,
			 __be32 __log_size, __be32 phys_size, u32 clump_size)
{
	struct super_block *sb = inode->i_sb;
	u32 log_size = be32_to_cpu(__log_size);
	u16 count;
	int i;

	memcpy(HFS_I(inode)->first_extents, ext, sizeof(hfs_extent_rec));
	for (count = 0, i = 0; i < 3; i++)
		count += be16_to_cpu(ext[i].count);
	HFS_I(inode)->first_blocks = count;

	inode->i_size = HFS_I(inode)->phys_size = log_size;
	HFS_I(inode)->fs_blocks = (log_size + sb->s_blocksize - 1) >> sb->s_blocksize_bits;
	inode_set_bytes(inode, HFS_I(inode)->fs_blocks << sb->s_blocksize_bits);
	HFS_I(inode)->alloc_blocks = be32_to_cpu(phys_size) /
				     HFS_SB(sb)->alloc_blksz;
	HFS_I(inode)->clump_blocks = clump_size / HFS_SB(sb)->alloc_blksz;
	if (!HFS_I(inode)->clump_blocks)
		HFS_I(inode)->clump_blocks = HFS_SB(sb)->clumpablks;
}