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
struct rpc_xprt {char const** address_strings; } ;

/* Variables and functions */
 size_t RPC_DISPLAY_NETID ; 
 size_t RPC_DISPLAY_PROTO ; 
 int /*<<< orphan*/  xs_format_common_peer_addresses (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xs_format_common_peer_ports (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_format_peer_addresses(struct rpc_xprt *xprt,
				     const char *protocol,
				     const char *netid)
{
	xprt->address_strings[RPC_DISPLAY_PROTO] = protocol;
	xprt->address_strings[RPC_DISPLAY_NETID] = netid;
	xs_format_common_peer_addresses(xprt);
	xs_format_common_peer_ports(xprt);
}