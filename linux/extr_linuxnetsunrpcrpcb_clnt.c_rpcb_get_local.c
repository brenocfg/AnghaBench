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
struct sunrpc_net {int rpcb_users; int /*<<< orphan*/  rpcb_clnt_lock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static int rpcb_get_local(struct net *net)
{
	int cnt;
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	spin_lock(&sn->rpcb_clnt_lock);
	if (sn->rpcb_users)
		sn->rpcb_users++;
	cnt = sn->rpcb_users;
	spin_unlock(&sn->rpcb_clnt_lock);

	return cnt;
}