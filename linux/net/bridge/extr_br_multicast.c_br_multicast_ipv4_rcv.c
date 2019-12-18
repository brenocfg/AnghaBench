#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_bridge_port {int dummy; } ;
struct net_bridge {int dummy; } ;
struct igmphdr {int type; int /*<<< orphan*/  group; } ;
struct TYPE_6__ {int mrouters_only; int igmp; } ;
struct TYPE_5__ {unsigned char* h_source; } ;
struct TYPE_4__ {scalar_t__ protocol; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 TYPE_3__* BR_INPUT_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  BR_MCAST_DIR_RX ; 
 int ENOMSG ; 
#define  IGMPV2_HOST_MEMBERSHIP_REPORT 132 
#define  IGMPV3_HOST_MEMBERSHIP_REPORT 131 
#define  IGMP_HOST_LEAVE_MESSAGE 130 
#define  IGMP_HOST_MEMBERSHIP_QUERY 129 
#define  IGMP_HOST_MEMBERSHIP_REPORT 128 
 scalar_t__ IPPROTO_PIM ; 
 int br_ip4_multicast_add_group (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*) ; 
 int br_ip4_multicast_igmp3_report (struct net_bridge*,struct net_bridge_port*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ip4_multicast_leave_group (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  br_ip4_multicast_mrd_rcv (struct net_bridge*,struct net_bridge_port*,struct sk_buff*) ; 
 int /*<<< orphan*/  br_ip4_multicast_query (struct net_bridge*,struct net_bridge_port*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_multicast_count (struct net_bridge*,struct net_bridge_port*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_multicast_err_count (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_multicast_pim (struct net_bridge*,struct net_bridge_port*,struct sk_buff*) ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 struct igmphdr* igmp_hdr (struct sk_buff*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int ip_mc_check_igmp (struct sk_buff*) ; 
 scalar_t__ ipv4_is_all_snoopers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_is_local_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ pim_ipv4_all_pim_routers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int br_multicast_ipv4_rcv(struct net_bridge *br,
				 struct net_bridge_port *port,
				 struct sk_buff *skb,
				 u16 vid)
{
	const unsigned char *src;
	struct igmphdr *ih;
	int err;

	err = ip_mc_check_igmp(skb);

	if (err == -ENOMSG) {
		if (!ipv4_is_local_multicast(ip_hdr(skb)->daddr)) {
			BR_INPUT_SKB_CB(skb)->mrouters_only = 1;
		} else if (pim_ipv4_all_pim_routers(ip_hdr(skb)->daddr)) {
			if (ip_hdr(skb)->protocol == IPPROTO_PIM)
				br_multicast_pim(br, port, skb);
		} else if (ipv4_is_all_snoopers(ip_hdr(skb)->daddr)) {
			br_ip4_multicast_mrd_rcv(br, port, skb);
		}

		return 0;
	} else if (err < 0) {
		br_multicast_err_count(br, port, skb->protocol);
		return err;
	}

	ih = igmp_hdr(skb);
	src = eth_hdr(skb)->h_source;
	BR_INPUT_SKB_CB(skb)->igmp = ih->type;

	switch (ih->type) {
	case IGMP_HOST_MEMBERSHIP_REPORT:
	case IGMPV2_HOST_MEMBERSHIP_REPORT:
		BR_INPUT_SKB_CB(skb)->mrouters_only = 1;
		err = br_ip4_multicast_add_group(br, port, ih->group, vid, src);
		break;
	case IGMPV3_HOST_MEMBERSHIP_REPORT:
		err = br_ip4_multicast_igmp3_report(br, port, skb, vid);
		break;
	case IGMP_HOST_MEMBERSHIP_QUERY:
		br_ip4_multicast_query(br, port, skb, vid);
		break;
	case IGMP_HOST_LEAVE_MESSAGE:
		br_ip4_multicast_leave_group(br, port, ih->group, vid, src);
		break;
	}

	br_multicast_count(br, port, skb, BR_INPUT_SKB_CB(skb)->igmp,
			   BR_MCAST_DIR_RX);

	return err;
}