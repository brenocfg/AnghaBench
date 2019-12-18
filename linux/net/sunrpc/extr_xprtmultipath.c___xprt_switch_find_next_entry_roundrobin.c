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
struct list_head {int dummy; } ;

/* Variables and functions */
 struct rpc_xprt* xprt_switch_find_first_entry (struct list_head*) ; 
 struct rpc_xprt* xprt_switch_find_next_entry (struct list_head*,struct rpc_xprt const*) ; 

__attribute__((used)) static
struct rpc_xprt *__xprt_switch_find_next_entry_roundrobin(struct list_head *head,
		const struct rpc_xprt *cur)
{
	struct rpc_xprt *ret;

	ret = xprt_switch_find_next_entry(head, cur);
	if (ret != NULL)
		return ret;
	return xprt_switch_find_first_entry(head);
}