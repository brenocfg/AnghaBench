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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int NR_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  NR_MORE_FLAG ; 
 int NR_TRANSPORT_LEN ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nr_kick (struct sock*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,int,int /*<<< orphan*/ ,int*) ; 

void nr_output(struct sock *sk, struct sk_buff *skb)
{
	struct sk_buff *skbn;
	unsigned char transport[NR_TRANSPORT_LEN];
	int err, frontlen, len;

	if (skb->len - NR_TRANSPORT_LEN > NR_MAX_PACKET_SIZE) {
		/* Save a copy of the Transport Header */
		skb_copy_from_linear_data(skb, transport, NR_TRANSPORT_LEN);
		skb_pull(skb, NR_TRANSPORT_LEN);

		frontlen = skb_headroom(skb);

		while (skb->len > 0) {
			if ((skbn = sock_alloc_send_skb(sk, frontlen + NR_MAX_PACKET_SIZE, 0, &err)) == NULL)
				return;

			skb_reserve(skbn, frontlen);

			len = (NR_MAX_PACKET_SIZE > skb->len) ? skb->len : NR_MAX_PACKET_SIZE;

			/* Copy the user data */
			skb_copy_from_linear_data(skb, skb_put(skbn, len), len);
			skb_pull(skb, len);

			/* Duplicate the Transport Header */
			skb_push(skbn, NR_TRANSPORT_LEN);
			skb_copy_to_linear_data(skbn, transport,
						NR_TRANSPORT_LEN);
			if (skb->len > 0)
				skbn->data[4] |= NR_MORE_FLAG;

			skb_queue_tail(&sk->sk_write_queue, skbn); /* Throw it on the queue */
		}

		kfree_skb(skb);
	} else {
		skb_queue_tail(&sk->sk_write_queue, skb);		/* Throw it on the queue */
	}

	nr_kick(sk);
}