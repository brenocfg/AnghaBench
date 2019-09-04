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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct iattr {int /*<<< orphan*/  ia_valid; int /*<<< orphan*/  ia_mode; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {int (* mknod ) (struct inode*,struct dentry*,struct iattr*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 TYPE_2__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 int stub1 (struct inode*,struct dentry*,struct iattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_nfs_mknod_enter (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  trace_nfs_mknod_exit (struct inode*,struct dentry*,int) ; 

int
nfs_mknod(struct inode *dir, struct dentry *dentry, umode_t mode, dev_t rdev)
{
	struct iattr attr;
	int status;

	dfprintk(VFS, "NFS: mknod(%s/%lu), %pd\n",
			dir->i_sb->s_id, dir->i_ino, dentry);

	attr.ia_mode = mode;
	attr.ia_valid = ATTR_MODE;

	trace_nfs_mknod_enter(dir, dentry);
	status = NFS_PROTO(dir)->mknod(dir, dentry, &attr, rdev);
	trace_nfs_mknod_exit(dir, dentry, status);
	if (status != 0)
		goto out_err;
	return 0;
out_err:
	d_drop(dentry);
	return status;
}