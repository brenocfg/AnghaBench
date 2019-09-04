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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int dummy; } ;
struct rpc_xprt {int /*<<< orphan*/ * address_strings; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RPCBIND_NETID_RDMA6 ; 
 size_t RPC_DISPLAY_HEX_ADDR ; 
 size_t RPC_DISPLAY_NETID ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xprt_rdma_format_addresses6(struct rpc_xprt *xprt, struct sockaddr *sap)
{
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sap;
	char buf[40];

	snprintf(buf, sizeof(buf), "%pi6", &sin6->sin6_addr);
	xprt->address_strings[RPC_DISPLAY_HEX_ADDR] = kstrdup(buf, GFP_KERNEL);

	xprt->address_strings[RPC_DISPLAY_NETID] = RPCBIND_NETID_RDMA6;
}