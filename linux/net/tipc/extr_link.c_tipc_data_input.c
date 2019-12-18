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
struct tipc_msg {int dummy; } ;
struct tipc_link {struct sk_buff_head* namedq; TYPE_1__* bc_rcvlink; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; struct sk_buff_head* inputq; } ;

/* Variables and functions */
#define  BCAST_PROTOCOL 138 
#define  CONN_MANAGER 137 
#define  GROUP_PROTOCOL 136 
 int /*<<< orphan*/  LINK_ESTABLISHED ; 
#define  MSG_BUNDLER 135 
#define  MSG_FRAGMENTER 134 
#define  NAME_DISTRIBUTOR 133 
#define  TIPC_CRITICAL_IMPORTANCE 132 
#define  TIPC_HIGH_IMPORTANCE 131 
#define  TIPC_LOW_IMPORTANCE 130 
#define  TIPC_MEDIUM_IMPORTANCE 129 
#define  TUNNEL_PROTOCOL 128 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_in_group (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_mcast (struct tipc_msg*) ; 
 int msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static bool tipc_data_input(struct tipc_link *l, struct sk_buff *skb,
			    struct sk_buff_head *inputq)
{
	struct sk_buff_head *mc_inputq = l->bc_rcvlink->inputq;
	struct tipc_msg *hdr = buf_msg(skb);

	switch (msg_user(hdr)) {
	case TIPC_LOW_IMPORTANCE:
	case TIPC_MEDIUM_IMPORTANCE:
	case TIPC_HIGH_IMPORTANCE:
	case TIPC_CRITICAL_IMPORTANCE:
		if (unlikely(msg_in_group(hdr) || msg_mcast(hdr))) {
			skb_queue_tail(mc_inputq, skb);
			return true;
		}
		/* fall through */
	case CONN_MANAGER:
		skb_queue_tail(inputq, skb);
		return true;
	case GROUP_PROTOCOL:
		skb_queue_tail(mc_inputq, skb);
		return true;
	case NAME_DISTRIBUTOR:
		l->bc_rcvlink->state = LINK_ESTABLISHED;
		skb_queue_tail(l->namedq, skb);
		return true;
	case MSG_BUNDLER:
	case TUNNEL_PROTOCOL:
	case MSG_FRAGMENTER:
	case BCAST_PROTOCOL:
		return false;
	default:
		pr_warn("Dropping received illegal msg type\n");
		kfree_skb(skb);
		return true;
	};
}