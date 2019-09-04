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
typedef  int umode_t ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct iattr {int ia_mode; int /*<<< orphan*/  ia_valid; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {int (* mkdir ) (struct inode*,struct dentry*,struct iattr*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 TYPE_2__* NFS_PROTO (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 int stub1 (struct inode*,struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  trace_nfs_mkdir_enter (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  trace_nfs_mkdir_exit (struct inode*,struct dentry*,int) ; 

int nfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct iattr attr;
	int error;

	dfprintk(VFS, "NFS: mkdir(%s/%lu), %pd\n",
			dir->i_sb->s_id, dir->i_ino, dentry);

	attr.ia_valid = ATTR_MODE;
	attr.ia_mode = mode | S_IFDIR;

	trace_nfs_mkdir_enter(dir, dentry);
	error = NFS_PROTO(dir)->mkdir(dir, dentry, &attr);
	trace_nfs_mkdir_exit(dir, dentry, error);
	if (error != 0)
		goto out_err;
	return 0;
out_err:
	d_drop(dentry);
	return error;
}