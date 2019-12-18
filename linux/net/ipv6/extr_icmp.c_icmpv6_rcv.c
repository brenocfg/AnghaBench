#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {struct net_device* dev; } ;
struct sec_path {int len; TYPE_2__** xvec; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  icmpv6_echo_ignore_all; } ;
struct TYPE_9__ {TYPE_3__ sysctl; } ;
struct net {TYPE_4__ ipv6; } ;
struct ipv6hdr {int dummy; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;
struct icmp6hdr {int icmp6_type; int /*<<< orphan*/  icmp6_mtu; int /*<<< orphan*/  icmp6_code; } ;
struct TYPE_10__ {struct in6_addr daddr; struct in6_addr saddr; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_7__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6MSGIN_INC_STATS (struct net*,struct inet6_dev*,int) ; 
 int /*<<< orphan*/  ICMP6_MIB_CSUMERRORS ; 
 int /*<<< orphan*/  ICMP6_MIB_INERRORS ; 
 int /*<<< orphan*/  ICMP6_MIB_INMSGS ; 
#define  ICMPV6_DEST_UNREACH 148 
#define  ICMPV6_DHAAD_REPLY 147 
#define  ICMPV6_DHAAD_REQUEST 146 
#define  ICMPV6_ECHO_REPLY 145 
#define  ICMPV6_ECHO_REQUEST 144 
 int ICMPV6_INFOMSG_MASK ; 
#define  ICMPV6_MGM_QUERY 143 
#define  ICMPV6_MGM_REDUCTION 142 
#define  ICMPV6_MGM_REPORT 141 
#define  ICMPV6_MLD2_REPORT 140 
#define  ICMPV6_MOBILE_PREFIX_ADV 139 
#define  ICMPV6_MOBILE_PREFIX_SOL 138 
#define  ICMPV6_NI_QUERY 137 
#define  ICMPV6_NI_REPLY 136 
#define  ICMPV6_PARAMPROB 135 
#define  ICMPV6_PKT_TOOBIG 134 
#define  ICMPV6_TIME_EXCEED 133 
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
#define  NDISC_NEIGHBOUR_ADVERTISEMENT 132 
#define  NDISC_NEIGHBOUR_SOLICITATION 131 
#define  NDISC_REDIRECT 130 
#define  NDISC_ROUTER_ADVERTISEMENT 129 
#define  NDISC_ROUTER_SOLICITATION 128 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int XFRM_STATE_ICMP ; 
 int /*<<< orphan*/  __ICMP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct net* dev_net (struct net_device*) ; 
 struct net_device* icmp6_dev (struct sk_buff*) ; 
 struct icmp6hdr* icmp6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  icmpv6_echo_reply (struct sk_buff*) ; 
 int /*<<< orphan*/  icmpv6_notify (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igmp6_event_query (struct sk_buff*) ; 
 int /*<<< orphan*/  igmp6_event_report (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_compute_pseudo ; 
 TYPE_5__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ndisc_rcv (struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,struct in6_addr const*,struct in6_addr const*) ; 
 int ping_rcv (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_checksum_validate (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_network_offset (struct sk_buff*) ; 
 struct sec_path* skb_sec_path (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  xfrm6_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm6_policy_check_reverse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int icmpv6_rcv(struct sk_buff *skb)
{
	struct net *net = dev_net(skb->dev);
	struct net_device *dev = icmp6_dev(skb);
	struct inet6_dev *idev = __in6_dev_get(dev);
	const struct in6_addr *saddr, *daddr;
	struct icmp6hdr *hdr;
	u8 type;
	bool success = false;

	if (!xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb)) {
		struct sec_path *sp = skb_sec_path(skb);
		int nh;

		if (!(sp && sp->xvec[sp->len - 1]->props.flags &
				 XFRM_STATE_ICMP))
			goto drop_no_count;

		if (!pskb_may_pull(skb, sizeof(*hdr) + sizeof(struct ipv6hdr)))
			goto drop_no_count;

		nh = skb_network_offset(skb);
		skb_set_network_header(skb, sizeof(*hdr));

		if (!xfrm6_policy_check_reverse(NULL, XFRM_POLICY_IN, skb))
			goto drop_no_count;

		skb_set_network_header(skb, nh);
	}

	__ICMP6_INC_STATS(dev_net(dev), idev, ICMP6_MIB_INMSGS);

	saddr = &ipv6_hdr(skb)->saddr;
	daddr = &ipv6_hdr(skb)->daddr;

	if (skb_checksum_validate(skb, IPPROTO_ICMPV6, ip6_compute_pseudo)) {
		net_dbg_ratelimited("ICMPv6 checksum failed [%pI6c > %pI6c]\n",
				    saddr, daddr);
		goto csum_error;
	}

	if (!pskb_pull(skb, sizeof(*hdr)))
		goto discard_it;

	hdr = icmp6_hdr(skb);

	type = hdr->icmp6_type;

	ICMP6MSGIN_INC_STATS(dev_net(dev), idev, type);

	switch (type) {
	case ICMPV6_ECHO_REQUEST:
		if (!net->ipv6.sysctl.icmpv6_echo_ignore_all)
			icmpv6_echo_reply(skb);
		break;

	case ICMPV6_ECHO_REPLY:
		success = ping_rcv(skb);
		break;

	case ICMPV6_PKT_TOOBIG:
		/* BUGGG_FUTURE: if packet contains rthdr, we cannot update
		   standard destination cache. Seems, only "advanced"
		   destination cache will allow to solve this problem
		   --ANK (980726)
		 */
		if (!pskb_may_pull(skb, sizeof(struct ipv6hdr)))
			goto discard_it;
		hdr = icmp6_hdr(skb);

		/* to notify */
		/* fall through */
	case ICMPV6_DEST_UNREACH:
	case ICMPV6_TIME_EXCEED:
	case ICMPV6_PARAMPROB:
		icmpv6_notify(skb, type, hdr->icmp6_code, hdr->icmp6_mtu);
		break;

	case NDISC_ROUTER_SOLICITATION:
	case NDISC_ROUTER_ADVERTISEMENT:
	case NDISC_NEIGHBOUR_SOLICITATION:
	case NDISC_NEIGHBOUR_ADVERTISEMENT:
	case NDISC_REDIRECT:
		ndisc_rcv(skb);
		break;

	case ICMPV6_MGM_QUERY:
		igmp6_event_query(skb);
		break;

	case ICMPV6_MGM_REPORT:
		igmp6_event_report(skb);
		break;

	case ICMPV6_MGM_REDUCTION:
	case ICMPV6_NI_QUERY:
	case ICMPV6_NI_REPLY:
	case ICMPV6_MLD2_REPORT:
	case ICMPV6_DHAAD_REQUEST:
	case ICMPV6_DHAAD_REPLY:
	case ICMPV6_MOBILE_PREFIX_SOL:
	case ICMPV6_MOBILE_PREFIX_ADV:
		break;

	default:
		/* informational */
		if (type & ICMPV6_INFOMSG_MASK)
			break;

		net_dbg_ratelimited("icmpv6: msg of unknown type [%pI6c > %pI6c]\n",
				    saddr, daddr);

		/*
		 * error of unknown type.
		 * must pass to upper level
		 */

		icmpv6_notify(skb, type, hdr->icmp6_code, hdr->icmp6_mtu);
	}

	/* until the v6 path can be better sorted assume failure and
	 * preserve the status quo behaviour for the rest of the paths to here
	 */
	if (success)
		consume_skb(skb);
	else
		kfree_skb(skb);

	return 0;

csum_error:
	__ICMP6_INC_STATS(dev_net(dev), idev, ICMP6_MIB_CSUMERRORS);
discard_it:
	__ICMP6_INC_STATS(dev_net(dev), idev, ICMP6_MIB_INERRORS);
drop_no_count:
	kfree_skb(skb);
	return 0;
}