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
struct rpc_task {int dummy; } ;
struct nfs_commit_data {int /*<<< orphan*/  inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* commit_rpc_prepare ) (struct rpc_task*,struct nfs_commit_data*) ;} ;

/* Variables and functions */
 TYPE_1__* NFS_PROTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*,struct nfs_commit_data*) ; 

void nfs_commit_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs_commit_data *data = calldata;

	NFS_PROTO(data->inode)->commit_rpc_prepare(task, data);
}