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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct sk_buff_head {int dummy; } ;
struct tipc_link {struct sk_buff_head wakeupq; struct sk_buff_head* inputq; struct sk_buff_head deferdq; struct sk_buff_head backlogq; TYPE_1__* backlog; struct sk_buff_head transmq; int /*<<< orphan*/  acked; int /*<<< orphan*/  rst_cnt; int /*<<< orphan*/  silent_intv_cnt; int /*<<< orphan*/  peer_caps; int /*<<< orphan*/  rcv_nxt_state; int /*<<< orphan*/  snd_nxt_state; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  peer_session; int /*<<< orphan*/  session; int /*<<< orphan*/  in_session; int /*<<< orphan*/  state; int /*<<< orphan*/  addr; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 size_t LINK_LMAX ; 
 size_t LINK_LMIN ; 
 size_t TIPC_CRITICAL_IMPORTANCE ; 
 int TIPC_DUMP_BACKLOGQ ; 
 int TIPC_DUMP_DEFERDQ ; 
 int TIPC_DUMP_INPUTQ ; 
 int TIPC_DUMP_TRANSMQ ; 
 int TIPC_DUMP_WAKEUP ; 
 size_t TIPC_HIGH_IMPORTANCE ; 
 size_t TIPC_LOW_IMPORTANCE ; 
 size_t TIPC_MEDIUM_IMPORTANCE ; 
 size_t TIPC_SYSTEM_IMPORTANCE ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_seqno (int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,size_t,char*,...) ; 
 struct sk_buff* skb_peek (struct sk_buff_head*) ; 
 struct sk_buff* skb_peek_tail (struct sk_buff_head*) ; 
 scalar_t__ skb_queue_len (struct sk_buff_head*) ; 
 scalar_t__ tipc_list_dump (struct sk_buff_head*,int,char*) ; 

int tipc_link_dump(struct tipc_link *l, u16 dqueues, char *buf)
{
	int i = 0;
	size_t sz = (dqueues) ? LINK_LMAX : LINK_LMIN;
	struct sk_buff_head *list;
	struct sk_buff *hskb, *tskb;
	u32 len;

	if (!l) {
		i += scnprintf(buf, sz, "link data: (null)\n");
		return i;
	}

	i += scnprintf(buf, sz, "link data: %x", l->addr);
	i += scnprintf(buf + i, sz - i, " %x", l->state);
	i += scnprintf(buf + i, sz - i, " %u", l->in_session);
	i += scnprintf(buf + i, sz - i, " %u", l->session);
	i += scnprintf(buf + i, sz - i, " %u", l->peer_session);
	i += scnprintf(buf + i, sz - i, " %u", l->snd_nxt);
	i += scnprintf(buf + i, sz - i, " %u", l->rcv_nxt);
	i += scnprintf(buf + i, sz - i, " %u", l->snd_nxt_state);
	i += scnprintf(buf + i, sz - i, " %u", l->rcv_nxt_state);
	i += scnprintf(buf + i, sz - i, " %x", l->peer_caps);
	i += scnprintf(buf + i, sz - i, " %u", l->silent_intv_cnt);
	i += scnprintf(buf + i, sz - i, " %u", l->rst_cnt);
	i += scnprintf(buf + i, sz - i, " %u", 0);
	i += scnprintf(buf + i, sz - i, " %u", 0);
	i += scnprintf(buf + i, sz - i, " %u", l->acked);

	list = &l->transmq;
	len = skb_queue_len(list);
	hskb = skb_peek(list);
	tskb = skb_peek_tail(list);
	i += scnprintf(buf + i, sz - i, " | %u %u %u", len,
		       (hskb) ? msg_seqno(buf_msg(hskb)) : 0,
		       (tskb) ? msg_seqno(buf_msg(tskb)) : 0);

	list = &l->deferdq;
	len = skb_queue_len(list);
	hskb = skb_peek(list);
	tskb = skb_peek_tail(list);
	i += scnprintf(buf + i, sz - i, " | %u %u %u", len,
		       (hskb) ? msg_seqno(buf_msg(hskb)) : 0,
		       (tskb) ? msg_seqno(buf_msg(tskb)) : 0);

	list = &l->backlogq;
	len = skb_queue_len(list);
	hskb = skb_peek(list);
	tskb = skb_peek_tail(list);
	i += scnprintf(buf + i, sz - i, " | %u %u %u", len,
		       (hskb) ? msg_seqno(buf_msg(hskb)) : 0,
		       (tskb) ? msg_seqno(buf_msg(tskb)) : 0);

	list = l->inputq;
	len = skb_queue_len(list);
	hskb = skb_peek(list);
	tskb = skb_peek_tail(list);
	i += scnprintf(buf + i, sz - i, " | %u %u %u\n", len,
		       (hskb) ? msg_seqno(buf_msg(hskb)) : 0,
		       (tskb) ? msg_seqno(buf_msg(tskb)) : 0);

	if (dqueues & TIPC_DUMP_TRANSMQ) {
		i += scnprintf(buf + i, sz - i, "transmq: ");
		i += tipc_list_dump(&l->transmq, false, buf + i);
	}
	if (dqueues & TIPC_DUMP_BACKLOGQ) {
		i += scnprintf(buf + i, sz - i,
			       "backlogq: <%u %u %u %u %u>, ",
			       l->backlog[TIPC_LOW_IMPORTANCE].len,
			       l->backlog[TIPC_MEDIUM_IMPORTANCE].len,
			       l->backlog[TIPC_HIGH_IMPORTANCE].len,
			       l->backlog[TIPC_CRITICAL_IMPORTANCE].len,
			       l->backlog[TIPC_SYSTEM_IMPORTANCE].len);
		i += tipc_list_dump(&l->backlogq, false, buf + i);
	}
	if (dqueues & TIPC_DUMP_DEFERDQ) {
		i += scnprintf(buf + i, sz - i, "deferdq: ");
		i += tipc_list_dump(&l->deferdq, false, buf + i);
	}
	if (dqueues & TIPC_DUMP_INPUTQ) {
		i += scnprintf(buf + i, sz - i, "inputq: ");
		i += tipc_list_dump(l->inputq, false, buf + i);
	}
	if (dqueues & TIPC_DUMP_WAKEUP) {
		i += scnprintf(buf + i, sz - i, "wakeup: ");
		i += tipc_list_dump(&l->wakeupq, false, buf + i);
	}

	return i;
}