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
struct rpc_clnt {int /*<<< orphan*/  cl_tasks; int /*<<< orphan*/  cl_xprt; TYPE_1__* cl_program; } ;
struct TYPE_4__ {int /*<<< orphan*/  servername; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  destroy_wait ; 
 int /*<<< orphan*/  dprintk_rcu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 TYPE_2__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_killall_tasks (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_release_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void rpc_shutdown_client(struct rpc_clnt *clnt)
{
	might_sleep();

	dprintk_rcu("RPC:       shutting down %s client for %s\n",
			clnt->cl_program->name,
			rcu_dereference(clnt->cl_xprt)->servername);

	while (!list_empty(&clnt->cl_tasks)) {
		rpc_killall_tasks(clnt);
		wait_event_timeout(destroy_wait,
			list_empty(&clnt->cl_tasks), 1*HZ);
	}

	rpc_release_client(clnt);
}