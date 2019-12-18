#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {scalar_t__ rcv_nxt; scalar_t__ rcv_wup; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  max_window; int /*<<< orphan*/  fastopen_rsk; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  qlen; } ;
struct request_sock_queue {TYPE_2__ fastopenq; } ;
struct request_sock {int /*<<< orphan*/  rsk_refcnt; } ;
struct TYPE_12__ {scalar_t__ seq; } ;
struct TYPE_11__ {TYPE_1__* icsk_af_ops; struct request_sock_queue icsk_accept_queue; } ;
struct TYPE_10__ {int /*<<< orphan*/  window; } ;
struct TYPE_9__ {int tfo_listener; scalar_t__ rcv_nxt; } ;
struct TYPE_7__ {struct sock* (* syn_recv_sock ) (struct sock*,struct sk_buff*,struct request_sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB ; 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  TCP_RTO_MAX ; 
 TYPE_6__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  TCP_TIMEOUT_INIT ; 
 TYPE_5__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct request_sock*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sock* stub1 (struct sock*,struct sk_buff*,struct request_sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  tcp_fastopen_add_skb (struct sock*,struct sk_buff*) ; 
 TYPE_4__* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_init_transfer (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tcp_rsk (struct request_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static struct sock *tcp_fastopen_create_child(struct sock *sk,
					      struct sk_buff *skb,
					      struct request_sock *req)
{
	struct tcp_sock *tp;
	struct request_sock_queue *queue = &inet_csk(sk)->icsk_accept_queue;
	struct sock *child;
	bool own_req;

	child = inet_csk(sk)->icsk_af_ops->syn_recv_sock(sk, skb, req, NULL,
							 NULL, &own_req);
	if (!child)
		return NULL;

	spin_lock(&queue->fastopenq.lock);
	queue->fastopenq.qlen++;
	spin_unlock(&queue->fastopenq.lock);

	/* Initialize the child socket. Have to fix some values to take
	 * into account the child is a Fast Open socket and is created
	 * only out of the bits carried in the SYN packet.
	 */
	tp = tcp_sk(child);

	rcu_assign_pointer(tp->fastopen_rsk, req);
	tcp_rsk(req)->tfo_listener = true;

	/* RFC1323: The window in SYN & SYN/ACK segments is never
	 * scaled. So correct it appropriately.
	 */
	tp->snd_wnd = ntohs(tcp_hdr(skb)->window);
	tp->max_window = tp->snd_wnd;

	/* Activate the retrans timer so that SYNACK can be retransmitted.
	 * The request socket is not added to the ehash
	 * because it's been added to the accept queue directly.
	 */
	inet_csk_reset_xmit_timer(child, ICSK_TIME_RETRANS,
				  TCP_TIMEOUT_INIT, TCP_RTO_MAX);

	refcount_set(&req->rsk_refcnt, 2);

	/* Now finish processing the fastopen child socket. */
	tcp_init_transfer(child, BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB);

	tp->rcv_nxt = TCP_SKB_CB(skb)->seq + 1;

	tcp_fastopen_add_skb(child, skb);

	tcp_rsk(req)->rcv_nxt = tp->rcv_nxt;
	tp->rcv_wup = tp->rcv_nxt;
	/* tcp_conn_request() is sending the SYNACK,
	 * and queues the child into listener accept queue.
	 */
	return child;
}