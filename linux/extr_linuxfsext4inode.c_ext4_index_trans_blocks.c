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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int ext4_ext_index_trans_blocks (struct inode*,int) ; 
 int ext4_ind_trans_blocks (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_index_trans_blocks(struct inode *inode, int lblocks,
				   int pextents)
{
	if (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		return ext4_ind_trans_blocks(inode, lblocks);
	return ext4_ext_index_trans_blocks(inode, pextents);
}