#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  label; TYPE_3__* fattr; int /*<<< orphan*/  fh; int /*<<< orphan*/  dir_cinfo; int /*<<< orphan*/  seq_res; } ;
struct TYPE_6__ {scalar_t__ ftype; int /*<<< orphan*/  seq_args; } ;
struct nfs4_createdata {TYPE_2__ res; TYPE_1__ arg; int /*<<< orphan*/  msg; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct dentry {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  client; } ;
struct TYPE_8__ {int /*<<< orphan*/  time_start; } ;

/* Variables and functions */
 scalar_t__ NF4DIR ; 
 TYPE_4__* NFS_SERVER (struct inode*) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs4_inc_nlink_locked (struct inode*) ; 
 int nfs_instantiate (struct dentry*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_changeattr_locked (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_do_create(struct inode *dir, struct dentry *dentry, struct nfs4_createdata *data)
{
	int status = nfs4_call_sync(NFS_SERVER(dir)->client, NFS_SERVER(dir), &data->msg,
				    &data->arg.seq_args, &data->res.seq_res, 1);
	if (status == 0) {
		spin_lock(&dir->i_lock);
		update_changeattr_locked(dir, &data->res.dir_cinfo,
				data->res.fattr->time_start, 0);
		/* Creating a directory bumps nlink in the parent */
		if (data->arg.ftype == NF4DIR)
			nfs4_inc_nlink_locked(dir);
		spin_unlock(&dir->i_lock);
		status = nfs_instantiate(dentry, data->res.fh, data->res.fattr, data->res.label);
	}
	return status;
}