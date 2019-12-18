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
typedef  void* u32 ;
struct tipc_link {TYPE_1__* bc_rcvlink; void* tolerance; } ;
struct sk_buff_head {int dummy; } ;
struct TYPE_2__ {void* tolerance; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_MSG ; 
 scalar_t__ link_is_up (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_build_proto_msg (struct tipc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct sk_buff_head*) ; 

void tipc_link_set_tolerance(struct tipc_link *l, u32 tol,
			     struct sk_buff_head *xmitq)
{
	l->tolerance = tol;
	if (l->bc_rcvlink)
		l->bc_rcvlink->tolerance = tol;
	if (link_is_up(l))
		tipc_link_build_proto_msg(l, STATE_MSG, 0, 0, 0, tol, 0, xmitq);
}