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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct nr_sock {scalar_t__ fraglen; int /*<<< orphan*/  frag_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NR_NETWORK_LEN ; 
 scalar_t__ NR_TRANSPORT_LEN ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  nr_start_idletimer (struct sock*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int nr_queue_rx_frame(struct sock *sk, struct sk_buff *skb, int more)
{
	struct sk_buff *skbo, *skbn = skb;
	struct nr_sock *nr = nr_sk(sk);

	skb_pull(skb, NR_NETWORK_LEN + NR_TRANSPORT_LEN);

	nr_start_idletimer(sk);

	if (more) {
		nr->fraglen += skb->len;
		skb_queue_tail(&nr->frag_queue, skb);
		return 0;
	}

	if (!more && nr->fraglen > 0) {	/* End of fragment */
		nr->fraglen += skb->len;
		skb_queue_tail(&nr->frag_queue, skb);

		if ((skbn = alloc_skb(nr->fraglen, GFP_ATOMIC)) == NULL)
			return 1;

		skb_reset_transport_header(skbn);

		while ((skbo = skb_dequeue(&nr->frag_queue)) != NULL) {
			skb_copy_from_linear_data(skbo,
						  skb_put(skbn, skbo->len),
						  skbo->len);
			kfree_skb(skbo);
		}

		nr->fraglen = 0;
	}

	return sock_queue_rcv_skb(sk, skbn);
}