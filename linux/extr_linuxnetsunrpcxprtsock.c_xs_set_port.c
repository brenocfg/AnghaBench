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
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct rpc_xprt*,unsigned short) ; 
 int /*<<< orphan*/  rpc_set_port (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  xs_addr (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xs_update_peer_port (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_set_port(struct rpc_xprt *xprt, unsigned short port)
{
	dprintk("RPC:       setting port for xprt %p to %u\n", xprt, port);

	rpc_set_port(xs_addr(xprt), port);
	xs_update_peer_port(xprt);
}