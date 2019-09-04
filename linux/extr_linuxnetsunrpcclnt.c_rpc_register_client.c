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
struct sunrpc_net {int /*<<< orphan*/  rpc_client_lock; int /*<<< orphan*/  all_clients; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_clients; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct net* rpc_net_ns (struct rpc_clnt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static void rpc_register_client(struct rpc_clnt *clnt)
{
	struct net *net = rpc_net_ns(clnt);
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	spin_lock(&sn->rpc_client_lock);
	list_add(&clnt->cl_clients, &sn->all_clients);
	spin_unlock(&sn->rpc_client_lock);
}