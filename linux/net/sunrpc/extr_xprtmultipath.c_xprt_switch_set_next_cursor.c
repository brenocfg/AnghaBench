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
typedef  struct rpc_xprt* (* xprt_switch_find_xprt_t ) (struct rpc_xprt_switch*,struct rpc_xprt*) ;
struct rpc_xprt_switch {int dummy; } ;
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 struct rpc_xprt* smp_load_acquire (struct rpc_xprt**) ; 
 int /*<<< orphan*/  smp_store_release (struct rpc_xprt**,struct rpc_xprt*) ; 

__attribute__((used)) static
struct rpc_xprt *xprt_switch_set_next_cursor(struct rpc_xprt_switch *xps,
		struct rpc_xprt **cursor,
		xprt_switch_find_xprt_t find_next)
{
	struct rpc_xprt *pos, *old;

	old = smp_load_acquire(cursor);
	pos = find_next(xps, old);
	smp_store_release(cursor, pos);
	return pos;
}