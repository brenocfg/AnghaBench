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
struct rpc_task {scalar_t__ tk_status; struct nfs_renamedata* tk_calldata; } ;
struct nfs_renameres {TYPE_2__* old_fattr; int /*<<< orphan*/  old_cinfo; TYPE_1__* new_fattr; int /*<<< orphan*/  new_cinfo; int /*<<< orphan*/  server; int /*<<< orphan*/  seq_res; } ;
struct nfs_renamedata {int /*<<< orphan*/  timeout; struct nfs_renameres res; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  time_start; } ;
struct TYPE_3__ {int /*<<< orphan*/  time_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  NFS_INO_INVALID_OTHER ; 
 int /*<<< orphan*/  nfs4_async_handle_error (struct rpc_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_sequence_done (struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_changeattr (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_proc_rename_done(struct rpc_task *task, struct inode *old_dir,
				 struct inode *new_dir)
{
	struct nfs_renamedata *data = task->tk_calldata;
	struct nfs_renameres *res = &data->res;

	if (!nfs4_sequence_done(task, &res->seq_res))
		return 0;
	if (nfs4_async_handle_error(task, res->server, NULL, &data->timeout) == -EAGAIN)
		return 0;

	if (task->tk_status == 0) {
		if (new_dir != old_dir) {
			/* Note: If we moved a directory, nlink will change */
			update_changeattr(old_dir, &res->old_cinfo,
					res->old_fattr->time_start,
					NFS_INO_INVALID_OTHER);
			update_changeattr(new_dir, &res->new_cinfo,
					res->new_fattr->time_start,
					NFS_INO_INVALID_OTHER);
		} else
			update_changeattr(old_dir, &res->old_cinfo,
					res->old_fattr->time_start,
					0);
	}
	return 1;
}