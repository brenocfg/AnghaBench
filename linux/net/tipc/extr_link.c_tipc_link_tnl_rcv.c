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
typedef  int /*<<< orphan*/  u16 ;
struct tipc_msg {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct tipc_link {int /*<<< orphan*/  drop_point; struct sk_buff_head failover_deferdq; struct sk_buff* reasm_tnlmsg; struct sk_buff* failover_reasm_skb; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_FRAGMENT ; 
 int /*<<< orphan*/  FRAGMENT ; 
 int /*<<< orphan*/  LAST_FRAGMENT ; 
 int /*<<< orphan*/  LINK_FAILURE_EVT ; 
 scalar_t__ SYNCH_MSG ; 
 struct sk_buff* __tipc_skb_dequeue (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __tipc_skb_queue_sorted (struct sk_buff_head*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  buf_seqno (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ link_is_bc_rcvlink (struct tipc_link*) ; 
 int msg_fragm_no (struct tipc_msg*) ; 
 int msg_nof_fragms (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,...) ; 
 int /*<<< orphan*/  skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_buf_append (struct sk_buff**,struct sk_buff**) ; 
 int /*<<< orphan*/  tipc_data_input (struct tipc_link*,struct sk_buff*,struct sk_buff_head*) ; 
 int tipc_link_fsm_evt (struct tipc_link*,int /*<<< orphan*/ ) ; 
 int tipc_link_input (struct tipc_link*,struct sk_buff*,struct sk_buff_head*,struct sk_buff**) ; 
 int /*<<< orphan*/  tipc_msg_extract (struct sk_buff*,struct sk_buff**,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tipc_link_tnl_rcv(struct tipc_link *l, struct sk_buff *skb,
			     struct sk_buff_head *inputq)
{
	struct sk_buff **reasm_skb = &l->failover_reasm_skb;
	struct sk_buff **reasm_tnlmsg = &l->reasm_tnlmsg;
	struct sk_buff_head *fdefq = &l->failover_deferdq;
	struct tipc_msg *hdr = buf_msg(skb);
	struct sk_buff *iskb;
	int ipos = 0;
	int rc = 0;
	u16 seqno;

	if (msg_type(hdr) == SYNCH_MSG) {
		kfree_skb(skb);
		return 0;
	}

	/* Not a fragment? */
	if (likely(!msg_nof_fragms(hdr))) {
		if (unlikely(!tipc_msg_extract(skb, &iskb, &ipos))) {
			pr_warn_ratelimited("Unable to extract msg, defq: %d\n",
					    skb_queue_len(fdefq));
			return 0;
		}
		kfree_skb(skb);
	} else {
		/* Set fragment type for buf_append */
		if (msg_fragm_no(hdr) == 1)
			msg_set_type(hdr, FIRST_FRAGMENT);
		else if (msg_fragm_no(hdr) < msg_nof_fragms(hdr))
			msg_set_type(hdr, FRAGMENT);
		else
			msg_set_type(hdr, LAST_FRAGMENT);

		if (!tipc_buf_append(reasm_tnlmsg, &skb)) {
			/* Successful but non-complete reassembly? */
			if (*reasm_tnlmsg || link_is_bc_rcvlink(l))
				return 0;
			pr_warn_ratelimited("Unable to reassemble tunnel msg\n");
			return tipc_link_fsm_evt(l, LINK_FAILURE_EVT);
		}
		iskb = skb;
	}

	do {
		seqno = buf_seqno(iskb);
		if (unlikely(less(seqno, l->drop_point))) {
			kfree_skb(iskb);
			continue;
		}
		if (unlikely(seqno != l->drop_point)) {
			__tipc_skb_queue_sorted(fdefq, seqno, iskb);
			continue;
		}

		l->drop_point++;
		if (!tipc_data_input(l, iskb, inputq))
			rc |= tipc_link_input(l, iskb, inputq, reasm_skb);
		if (unlikely(rc))
			break;
	} while ((iskb = __tipc_skb_dequeue(fdefq, l->drop_point)));

	return rc;
}