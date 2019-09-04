#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct smap_psock {int /*<<< orphan*/  tx_work; int /*<<< orphan*/  rxqueue; int /*<<< orphan*/  state; } ;
struct sk_buff {int dummy; } ;
typedef  int __u32 ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ bpf; } ;

/* Variables and functions */
 int BPF_F_INGRESS ; 
 int /*<<< orphan*/  SMAP_TX_RUNNING ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
#define  __SK_DROP 129 
#define  __SK_REDIRECT 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct sock* do_sk_redirect_map (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 int smap_verdict_func (struct smap_psock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_writeable (struct sock*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static void smap_do_verdict(struct smap_psock *psock, struct sk_buff *skb)
{
	struct smap_psock *peer;
	struct sock *sk;
	__u32 in;
	int rc;

	rc = smap_verdict_func(psock, skb);
	switch (rc) {
	case __SK_REDIRECT:
		sk = do_sk_redirect_map(skb);
		if (!sk) {
			kfree_skb(skb);
			break;
		}

		peer = smap_psock_sk(sk);
		in = (TCP_SKB_CB(skb)->bpf.flags) & BPF_F_INGRESS;

		if (unlikely(!peer || sock_flag(sk, SOCK_DEAD) ||
			     !test_bit(SMAP_TX_RUNNING, &peer->state))) {
			kfree_skb(skb);
			break;
		}

		if (!in && sock_writeable(sk)) {
			skb_set_owner_w(skb, sk);
			skb_queue_tail(&peer->rxqueue, skb);
			schedule_work(&peer->tx_work);
			break;
		} else if (in &&
			   atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf) {
			skb_queue_tail(&peer->rxqueue, skb);
			schedule_work(&peer->tx_work);
			break;
		}
	/* Fall through and free skb otherwise */
	case __SK_DROP:
	default:
		kfree_skb(skb);
	}
}