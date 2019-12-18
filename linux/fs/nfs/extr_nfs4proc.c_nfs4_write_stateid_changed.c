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
struct rpc_task {int /*<<< orphan*/  tk_status; } ;
struct nfs_pgio_args {int /*<<< orphan*/  lock_context; int /*<<< orphan*/  context; int /*<<< orphan*/  stateid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  nfs4_error_stateid_expired (int /*<<< orphan*/ ) ; 
 scalar_t__ nfs4_stateid_is_current (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 

__attribute__((used)) static bool nfs4_write_stateid_changed(struct rpc_task *task,
		struct nfs_pgio_args *args)
{

	if (!nfs4_error_stateid_expired(task->tk_status) ||
		nfs4_stateid_is_current(&args->stateid,
				args->context,
				args->lock_context,
				FMODE_WRITE))
		return false;
	rpc_restart_call_prepare(task);
	return true;
}