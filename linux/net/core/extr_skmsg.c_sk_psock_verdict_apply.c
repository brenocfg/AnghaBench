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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct tcp_skb_cb {TYPE_1__ bpf; } ;
struct sock {int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_psock {int /*<<< orphan*/  work; int /*<<< orphan*/  ingress_skb; struct sock* sk; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_INGRESS ; 
 int /*<<< orphan*/  SK_PSOCK_TX_ENABLED ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 struct tcp_skb_cb* TCP_SKB_CB (struct sk_buff*) ; 
#define  __SK_DROP 130 
#define  __SK_PASS 129 
#define  __SK_REDIRECT 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct sk_psock* sk_psock (struct sock*) ; 
 int /*<<< orphan*/  sk_psock_test_state (struct sk_psock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_writeable (struct sock*) ; 
 int tcp_skb_bpf_ingress (struct sk_buff*) ; 
 struct sock* tcp_skb_bpf_redirect_fetch (struct sk_buff*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static void sk_psock_verdict_apply(struct sk_psock *psock,
				   struct sk_buff *skb, int verdict)
{
	struct sk_psock *psock_other;
	struct sock *sk_other;
	bool ingress;

	switch (verdict) {
	case __SK_PASS:
		sk_other = psock->sk;
		if (sock_flag(sk_other, SOCK_DEAD) ||
		    !sk_psock_test_state(psock, SK_PSOCK_TX_ENABLED)) {
			goto out_free;
		}
		if (atomic_read(&sk_other->sk_rmem_alloc) <=
		    sk_other->sk_rcvbuf) {
			struct tcp_skb_cb *tcp = TCP_SKB_CB(skb);

			tcp->bpf.flags |= BPF_F_INGRESS;
			skb_queue_tail(&psock->ingress_skb, skb);
			schedule_work(&psock->work);
			break;
		}
		goto out_free;
	case __SK_REDIRECT:
		sk_other = tcp_skb_bpf_redirect_fetch(skb);
		if (unlikely(!sk_other))
			goto out_free;
		psock_other = sk_psock(sk_other);
		if (!psock_other || sock_flag(sk_other, SOCK_DEAD) ||
		    !sk_psock_test_state(psock_other, SK_PSOCK_TX_ENABLED))
			goto out_free;
		ingress = tcp_skb_bpf_ingress(skb);
		if ((!ingress && sock_writeable(sk_other)) ||
		    (ingress &&
		     atomic_read(&sk_other->sk_rmem_alloc) <=
		     sk_other->sk_rcvbuf)) {
			if (!ingress)
				skb_set_owner_w(skb, sk_other);
			skb_queue_tail(&psock_other->ingress_skb, skb);
			schedule_work(&psock_other->work);
			break;
		}
		/* fall-through */
	case __SK_DROP:
		/* fall-through */
	default:
out_free:
		kfree_skb(skb);
	}
}