#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct hsr_port {TYPE_1__* hsr; } ;
struct hsr_frame_info {int is_vlan; struct hsr_port* port_rcv; int /*<<< orphan*/  sequence_nr; struct sk_buff* skb_hsr; struct sk_buff* skb_std; int /*<<< orphan*/  node_src; int /*<<< orphan*/  is_supervision; } ;
struct ethhdr {scalar_t__ h_proto; } ;
struct TYPE_3__ {int /*<<< orphan*/  seqnr_lock; int /*<<< orphan*/  sequence_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_HSR ; 
 int /*<<< orphan*/  ETH_P_PRP ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  check_local_dest (TYPE_1__*,struct sk_buff*,struct hsr_frame_info*) ; 
 int /*<<< orphan*/  hsr_get_node (struct hsr_port*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsr_get_skb_sequence_nr (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_supervision_frame (TYPE_1__*,struct sk_buff*) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hsr_fill_frame_info(struct hsr_frame_info *frame,
			       struct sk_buff *skb, struct hsr_port *port)
{
	struct ethhdr *ethhdr;
	unsigned long irqflags;

	frame->is_supervision = is_supervision_frame(port->hsr, skb);
	frame->node_src = hsr_get_node(port, skb, frame->is_supervision);
	if (!frame->node_src)
		return -1; /* Unknown node and !is_supervision, or no mem */

	ethhdr = (struct ethhdr *)skb_mac_header(skb);
	frame->is_vlan = false;
	if (ethhdr->h_proto == htons(ETH_P_8021Q)) {
		frame->is_vlan = true;
		/* FIXME: */
		WARN_ONCE(1, "HSR: VLAN not yet supported");
	}
	if (ethhdr->h_proto == htons(ETH_P_PRP) ||
	    ethhdr->h_proto == htons(ETH_P_HSR)) {
		frame->skb_std = NULL;
		frame->skb_hsr = skb;
		frame->sequence_nr = hsr_get_skb_sequence_nr(skb);
	} else {
		frame->skb_std = skb;
		frame->skb_hsr = NULL;
		/* Sequence nr for the master node */
		spin_lock_irqsave(&port->hsr->seqnr_lock, irqflags);
		frame->sequence_nr = port->hsr->sequence_nr;
		port->hsr->sequence_nr++;
		spin_unlock_irqrestore(&port->hsr->seqnr_lock, irqflags);
	}

	frame->port_rcv = port;
	check_local_dest(port->hsr, skb, frame);

	return 0;
}