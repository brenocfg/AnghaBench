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
struct rpc_xprt_switch {int dummy; } ;
struct rpc_xprt_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xprt_iter_init (struct rpc_xprt_iter*,struct rpc_xprt_switch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_xprt_iter_listall ; 

void xprt_iter_init_listall(struct rpc_xprt_iter *xpi,
		struct rpc_xprt_switch *xps)
{
	__xprt_iter_init(xpi, xps, &rpc_xprt_iter_listall);
}