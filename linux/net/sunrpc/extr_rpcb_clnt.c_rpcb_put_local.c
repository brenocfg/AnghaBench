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
struct sunrpc_net {scalar_t__ rpcb_users; int /*<<< orphan*/  rpcb_clnt_lock; struct rpc_clnt* rpcb_local_clnt4; struct rpc_clnt* rpcb_local_clnt; } ;
struct rpc_clnt {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

void rpcb_put_local(struct net *net)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	struct rpc_clnt *clnt = sn->rpcb_local_clnt;
	struct rpc_clnt *clnt4 = sn->rpcb_local_clnt4;
	int shutdown = 0;

	spin_lock(&sn->rpcb_clnt_lock);
	if (sn->rpcb_users) {
		if (--sn->rpcb_users == 0) {
			sn->rpcb_local_clnt = NULL;
			sn->rpcb_local_clnt4 = NULL;
		}
		shutdown = !sn->rpcb_users;
	}
	spin_unlock(&sn->rpcb_clnt_lock);

	if (shutdown) {
		/*
		 * cleanup_rpcb_clnt - remove xprtsock's sysctls, unregister
		 */
		if (clnt4)
			rpc_shutdown_client(clnt4);
		if (clnt)
			rpc_shutdown_client(clnt);
	}
}