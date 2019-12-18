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
struct sunrpc_net {int /*<<< orphan*/ * proc_net_rpc; } ;
struct net {int /*<<< orphan*/  proc_net; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

int rpc_proc_init(struct net *net)
{
	struct sunrpc_net *sn;

	dprintk("RPC:       registering /proc/net/rpc\n");
	sn = net_generic(net, sunrpc_net_id);
	sn->proc_net_rpc = proc_mkdir("rpc", net->proc_net);
	if (sn->proc_net_rpc == NULL)
		return -ENOMEM;

	return 0;
}