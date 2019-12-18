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
struct nfs_server {int dummy; } ;
struct nfs4_state {int dummy; } ;
struct nfs4_exception {long timeout; scalar_t__ retry; scalar_t__ delay; struct nfs4_state* state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  nfs4_async_handle_exception (struct rpc_task*,struct nfs_server*,int /*<<< orphan*/ ,struct nfs4_exception*) ; 

int
nfs4_async_handle_error(struct rpc_task *task, struct nfs_server *server,
			struct nfs4_state *state, long *timeout)
{
	struct nfs4_exception exception = {
		.state = state,
	};

	if (task->tk_status >= 0)
		return 0;
	if (timeout)
		exception.timeout = *timeout;
	task->tk_status = nfs4_async_handle_exception(task, server,
			task->tk_status,
			&exception);
	if (exception.delay && timeout)
		*timeout = exception.timeout;
	if (exception.retry)
		return -EAGAIN;
	return 0;
}