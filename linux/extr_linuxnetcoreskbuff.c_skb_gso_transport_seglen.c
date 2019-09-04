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
struct udphdr {int dummy; } ;
struct skb_shared_info {int gso_type; unsigned int gso_size; } ;
struct sk_buff {scalar_t__ encapsulation; } ;
struct sctphdr {int dummy; } ;

/* Variables and functions */
 int SKB_GSO_TCPV4 ; 
 int SKB_GSO_TCPV6 ; 
 int SKB_GSO_UDP_L4 ; 
 scalar_t__ inner_tcp_hdrlen (struct sk_buff const*) ; 
 scalar_t__ likely (int) ; 
 unsigned int skb_inner_transport_header (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_is_gso_sctp (struct sk_buff const*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff const*) ; 
 unsigned int skb_transport_header (struct sk_buff const*) ; 
 unsigned int tcp_hdrlen (struct sk_buff const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int skb_gso_transport_seglen(const struct sk_buff *skb)
{
	const struct skb_shared_info *shinfo = skb_shinfo(skb);
	unsigned int thlen = 0;

	if (skb->encapsulation) {
		thlen = skb_inner_transport_header(skb) -
			skb_transport_header(skb);

		if (likely(shinfo->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)))
			thlen += inner_tcp_hdrlen(skb);
	} else if (likely(shinfo->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6))) {
		thlen = tcp_hdrlen(skb);
	} else if (unlikely(skb_is_gso_sctp(skb))) {
		thlen = sizeof(struct sctphdr);
	} else if (shinfo->gso_type & SKB_GSO_UDP_L4) {
		thlen = sizeof(struct udphdr);
	}
	/* UFO sets gso_size to the size of the fragmentation
	 * payload, i.e. the size of the L4 (UDP) header is already
	 * accounted for.
	 */
	return thlen + shinfo->gso_size;
}