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
struct rpc_task {scalar_t__ tk_status; } ;
struct nfs_renamedata {struct dentry* old_dentry; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_cancel_async_unlink (struct dentry*) ; 

__attribute__((used)) static void
nfs_complete_sillyrename(struct rpc_task *task, struct nfs_renamedata *data)
{
	struct dentry *dentry = data->old_dentry;

	if (task->tk_status != 0) {
		nfs_cancel_async_unlink(dentry);
		return;
	}
}