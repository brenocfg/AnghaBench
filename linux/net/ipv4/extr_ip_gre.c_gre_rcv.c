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
struct tnl_ptk_info {scalar_t__ proto; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ERSPAN ; 
 int /*<<< orphan*/  ETH_P_ERSPAN2 ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_PORT_UNREACH ; 
 scalar_t__ PACKET_RCVD ; 
 scalar_t__ erspan_rcv (struct sk_buff*,struct tnl_ptk_info*,int) ; 
 int gre_parse_header (struct sk_buff*,struct tnl_ptk_info*,int*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ipgre_rcv (struct sk_buff*,struct tnl_ptk_info*,int) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ rt_is_output_route (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_rtable (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gre_rcv(struct sk_buff *skb)
{
	struct tnl_ptk_info tpi;
	bool csum_err = false;
	int hdr_len;

#ifdef CONFIG_NET_IPGRE_BROADCAST
	if (ipv4_is_multicast(ip_hdr(skb)->daddr)) {
		/* Looped back packet, drop it! */
		if (rt_is_output_route(skb_rtable(skb)))
			goto drop;
	}
#endif

	hdr_len = gre_parse_header(skb, &tpi, &csum_err, htons(ETH_P_IP), 0);
	if (hdr_len < 0)
		goto drop;

	if (unlikely(tpi.proto == htons(ETH_P_ERSPAN) ||
		     tpi.proto == htons(ETH_P_ERSPAN2))) {
		if (erspan_rcv(skb, &tpi, hdr_len) == PACKET_RCVD)
			return 0;
		goto out;
	}

	if (ipgre_rcv(skb, &tpi, hdr_len) == PACKET_RCVD)
		return 0;

out:
	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);
drop:
	kfree_skb(skb);
	return 0;
}