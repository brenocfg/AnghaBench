#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const** address_strings; } ;
struct rpcrdma_xprt {TYPE_1__ rx_xprt; } ;

/* Variables and functions */
 size_t RPC_DISPLAY_PORT ; 

__attribute__((used)) static inline const char *
rpcrdma_portstr(const struct rpcrdma_xprt *r_xprt)
{
	return r_xprt->rx_xprt.address_strings[RPC_DISPLAY_PORT];
}