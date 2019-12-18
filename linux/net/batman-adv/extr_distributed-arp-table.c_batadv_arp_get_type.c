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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  dev; } ;
struct ethhdr {scalar_t__ h_proto; } ;
struct batadv_priv {int dummy; } ;
struct arphdr {scalar_t__ ar_hrd; scalar_t__ ar_pro; scalar_t__ ar_hln; int ar_pln; scalar_t__ ar_op; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 scalar_t__ ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ arp_hdr_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * batadv_arp_hw_dst (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * batadv_arp_hw_src (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_arp_ip_dst (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_arp_ip_src (struct sk_buff*,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_lbcast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_loopback (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_zeronet (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 batadv_arp_get_type(struct batadv_priv *bat_priv,
			       struct sk_buff *skb, int hdr_size)
{
	struct arphdr *arphdr;
	struct ethhdr *ethhdr;
	__be32 ip_src, ip_dst;
	u8 *hw_src, *hw_dst;
	u16 type = 0;

	/* pull the ethernet header */
	if (unlikely(!pskb_may_pull(skb, hdr_size + ETH_HLEN)))
		goto out;

	ethhdr = (struct ethhdr *)(skb->data + hdr_size);

	if (ethhdr->h_proto != htons(ETH_P_ARP))
		goto out;

	/* pull the ARP payload */
	if (unlikely(!pskb_may_pull(skb, hdr_size + ETH_HLEN +
				    arp_hdr_len(skb->dev))))
		goto out;

	arphdr = (struct arphdr *)(skb->data + hdr_size + ETH_HLEN);

	/* check whether the ARP packet carries a valid IP information */
	if (arphdr->ar_hrd != htons(ARPHRD_ETHER))
		goto out;

	if (arphdr->ar_pro != htons(ETH_P_IP))
		goto out;

	if (arphdr->ar_hln != ETH_ALEN)
		goto out;

	if (arphdr->ar_pln != 4)
		goto out;

	/* Check for bad reply/request. If the ARP message is not sane, DAT
	 * will simply ignore it
	 */
	ip_src = batadv_arp_ip_src(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);
	if (ipv4_is_loopback(ip_src) || ipv4_is_multicast(ip_src) ||
	    ipv4_is_loopback(ip_dst) || ipv4_is_multicast(ip_dst) ||
	    ipv4_is_zeronet(ip_src) || ipv4_is_lbcast(ip_src) ||
	    ipv4_is_zeronet(ip_dst) || ipv4_is_lbcast(ip_dst))
		goto out;

	hw_src = batadv_arp_hw_src(skb, hdr_size);
	if (is_zero_ether_addr(hw_src) || is_multicast_ether_addr(hw_src))
		goto out;

	/* don't care about the destination MAC address in ARP requests */
	if (arphdr->ar_op != htons(ARPOP_REQUEST)) {
		hw_dst = batadv_arp_hw_dst(skb, hdr_size);
		if (is_zero_ether_addr(hw_dst) ||
		    is_multicast_ether_addr(hw_dst))
			goto out;
	}

	type = ntohs(arphdr->ar_op);
out:
	return type;
}