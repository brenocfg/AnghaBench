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
typedef  struct rpc_xprt* (* xprt_switch_find_xprt_t ) (struct list_head*,struct rpc_xprt*) ;
struct rpc_xprt {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 struct rpc_xprt* READ_ONCE (struct rpc_xprt*) ; 
 struct rpc_xprt* cmpxchg_relaxed (struct rpc_xprt**,struct rpc_xprt*,struct rpc_xprt*) ; 

__attribute__((used)) static
struct rpc_xprt *xprt_switch_set_next_cursor(struct list_head *head,
		struct rpc_xprt **cursor,
		xprt_switch_find_xprt_t find_next)
{
	struct rpc_xprt *cur, *pos, *old;

	cur = READ_ONCE(*cursor);
	for (;;) {
		old = cur;
		pos = find_next(head, old);
		if (pos == NULL)
			break;
		cur = cmpxchg_relaxed(cursor, old, pos);
		if (cur == old)
			break;
	}
	return pos;
}