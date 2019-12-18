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
struct TYPE_2__ {int /*<<< orphan*/  recv_fragmented; int /*<<< orphan*/  recv_fragments; int /*<<< orphan*/  recv_bundled; int /*<<< orphan*/  recv_bundles; } ;
struct tipc_link {int /*<<< orphan*/  net; int /*<<< orphan*/  bc_rcvlink; TYPE_1__ stats; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int BCAST_PROTOCOL ; 
 int /*<<< orphan*/  LINK_FAILURE_EVT ; 
 int MSG_BUNDLER ; 
 int MSG_FRAGMENTER ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  link_is_bc_rcvlink (struct tipc_link*) ; 
 scalar_t__ msg_msgcnt (struct tipc_msg*) ; 
 int msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ tipc_buf_append (struct sk_buff**,struct sk_buff**) ; 
 int /*<<< orphan*/  tipc_data_input (struct tipc_link*,struct sk_buff*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_bc_init_rcv (int /*<<< orphan*/ ,struct tipc_msg*) ; 
 int tipc_link_fsm_evt (struct tipc_link*,int /*<<< orphan*/ ) ; 
 scalar_t__ tipc_msg_extract (struct sk_buff*,struct sk_buff**,int*) ; 
 int /*<<< orphan*/  tipc_skb_queue_splice_tail (struct sk_buff_head*,struct sk_buff_head*) ; 

__attribute__((used)) static int tipc_link_input(struct tipc_link *l, struct sk_buff *skb,
			   struct sk_buff_head *inputq,
			   struct sk_buff **reasm_skb)
{
	struct tipc_msg *hdr = buf_msg(skb);
	struct sk_buff *iskb;
	struct sk_buff_head tmpq;
	int usr = msg_user(hdr);
	int pos = 0;

	if (usr == MSG_BUNDLER) {
		skb_queue_head_init(&tmpq);
		l->stats.recv_bundles++;
		l->stats.recv_bundled += msg_msgcnt(hdr);
		while (tipc_msg_extract(skb, &iskb, &pos))
			tipc_data_input(l, iskb, &tmpq);
		tipc_skb_queue_splice_tail(&tmpq, inputq);
		return 0;
	} else if (usr == MSG_FRAGMENTER) {
		l->stats.recv_fragments++;
		if (tipc_buf_append(reasm_skb, &skb)) {
			l->stats.recv_fragmented++;
			tipc_data_input(l, skb, inputq);
		} else if (!*reasm_skb && !link_is_bc_rcvlink(l)) {
			pr_warn_ratelimited("Unable to build fragment list\n");
			return tipc_link_fsm_evt(l, LINK_FAILURE_EVT);
		}
		return 0;
	} else if (usr == BCAST_PROTOCOL) {
		tipc_bcast_lock(l->net);
		tipc_link_bc_init_rcv(l->bc_rcvlink, hdr);
		tipc_bcast_unlock(l->net);
	}

	kfree_skb(skb);
	return 0;
}