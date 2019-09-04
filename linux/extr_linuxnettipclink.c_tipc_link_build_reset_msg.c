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
struct tipc_link {scalar_t__ state; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int ACTIVATE_MSG ; 
 scalar_t__ LINK_ESTABLISHING ; 
 scalar_t__ LINK_RESET ; 
 int RESET_MSG ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_set_peer_stopping (int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_peek_tail (struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_build_proto_msg (struct tipc_link*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff_head*) ; 

void tipc_link_build_reset_msg(struct tipc_link *l, struct sk_buff_head *xmitq)
{
	int mtyp = RESET_MSG;
	struct sk_buff *skb;

	if (l->state == LINK_ESTABLISHING)
		mtyp = ACTIVATE_MSG;

	tipc_link_build_proto_msg(l, mtyp, 0, 0, 0, 0, 0, xmitq);

	/* Inform peer that this endpoint is going down if applicable */
	skb = skb_peek_tail(xmitq);
	if (skb && (l->state == LINK_RESET))
		msg_set_peer_stopping(buf_msg(skb), 1);
}