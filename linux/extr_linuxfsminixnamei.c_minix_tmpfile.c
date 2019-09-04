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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_tmpfile (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct inode* minix_new_inode (struct inode*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  minix_set_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int minix_tmpfile(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	int error;
	struct inode *inode = minix_new_inode(dir, mode, &error);
	if (inode) {
		minix_set_inode(inode, 0);
		mark_inode_dirty(inode);
		d_tmpfile(dentry, inode);
	}
	return error;
}