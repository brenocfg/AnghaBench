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
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct tipc_link {int in_session; int snd_nxt; int rcv_nxt; int snd_nxt_state; int rcv_nxt_state; int bc_peer_is_up; int /*<<< orphan*/  mon_state; scalar_t__ stale_cnt; scalar_t__ rst_cnt; scalar_t__ silent_intv_cnt; scalar_t__ acked; scalar_t__ rcv_unacked; int /*<<< orphan*/ * failover_reasm_skb; int /*<<< orphan*/ * reasm_buf; TYPE_1__* backlog; int /*<<< orphan*/  backlogq; int /*<<< orphan*/  deferdq; int /*<<< orphan*/  transmq; struct sk_buff_head* inputq; struct sk_buff_head wakeupq; int /*<<< orphan*/  advertised_mtu; int /*<<< orphan*/  mtu; int /*<<< orphan*/  session; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 size_t TIPC_CRITICAL_IMPORTANCE ; 
 size_t TIPC_HIGH_IMPORTANCE ; 
 size_t TIPC_LOW_IMPORTANCE ; 
 size_t TIPC_MEDIUM_IMPORTANCE ; 
 size_t TIPC_SYSTEM_IMPORTANCE ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_queue_splice_init (struct sk_buff_head*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_link_reset_stats (struct tipc_link*) ; 

void tipc_link_reset(struct tipc_link *l)
{
	struct sk_buff_head list;

	__skb_queue_head_init(&list);

	l->in_session = false;
	l->session++;
	l->mtu = l->advertised_mtu;

	spin_lock_bh(&l->wakeupq.lock);
	skb_queue_splice_init(&l->wakeupq, &list);
	spin_unlock_bh(&l->wakeupq.lock);

	spin_lock_bh(&l->inputq->lock);
	skb_queue_splice_init(&list, l->inputq);
	spin_unlock_bh(&l->inputq->lock);

	__skb_queue_purge(&l->transmq);
	__skb_queue_purge(&l->deferdq);
	__skb_queue_purge(&l->backlogq);
	l->backlog[TIPC_LOW_IMPORTANCE].len = 0;
	l->backlog[TIPC_MEDIUM_IMPORTANCE].len = 0;
	l->backlog[TIPC_HIGH_IMPORTANCE].len = 0;
	l->backlog[TIPC_CRITICAL_IMPORTANCE].len = 0;
	l->backlog[TIPC_SYSTEM_IMPORTANCE].len = 0;
	kfree_skb(l->reasm_buf);
	kfree_skb(l->failover_reasm_skb);
	l->reasm_buf = NULL;
	l->failover_reasm_skb = NULL;
	l->rcv_unacked = 0;
	l->snd_nxt = 1;
	l->rcv_nxt = 1;
	l->snd_nxt_state = 1;
	l->rcv_nxt_state = 1;
	l->acked = 0;
	l->silent_intv_cnt = 0;
	l->rst_cnt = 0;
	l->stale_cnt = 0;
	l->bc_peer_is_up = false;
	memset(&l->mon_state, 0, sizeof(l->mon_state));
	tipc_link_reset_stats(l);
}