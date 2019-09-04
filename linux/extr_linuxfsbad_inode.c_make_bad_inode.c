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
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_opflags; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP_XATTR ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  bad_file_ops ; 
 int /*<<< orphan*/  bad_inode_ops ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  remove_inode_hash (struct inode*) ; 

void make_bad_inode(struct inode *inode)
{
	remove_inode_hash(inode);

	inode->i_mode = S_IFREG;
	inode->i_atime = inode->i_mtime = inode->i_ctime =
		current_time(inode);
	inode->i_op = &bad_inode_ops;	
	inode->i_opflags &= ~IOP_XATTR;
	inode->i_fop = &bad_file_ops;	
}