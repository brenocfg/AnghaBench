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
struct sunrpc_net {int /*<<< orphan*/  rpcb_local_clnt4; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr {int dummy; } ;
struct rpcbind_args {int /*<<< orphan*/  r_addr; int /*<<< orphan*/  r_netid; int /*<<< orphan*/  r_vers; int /*<<< orphan*/  r_prog; } ;
struct rpc_message {int /*<<< orphan*/ * rpc_proc; struct rpcbind_args* rpc_argp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t RPCBPROC_SET ; 
 size_t RPCBPROC_UNSET ; 
 int /*<<< orphan*/  dprintk (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_sockaddr2uaddr (struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rpcb_procedures4 ; 
 int rpcb_register_call (struct sunrpc_net*,int /*<<< orphan*/ ,struct rpc_message*,int) ; 

__attribute__((used)) static int rpcb_register_inet6(struct sunrpc_net *sn,
			       const struct sockaddr *sap,
			       struct rpc_message *msg)
{
	const struct sockaddr_in6 *sin6 = (const struct sockaddr_in6 *)sap;
	struct rpcbind_args *map = msg->rpc_argp;
	unsigned short port = ntohs(sin6->sin6_port);
	bool is_set = false;
	int result;

	map->r_addr = rpc_sockaddr2uaddr(sap, GFP_KERNEL);

	dprintk("RPC:       %sregistering [%u, %u, %s, '%s'] with "
		"local rpcbind\n", (port ? "" : "un"),
			map->r_prog, map->r_vers,
			map->r_addr, map->r_netid);

	msg->rpc_proc = &rpcb_procedures4[RPCBPROC_UNSET];
	if (port != 0) {
		msg->rpc_proc = &rpcb_procedures4[RPCBPROC_SET];
		is_set = true;
	}

	result = rpcb_register_call(sn, sn->rpcb_local_clnt4, msg, is_set);
	kfree(map->r_addr);
	return result;
}