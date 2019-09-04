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
struct inode {int /*<<< orphan*/ * i_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  simple_symlink_inode_operations ; 

__attribute__((used)) static inline void set_inode_fast_symlink(struct inode *inode)
{
#ifdef CONFIG_EROFS_FS_XATTR
	inode->i_op = &erofs_fast_symlink_xattr_iops;
#else
	inode->i_op = &simple_symlink_inode_operations;
#endif
}