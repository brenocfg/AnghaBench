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
struct sk_buff {scalar_t__ data; } ;
struct neighbour_cb {int dummy; } ;
struct TYPE_3__ {int icmp6_code; int icmp6_type; } ;
struct nd_msg {TYPE_1__ icmph; } ;
struct TYPE_4__ {int hop_limit; } ;

/* Variables and functions */
#define  NDISC_NEIGHBOUR_ADVERTISEMENT 132 
#define  NDISC_NEIGHBOUR_SOLICITATION 131 
#define  NDISC_REDIRECT 130 
#define  NDISC_ROUTER_ADVERTISEMENT 129 
#define  NDISC_ROUTER_SOLICITATION 128 
 int /*<<< orphan*/  ND_PRINTK (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NEIGH_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,scalar_t__) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndisc_recv_na (struct sk_buff*) ; 
 int /*<<< orphan*/  ndisc_recv_ns (struct sk_buff*) ; 
 int /*<<< orphan*/  ndisc_recv_rs (struct sk_buff*) ; 
 int /*<<< orphan*/  ndisc_redirect_rcv (struct sk_buff*) ; 
 int /*<<< orphan*/  ndisc_router_discovery (struct sk_buff*) ; 
 scalar_t__ ndisc_suppress_frag_ndisc (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  warn ; 

int ndisc_rcv(struct sk_buff *skb)
{
	struct nd_msg *msg;

	if (ndisc_suppress_frag_ndisc(skb))
		return 0;

	if (skb_linearize(skb))
		return 0;

	msg = (struct nd_msg *)skb_transport_header(skb);

	__skb_push(skb, skb->data - skb_transport_header(skb));

	if (ipv6_hdr(skb)->hop_limit != 255) {
		ND_PRINTK(2, warn, "NDISC: invalid hop-limit: %d\n",
			  ipv6_hdr(skb)->hop_limit);
		return 0;
	}

	if (msg->icmph.icmp6_code != 0) {
		ND_PRINTK(2, warn, "NDISC: invalid ICMPv6 code: %d\n",
			  msg->icmph.icmp6_code);
		return 0;
	}

	switch (msg->icmph.icmp6_type) {
	case NDISC_NEIGHBOUR_SOLICITATION:
		memset(NEIGH_CB(skb), 0, sizeof(struct neighbour_cb));
		ndisc_recv_ns(skb);
		break;

	case NDISC_NEIGHBOUR_ADVERTISEMENT:
		ndisc_recv_na(skb);
		break;

	case NDISC_ROUTER_SOLICITATION:
		ndisc_recv_rs(skb);
		break;

	case NDISC_ROUTER_ADVERTISEMENT:
		ndisc_router_discovery(skb);
		break;

	case NDISC_REDIRECT:
		ndisc_redirect_rcv(skb);
		break;
	}

	return 0;
}