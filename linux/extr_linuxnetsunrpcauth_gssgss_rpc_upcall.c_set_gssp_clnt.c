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
struct sunrpc_net {int /*<<< orphan*/  gssp_lock; struct rpc_clnt* gssp_clnt; } ;
struct rpc_clnt {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int gssp_rpc_create (struct net*,struct rpc_clnt**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

int set_gssp_clnt(struct net *net)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	struct rpc_clnt *clnt;
	int ret;

	mutex_lock(&sn->gssp_lock);
	ret = gssp_rpc_create(net, &clnt);
	if (!ret) {
		if (sn->gssp_clnt)
			rpc_shutdown_client(sn->gssp_clnt);
		sn->gssp_clnt = clnt;
	}
	mutex_unlock(&sn->gssp_lock);
	return ret;
}