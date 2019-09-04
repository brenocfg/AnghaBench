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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_link {int /*<<< orphan*/  priority; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_MSG ; 
 int /*<<< orphan*/  tipc_link_build_proto_msg (struct tipc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff_head*) ; 

void tipc_link_set_prio(struct tipc_link *l, u32 prio,
			struct sk_buff_head *xmitq)
{
	l->priority = prio;
	tipc_link_build_proto_msg(l, STATE_MSG, 0, 0, 0, 0, prio, xmitq);
}