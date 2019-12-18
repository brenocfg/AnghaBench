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
struct sock {int /*<<< orphan*/  sk_drops; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ truesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UDPLITE (struct sock*) ; 
 int /*<<< orphan*/  UDP_MIB_CSUMERRORS ; 
 int /*<<< orphan*/  UDP_MIB_INERRORS ; 
 int /*<<< orphan*/  __UDP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ udp_lib_checksum_complete (struct sk_buff*) ; 
 int /*<<< orphan*/  udp_skb_csum_unnecessary_set (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *__first_packet_length(struct sock *sk,
					     struct sk_buff_head *rcvq,
					     int *total)
{
	struct sk_buff *skb;

	while ((skb = skb_peek(rcvq)) != NULL) {
		if (udp_lib_checksum_complete(skb)) {
			__UDP_INC_STATS(sock_net(sk), UDP_MIB_CSUMERRORS,
					IS_UDPLITE(sk));
			__UDP_INC_STATS(sock_net(sk), UDP_MIB_INERRORS,
					IS_UDPLITE(sk));
			atomic_inc(&sk->sk_drops);
			__skb_unlink(skb, rcvq);
			*total += skb->truesize;
			kfree_skb(skb);
		} else {
			udp_skb_csum_unnecessary_set(skb);
			break;
		}
	}
	return skb;
}