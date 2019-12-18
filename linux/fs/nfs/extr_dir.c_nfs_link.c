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
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {int (* link ) (struct inode*,struct inode*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int stub1 (struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs_link_enter (struct inode*,struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  trace_nfs_link_exit (struct inode*,struct inode*,struct dentry*,int) ; 

int
nfs_link(struct dentry *old_dentry, struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = d_inode(old_dentry);
	int error;

	dfprintk(VFS, "NFS: link(%pd2 -> %pd2)\n",
		old_dentry, dentry);

	trace_nfs_link_enter(inode, dir, dentry);
	d_drop(dentry);
	error = NFS_PROTO(dir)->link(inode, dir, &dentry->d_name);
	if (error == 0) {
		ihold(inode);
		d_add(dentry, inode);
	}
	trace_nfs_link_exit(inode, dir, dentry, error);
	return error;
}