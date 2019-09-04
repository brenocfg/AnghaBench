#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {TYPE_6__* dev; scalar_t__ data; } ;
struct TYPE_9__ {int /*<<< orphan*/  sysctl_icmp_ignore_bogus_error_responses; int /*<<< orphan*/  sysctl_ip_no_pmtu_disc; } ;
struct net {TYPE_3__ ipv4; } ;
struct iphdr {int ihl; int /*<<< orphan*/  daddr; int /*<<< orphan*/  protocol; } ;
struct TYPE_7__ {int /*<<< orphan*/  mtu; } ;
struct TYPE_8__ {int /*<<< orphan*/  gateway; TYPE_1__ frag; } ;
struct icmphdr {int type; int code; TYPE_2__ un; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ICMP_DEST_UNREACH 136 
 int ICMP_EXC_FRAGTIME ; 
#define  ICMP_FRAG_NEEDED 135 
#define  ICMP_HOST_UNREACH 134 
 int /*<<< orphan*/  ICMP_MIB_INERRORS ; 
 int /*<<< orphan*/  ICMP_MIB_INTIMEEXCDS ; 
#define  ICMP_NET_UNREACH 133 
#define  ICMP_PARAMETERPROB 132 
#define  ICMP_PORT_UNREACH 131 
#define  ICMP_PROT_UNREACH 130 
#define  ICMP_SR_FAILED 129 
#define  ICMP_TIME_EXCEEDED 128 
 int NR_ICMP_UNREACH ; 
 scalar_t__ RTN_BROADCAST ; 
 int /*<<< orphan*/  __ICMP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 struct icmphdr* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  icmp_socket_deliver (struct sk_buff*,int) ; 
 int /*<<< orphan*/  icmp_tag_validation (int /*<<< orphan*/ ) ; 
 scalar_t__ inet_addr_type_dev_table (struct net*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 TYPE_4__* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static bool icmp_unreach(struct sk_buff *skb)
{
	const struct iphdr *iph;
	struct icmphdr *icmph;
	struct net *net;
	u32 info = 0;

	net = dev_net(skb_dst(skb)->dev);

	/*
	 *	Incomplete header ?
	 * 	Only checks for the IP header, there should be an
	 *	additional check for longer headers in upper levels.
	 */

	if (!pskb_may_pull(skb, sizeof(struct iphdr)))
		goto out_err;

	icmph = icmp_hdr(skb);
	iph   = (const struct iphdr *)skb->data;

	if (iph->ihl < 5) /* Mangled header, drop. */
		goto out_err;

	switch (icmph->type) {
	case ICMP_DEST_UNREACH:
		switch (icmph->code & 15) {
		case ICMP_NET_UNREACH:
		case ICMP_HOST_UNREACH:
		case ICMP_PROT_UNREACH:
		case ICMP_PORT_UNREACH:
			break;
		case ICMP_FRAG_NEEDED:
			/* for documentation of the ip_no_pmtu_disc
			 * values please see
			 * Documentation/networking/ip-sysctl.txt
			 */
			switch (net->ipv4.sysctl_ip_no_pmtu_disc) {
			default:
				net_dbg_ratelimited("%pI4: fragmentation needed and DF set\n",
						    &iph->daddr);
				break;
			case 2:
				goto out;
			case 3:
				if (!icmp_tag_validation(iph->protocol))
					goto out;
				/* fall through */
			case 0:
				info = ntohs(icmph->un.frag.mtu);
			}
			break;
		case ICMP_SR_FAILED:
			net_dbg_ratelimited("%pI4: Source Route Failed\n",
					    &iph->daddr);
			break;
		default:
			break;
		}
		if (icmph->code > NR_ICMP_UNREACH)
			goto out;
		break;
	case ICMP_PARAMETERPROB:
		info = ntohl(icmph->un.gateway) >> 24;
		break;
	case ICMP_TIME_EXCEEDED:
		__ICMP_INC_STATS(net, ICMP_MIB_INTIMEEXCDS);
		if (icmph->code == ICMP_EXC_FRAGTIME)
			goto out;
		break;
	}

	/*
	 *	Throw it at our lower layers
	 *
	 *	RFC 1122: 3.2.2 MUST extract the protocol ID from the passed
	 *		  header.
	 *	RFC 1122: 3.2.2.1 MUST pass ICMP unreach messages to the
	 *		  transport layer.
	 *	RFC 1122: 3.2.2.2 MUST pass ICMP time expired messages to
	 *		  transport layer.
	 */

	/*
	 *	Check the other end isn't violating RFC 1122. Some routers send
	 *	bogus responses to broadcast frames. If you see this message
	 *	first check your netmask matches at both ends, if it does then
	 *	get the other vendor to fix their kit.
	 */

	if (!net->ipv4.sysctl_icmp_ignore_bogus_error_responses &&
	    inet_addr_type_dev_table(net, skb->dev, iph->daddr) == RTN_BROADCAST) {
		net_warn_ratelimited("%pI4 sent an invalid ICMP type %u, code %u error to a broadcast: %pI4 on %s\n",
				     &ip_hdr(skb)->saddr,
				     icmph->type, icmph->code,
				     &iph->daddr, skb->dev->name);
		goto out;
	}

	icmp_socket_deliver(skb, info);

out:
	return true;
out_err:
	__ICMP_INC_STATS(net, ICMP_MIB_INERRORS);
	return false;
}