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
struct sk_buff {int dummy; } ;
struct iphdr {int frag_off; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  IP_OFFSET ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_hdrlen (struct sk_buff*) ; 
 scalar_t__ nf_ip_checksum (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_reject_verify_csum (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_csum_unnecessary (struct sk_buff*) ; 

void nf_send_unreach(struct sk_buff *skb_in, int code, int hook)
{
	struct iphdr *iph = ip_hdr(skb_in);
	u8 proto = iph->protocol;

	if (iph->frag_off & htons(IP_OFFSET))
		return;

	if (skb_csum_unnecessary(skb_in) || !nf_reject_verify_csum(proto)) {
		icmp_send(skb_in, ICMP_DEST_UNREACH, code, 0);
		return;
	}

	if (nf_ip_checksum(skb_in, hook, ip_hdrlen(skb_in), proto) == 0)
		icmp_send(skb_in, ICMP_DEST_UNREACH, code, 0);
}