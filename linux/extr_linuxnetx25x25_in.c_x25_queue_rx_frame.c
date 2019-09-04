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
struct x25_sock {int fraglen; TYPE_1__* neighbour; int /*<<< orphan*/  fragment_queue; } ;
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int len; } ;
struct TYPE_2__ {scalar_t__ extended; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  X25_EXT_MIN_LEN ; 
 int /*<<< orphan*/  X25_STD_MIN_LEN ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct x25_sock* x25_sk (struct sock*) ; 

__attribute__((used)) static int x25_queue_rx_frame(struct sock *sk, struct sk_buff *skb, int more)
{
	struct sk_buff *skbo, *skbn = skb;
	struct x25_sock *x25 = x25_sk(sk);

	if (more) {
		x25->fraglen += skb->len;
		skb_queue_tail(&x25->fragment_queue, skb);
		skb_set_owner_r(skb, sk);
		return 0;
	}

	if (!more && x25->fraglen > 0) {	/* End of fragment */
		int len = x25->fraglen + skb->len;

		if ((skbn = alloc_skb(len, GFP_ATOMIC)) == NULL){
			kfree_skb(skb);
			return 1;
		}

		skb_queue_tail(&x25->fragment_queue, skb);

		skb_reset_transport_header(skbn);

		skbo = skb_dequeue(&x25->fragment_queue);
		skb_copy_from_linear_data(skbo, skb_put(skbn, skbo->len),
					  skbo->len);
		kfree_skb(skbo);

		while ((skbo =
			skb_dequeue(&x25->fragment_queue)) != NULL) {
			skb_pull(skbo, (x25->neighbour->extended) ?
					X25_EXT_MIN_LEN : X25_STD_MIN_LEN);
			skb_copy_from_linear_data(skbo,
						  skb_put(skbn, skbo->len),
						  skbo->len);
			kfree_skb(skbo);
		}

		x25->fraglen = 0;
	}

	skb_set_owner_r(skbn, sk);
	skb_queue_tail(&sk->sk_receive_queue, skbn);
	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_ready(sk);

	return 0;
}