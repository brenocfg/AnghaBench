#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_2__* dev; int /*<<< orphan*/  priority; int /*<<< orphan*/  protocol; } ;
struct net_bridge_port {TYPE_2__* dev; TYPE_1__* br; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  group_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  LLC_PDU_CMD ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_U ; 
 scalar_t__ LLC_RESERVE ; 
 int /*<<< orphan*/  LLC_SAP_BSPAN ; 
 int /*<<< orphan*/  NFPROTO_BRIDGE ; 
 int /*<<< orphan*/  NF_BR_LOCAL_OUT ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_PRIO_CONTROL ; 
 int /*<<< orphan*/  __skb_put_data (struct sk_buff*,unsigned char const*,int) ; 
 int /*<<< orphan*/  br_send_bpdu_finish ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_net (TYPE_2__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_mac_hdr_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_header_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_init_as_ui_cmd (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void br_send_bpdu(struct net_bridge_port *p,
			 const unsigned char *data, int length)
{
	struct sk_buff *skb;

	skb = dev_alloc_skb(length+LLC_RESERVE);
	if (!skb)
		return;

	skb->dev = p->dev;
	skb->protocol = htons(ETH_P_802_2);
	skb->priority = TC_PRIO_CONTROL;

	skb_reserve(skb, LLC_RESERVE);
	__skb_put_data(skb, data, length);

	llc_pdu_header_init(skb, LLC_PDU_TYPE_U, LLC_SAP_BSPAN,
			    LLC_SAP_BSPAN, LLC_PDU_CMD);
	llc_pdu_init_as_ui_cmd(skb);

	llc_mac_hdr_init(skb, p->dev->dev_addr, p->br->group_addr);

	skb_reset_mac_header(skb);

	NF_HOOK(NFPROTO_BRIDGE, NF_BR_LOCAL_OUT,
		dev_net(p->dev), NULL, skb, NULL, skb->dev,
		br_send_bpdu_finish);
}