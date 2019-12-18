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
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;
struct inode {TYPE_1__ i_data; int /*<<< orphan*/ * i_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_symlink_aops ; 
 int /*<<< orphan*/  fuse_symlink_inode_operations ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 

void fuse_init_symlink(struct inode *inode)
{
	inode->i_op = &fuse_symlink_inode_operations;
	inode->i_data.a_ops = &fuse_symlink_aops;
	inode_nohighmem(inode);
}