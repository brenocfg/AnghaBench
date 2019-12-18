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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct ipv6hdr {int version; scalar_t__ nexthdr; int /*<<< orphan*/  payload_len; } ;
struct inet6_skb_parm {int dummy; } ;
struct inet6_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSTATS_MIB_INDISCARDS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INHDRERRORS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INTRUNCATEDPKTS ; 
 scalar_t__ NEXTHDR_HOP ; 
 int /*<<< orphan*/  __IP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* __in6_dev_get (int /*<<< orphan*/ ) ; 
 scalar_t__ br_nf_check_hbh_len (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ pskb_trim_rcsum (struct sk_buff*,scalar_t__) ; 

int br_validate_ipv6(struct net *net, struct sk_buff *skb)
{
	const struct ipv6hdr *hdr;
	struct inet6_dev *idev = __in6_dev_get(skb->dev);
	u32 pkt_len;
	u8 ip6h_len = sizeof(struct ipv6hdr);

	if (!pskb_may_pull(skb, ip6h_len))
		goto inhdr_error;

	if (skb->len < ip6h_len)
		goto drop;

	hdr = ipv6_hdr(skb);

	if (hdr->version != 6)
		goto inhdr_error;

	pkt_len = ntohs(hdr->payload_len);

	if (pkt_len || hdr->nexthdr != NEXTHDR_HOP) {
		if (pkt_len + ip6h_len > skb->len) {
			__IP6_INC_STATS(net, idev,
					IPSTATS_MIB_INTRUNCATEDPKTS);
			goto drop;
		}
		if (pskb_trim_rcsum(skb, pkt_len + ip6h_len)) {
			__IP6_INC_STATS(net, idev,
					IPSTATS_MIB_INDISCARDS);
			goto drop;
		}
		hdr = ipv6_hdr(skb);
	}
	if (hdr->nexthdr == NEXTHDR_HOP && br_nf_check_hbh_len(skb))
		goto drop;

	memset(IP6CB(skb), 0, sizeof(struct inet6_skb_parm));
	/* No IP options in IPv6 header; however it should be
	 * checked if some next headers need special treatment
	 */
	return 0;

inhdr_error:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
drop:
	return -1;
}