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
struct rpc_xprt_iter {int dummy; } ;
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 struct rpc_xprt* xprt_iter_next_entry_multiple (struct rpc_xprt_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_switch_find_next_entry_all ; 

__attribute__((used)) static
struct rpc_xprt *xprt_iter_next_entry_all(struct rpc_xprt_iter *xpi)
{
	return xprt_iter_next_entry_multiple(xpi,
			xprt_switch_find_next_entry_all);
}