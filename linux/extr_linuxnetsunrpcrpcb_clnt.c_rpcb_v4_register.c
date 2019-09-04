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
typedef  int /*<<< orphan*/  u32 ;
struct sunrpc_net {int /*<<< orphan*/ * rpcb_local_clnt4; } ;
struct sockaddr {int sa_family; } ;
struct rpcbind_args {char const* r_netid; int /*<<< orphan*/  r_owner; int /*<<< orphan*/  const r_vers; int /*<<< orphan*/  const r_prog; } ;
struct rpc_message {struct rpcbind_args* rpc_argp; } ;
struct net {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAFNOSUPPORT ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  RPCB_OWNER_STRING ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int rpcb_register_inet4 (struct sunrpc_net*,struct sockaddr const*,struct rpc_message*) ; 
 int rpcb_register_inet6 (struct sunrpc_net*,struct sockaddr const*,struct rpc_message*) ; 
 int rpcb_unregister_all_protofamilies (struct sunrpc_net*,struct rpc_message*) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

int rpcb_v4_register(struct net *net, const u32 program, const u32 version,
		     const struct sockaddr *address, const char *netid)
{
	struct rpcbind_args map = {
		.r_prog		= program,
		.r_vers		= version,
		.r_netid	= netid,
		.r_owner	= RPCB_OWNER_STRING,
	};
	struct rpc_message msg = {
		.rpc_argp	= &map,
	};
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	if (sn->rpcb_local_clnt4 == NULL)
		return -EPROTONOSUPPORT;

	if (address == NULL)
		return rpcb_unregister_all_protofamilies(sn, &msg);

	switch (address->sa_family) {
	case AF_INET:
		return rpcb_register_inet4(sn, address, &msg);
	case AF_INET6:
		return rpcb_register_inet6(sn, address, &msg);
	}

	return -EAFNOSUPPORT;
}