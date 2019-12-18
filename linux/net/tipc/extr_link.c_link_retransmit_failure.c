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
struct tipc_link {int /*<<< orphan*/  state; int /*<<< orphan*/  transmq; int /*<<< orphan*/  name; int /*<<< orphan*/  acked; int /*<<< orphan*/  tolerance; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  retr_cnt; scalar_t__ retr_stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_FAILURE_EVT ; 
 int /*<<< orphan*/  LINK_RESET ; 
 int /*<<< orphan*/  TIPC_DUMP_NONE ; 
 int TIPC_LINK_DOWN_EVT ; 
 TYPE_1__* TIPC_SKB_CB (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ link_is_bc_sndlink (struct tipc_link*) ; 
 int /*<<< orphan*/  link_print (struct tipc_link*,char*) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_destnode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_errcode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_prevnode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_seqno (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_size (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_type (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int tipc_link_fsm_evt (struct tipc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tipc_link_dump (struct tipc_link*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace_tipc_list_dump (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static bool link_retransmit_failure(struct tipc_link *l, struct tipc_link *r,
				    int *rc)
{
	struct sk_buff *skb = skb_peek(&l->transmq);
	struct tipc_msg *hdr;

	if (!skb)
		return false;

	if (!TIPC_SKB_CB(skb)->retr_cnt)
		return false;

	if (!time_after(jiffies, TIPC_SKB_CB(skb)->retr_stamp +
			msecs_to_jiffies(r->tolerance)))
		return false;

	hdr = buf_msg(skb);
	if (link_is_bc_sndlink(l) && !less(r->acked, msg_seqno(hdr)))
		return false;

	pr_warn("Retransmission failure on link <%s>\n", l->name);
	link_print(l, "State of link ");
	pr_info("Failed msg: usr %u, typ %u, len %u, err %u\n",
		msg_user(hdr), msg_type(hdr), msg_size(hdr), msg_errcode(hdr));
	pr_info("sqno %u, prev: %x, dest: %x\n",
		msg_seqno(hdr), msg_prevnode(hdr), msg_destnode(hdr));
	pr_info("retr_stamp %d, retr_cnt %d\n",
		jiffies_to_msecs(TIPC_SKB_CB(skb)->retr_stamp),
		TIPC_SKB_CB(skb)->retr_cnt);

	trace_tipc_list_dump(&l->transmq, true, "retrans failure!");
	trace_tipc_link_dump(l, TIPC_DUMP_NONE, "retrans failure!");
	trace_tipc_link_dump(r, TIPC_DUMP_NONE, "retrans failure!");

	if (link_is_bc_sndlink(l)) {
		r->state = LINK_RESET;
		*rc = TIPC_LINK_DOWN_EVT;
	} else {
		*rc = tipc_link_fsm_evt(l, LINK_FAILURE_EVT);
	}

	return true;
}