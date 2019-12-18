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
struct udphdr {scalar_t__ check; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IS_UDPLITE (struct sock*) ; 
 int /*<<< orphan*/  inet_compute_pseudo ; 
 scalar_t__ inet_get_convert_csum (struct sock*) ; 
 int /*<<< orphan*/  skb_checksum_try_convert (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int udp_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int udp_unicast_rcv_skb(struct sock *sk, struct sk_buff *skb,
			       struct udphdr *uh)
{
	int ret;

	if (inet_get_convert_csum(sk) && uh->check && !IS_UDPLITE(sk))
		skb_checksum_try_convert(skb, IPPROTO_UDP, inet_compute_pseudo);

	ret = udp_queue_rcv_skb(sk, skb);

	/* a return value > 0 means to resubmit the input, but
	 * it wants the return to be -protocol, or 0
	 */
	if (ret > 0)
		return -ret;
	return 0;
}