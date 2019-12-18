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
struct sockaddr {int sa_family; } ;
struct rpc_xprt {char** address_strings; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t RPC_DISPLAY_ADDR ; 
 size_t RPC_DISPLAY_HEX_PORT ; 
 size_t RPC_DISPLAY_PORT ; 
 size_t RPC_DISPLAY_PROTO ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int rpc_get_port (struct sockaddr*) ; 
 int /*<<< orphan*/  rpc_ntop (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  xprt_rdma_format_addresses4 (struct rpc_xprt*,struct sockaddr*) ; 
 int /*<<< orphan*/  xprt_rdma_format_addresses6 (struct rpc_xprt*,struct sockaddr*) ; 

void
xprt_rdma_format_addresses(struct rpc_xprt *xprt, struct sockaddr *sap)
{
	char buf[128];

	switch (sap->sa_family) {
	case AF_INET:
		xprt_rdma_format_addresses4(xprt, sap);
		break;
	case AF_INET6:
		xprt_rdma_format_addresses6(xprt, sap);
		break;
	default:
		pr_err("rpcrdma: Unrecognized address family\n");
		return;
	}

	(void)rpc_ntop(sap, buf, sizeof(buf));
	xprt->address_strings[RPC_DISPLAY_ADDR] = kstrdup(buf, GFP_KERNEL);

	snprintf(buf, sizeof(buf), "%u", rpc_get_port(sap));
	xprt->address_strings[RPC_DISPLAY_PORT] = kstrdup(buf, GFP_KERNEL);

	snprintf(buf, sizeof(buf), "%4hx", rpc_get_port(sap));
	xprt->address_strings[RPC_DISPLAY_HEX_PORT] = kstrdup(buf, GFP_KERNEL);

	xprt->address_strings[RPC_DISPLAY_PROTO] = "rdma";
}