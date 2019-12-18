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
struct rpc_clnt {int /*<<< orphan*/  cl_cred; int /*<<< orphan*/  cl_xpi; int /*<<< orphan*/  cl_xprt; int /*<<< orphan*/ * cl_metrics; struct rpc_clnt* cl_parent; TYPE_1__* cl_program; } ;
struct TYPE_4__ {int /*<<< orphan*/  servername; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk_rcu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rpc_clnt*) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 TYPE_2__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_clnt_debugfs_unregister (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_clnt_remove_pipedir (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_free_clid (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_free_iostats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_unregister_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpciod_down () ; 
 int /*<<< orphan*/  xprt_iter_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpc_clnt *
rpc_free_client(struct rpc_clnt *clnt)
{
	struct rpc_clnt *parent = NULL;

	dprintk_rcu("RPC:       destroying %s client for %s\n",
			clnt->cl_program->name,
			rcu_dereference(clnt->cl_xprt)->servername);
	if (clnt->cl_parent != clnt)
		parent = clnt->cl_parent;
	rpc_clnt_debugfs_unregister(clnt);
	rpc_clnt_remove_pipedir(clnt);
	rpc_unregister_client(clnt);
	rpc_free_iostats(clnt->cl_metrics);
	clnt->cl_metrics = NULL;
	xprt_put(rcu_dereference_raw(clnt->cl_xprt));
	xprt_iter_destroy(&clnt->cl_xpi);
	rpciod_down();
	put_cred(clnt->cl_cred);
	rpc_free_clid(clnt);
	kfree(clnt);
	return parent;
}