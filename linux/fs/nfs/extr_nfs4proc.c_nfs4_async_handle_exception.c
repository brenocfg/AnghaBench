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
struct rpc_task {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  mig_status; struct nfs_client* nfs_client; } ;
struct nfs_client {int /*<<< orphan*/  cl_rpcwaitq; int /*<<< orphan*/  cl_state; } ;
struct nfs4_exception {int retry; scalar_t__ recovering; int /*<<< orphan*/  timeout; scalar_t__ delay; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NFS4CLNT_MANAGER_RUNNING ; 
 int NFS4ERR_MOVED ; 
 int /*<<< orphan*/  NFS_MIG_FAILED ; 
 int nfs4_do_handle_exception (struct nfs_server*,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  nfs4_update_delay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_delay (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_task_release_transport (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task (int /*<<< orphan*/ *,struct rpc_task*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs4_async_handle_exception(struct rpc_task *task, struct nfs_server *server,
		int errorcode, struct nfs4_exception *exception)
{
	struct nfs_client *clp = server->nfs_client;
	int ret;

	ret = nfs4_do_handle_exception(server, errorcode, exception);
	if (exception->delay) {
		rpc_delay(task, nfs4_update_delay(&exception->timeout));
		goto out_retry;
	}
	if (exception->recovering) {
		rpc_sleep_on(&clp->cl_rpcwaitq, task, NULL);
		if (test_bit(NFS4CLNT_MANAGER_RUNNING, &clp->cl_state) == 0)
			rpc_wake_up_queued_task(&clp->cl_rpcwaitq, task);
		goto out_retry;
	}
	if (test_bit(NFS_MIG_FAILED, &server->mig_status))
		ret = -EIO;
	return ret;
out_retry:
	if (ret == 0) {
		exception->retry = 1;
		/*
		 * For NFS4ERR_MOVED, the client transport will need to
		 * be recomputed after migration recovery has completed.
		 */
		if (errorcode == -NFS4ERR_MOVED)
			rpc_task_release_transport(task);
	}
	return ret;
}