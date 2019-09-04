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
struct tipc_link {int /*<<< orphan*/  bc_rcvlink; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  buf_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bc_ack_invalid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_build_bc_proto_msg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_xmit (struct tipc_link*,struct sk_buff_head*,struct sk_buff_head*) ; 

__attribute__((used)) static void tipc_link_build_bc_init_msg(struct tipc_link *l,
					struct sk_buff_head *xmitq)
{
	struct sk_buff_head list;

	__skb_queue_head_init(&list);
	if (!tipc_link_build_bc_proto_msg(l->bc_rcvlink, false, 0, &list))
		return;
	msg_set_bc_ack_invalid(buf_msg(skb_peek(&list)), true);
	tipc_link_xmit(l, &list, xmitq);
}