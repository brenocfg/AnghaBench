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
typedef  int /*<<< orphan*/  u32 ;
struct tnl_ptk_info {int dummy; } ;
struct sk_buff {TYPE_2__* dev; scalar_t__ data; } ;
struct iphdr {int ihl; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_3__ {int type; int code; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int const ICMP_DEST_UNREACH ; 
 int const ICMP_FRAG_NEEDED ; 
 int const ICMP_REDIRECT ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int /*<<< orphan*/  dev_net (TYPE_2__*) ; 
 scalar_t__ gre_parse_header (struct sk_buff*,struct tnl_ptk_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipgre_err (struct sk_buff*,int /*<<< orphan*/ ,struct tnl_ptk_info*) ; 
 int /*<<< orphan*/  ipv4_redirect (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_update_pmtu (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gre_err(struct sk_buff *skb, u32 info)
{
	/* All the routers (except for Linux) return only
	 * 8 bytes of packet payload. It means, that precise relaying of
	 * ICMP in the real Internet is absolutely infeasible.
	 *
	 * Moreover, Cisco "wise men" put GRE key to the third word
	 * in GRE header. It makes impossible maintaining even soft
	 * state for keyed
	 * GRE tunnels with enabled checksum. Tell them "thank you".
	 *
	 * Well, I wonder, rfc1812 was written by Cisco employee,
	 * what the hell these idiots break standards established
	 * by themselves???
	 */

	const struct iphdr *iph = (struct iphdr *)skb->data;
	const int type = icmp_hdr(skb)->type;
	const int code = icmp_hdr(skb)->code;
	struct tnl_ptk_info tpi;

	if (gre_parse_header(skb, &tpi, NULL, htons(ETH_P_IP),
			     iph->ihl * 4) < 0)
		return;

	if (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED) {
		ipv4_update_pmtu(skb, dev_net(skb->dev), info,
				 skb->dev->ifindex, IPPROTO_GRE);
		return;
	}
	if (type == ICMP_REDIRECT) {
		ipv4_redirect(skb, dev_net(skb->dev), skb->dev->ifindex,
			      IPPROTO_GRE);
		return;
	}

	ipgre_err(skb, info, &tpi);
}