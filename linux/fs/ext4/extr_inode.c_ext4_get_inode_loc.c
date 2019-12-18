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
struct ext4_iloc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_STATE_XATTR ; 
 int __ext4_get_inode_loc (struct inode*,struct ext4_iloc*,int) ; 
 int /*<<< orphan*/  ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 

int ext4_get_inode_loc(struct inode *inode, struct ext4_iloc *iloc)
{
	/* We have all inode data except xattrs in memory here. */
	return __ext4_get_inode_loc(inode, iloc,
		!ext4_test_inode_state(inode, EXT4_STATE_XATTR));
}