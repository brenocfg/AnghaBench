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
struct rpc_xprt {int /*<<< orphan*/ * address_strings; } ;

/* Variables and functions */
 unsigned int RPC_DISPLAY_MAX ; 
#define  RPC_DISPLAY_NETID 129 
#define  RPC_DISPLAY_PROTO 128 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void
xprt_rdma_free_addresses(struct rpc_xprt *xprt)
{
	unsigned int i;

	for (i = 0; i < RPC_DISPLAY_MAX; i++)
		switch (i) {
		case RPC_DISPLAY_PROTO:
		case RPC_DISPLAY_NETID:
			continue;
		default:
			kfree(xprt->address_strings[i]);
		}
}