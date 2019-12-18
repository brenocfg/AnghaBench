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
struct TYPE_4__ {int (* create ) (struct inode*,struct dentry*,struct iattr*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 TYPE_2__* NFS_PROTO (struct inode*) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 int stub1 (struct inode*,struct dentry*,struct iattr*,int) ; 
 int /*<<< orphan*/  trace_nfs_create_enter (struct inode*,struct dentry*,int) ; 
 int /*<<< orphan*/  trace_nfs_create_exit (struct inode*,struct dentry*,int,int) ; 

int nfs_create(struct inode *dir, struct dentry *dentry,
		umode_t mode, bool excl)
{
	struct iattr attr;
	int open_flags = excl ? O_CREAT | O_EXCL : O_CREAT;
	int error;

	dfprintk(VFS, "NFS: create(%s/%lu), %pd\n",
			dir->i_sb->s_id, dir->i_ino, dentry);

	attr.ia_mode = mode;
	attr.ia_valid = ATTR_MODE;

	trace_nfs_create_enter(dir, dentry, open_flags);
	error = NFS_PROTO(dir)->create(dir, dentry, &attr, open_flags);
	trace_nfs_create_exit(dir, dentry, open_flags, error);
	if (error != 0)
		goto out_err;
	return 0;
out_err:
	d_drop(dentry);
	return error;
}