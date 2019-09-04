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
struct sk_buff {int dummy; } ;
struct fou {scalar_t__ family; } ;
struct TYPE_4__ {void* tot_len; } ;
struct TYPE_3__ {void* payload_len; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,size_t) ; 
 void* htons (scalar_t__) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int iptunnel_pull_offloads (struct sk_buff*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ ntohs (void*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  udp_hdr (struct sk_buff*) ; 

__attribute__((used)) static int fou_recv_pull(struct sk_buff *skb, struct fou *fou, size_t len)
{
	/* Remove 'len' bytes from the packet (UDP header and
	 * FOU header if present).
	 */
	if (fou->family == AF_INET)
		ip_hdr(skb)->tot_len = htons(ntohs(ip_hdr(skb)->tot_len) - len);
	else
		ipv6_hdr(skb)->payload_len =
		    htons(ntohs(ipv6_hdr(skb)->payload_len) - len);

	__skb_pull(skb, len);
	skb_postpull_rcsum(skb, udp_hdr(skb), len);
	skb_reset_transport_header(skb);
	return iptunnel_pull_offloads(skb);
}