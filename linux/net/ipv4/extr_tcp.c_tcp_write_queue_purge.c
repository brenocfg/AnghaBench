#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {struct sk_buff* sk_tx_skb_cache; int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {scalar_t__ icsk_backoff; } ;
struct TYPE_4__ {scalar_t__ packets_out; int /*<<< orphan*/  tsorted_sent_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCP_CHRONO_BUSY ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 TYPE_3__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  sk_mem_reclaim (struct sock*) ; 
 int /*<<< orphan*/  sk_wmem_free_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_chrono_stop (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_clear_all_retrans_hints (TYPE_1__*) ; 
 int /*<<< orphan*/  tcp_rtx_queue_purge (struct sock*) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_skb_tsorted_anchor_cleanup (struct sk_buff*) ; 

void tcp_write_queue_purge(struct sock *sk)
{
	struct sk_buff *skb;

	tcp_chrono_stop(sk, TCP_CHRONO_BUSY);
	while ((skb = __skb_dequeue(&sk->sk_write_queue)) != NULL) {
		tcp_skb_tsorted_anchor_cleanup(skb);
		sk_wmem_free_skb(sk, skb);
	}
	tcp_rtx_queue_purge(sk);
	skb = sk->sk_tx_skb_cache;
	if (skb) {
		__kfree_skb(skb);
		sk->sk_tx_skb_cache = NULL;
	}
	INIT_LIST_HEAD(&tcp_sk(sk)->tsorted_sent_queue);
	sk_mem_reclaim(sk);
	tcp_clear_all_retrans_hints(tcp_sk(sk));
	tcp_sk(sk)->packets_out = 0;
	inet_csk(sk)->icsk_backoff = 0;
}