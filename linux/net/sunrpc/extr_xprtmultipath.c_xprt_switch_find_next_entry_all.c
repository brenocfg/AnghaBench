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
struct rpc_xprt_switch {int /*<<< orphan*/  xps_xprt_list; } ;
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 struct rpc_xprt* xprt_switch_find_next_entry (int /*<<< orphan*/ *,struct rpc_xprt const*) ; 

__attribute__((used)) static
struct rpc_xprt *xprt_switch_find_next_entry_all(struct rpc_xprt_switch *xps,
		const struct rpc_xprt *cur)
{
	return xprt_switch_find_next_entry(&xps->xps_xprt_list, cur);
}