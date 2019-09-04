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
struct hsr_port {TYPE_2__* dev; } ;
struct hsr_frame_info {struct sk_buff* skb_std; struct sk_buff* skb_hsr; int /*<<< orphan*/  sequence_nr; int /*<<< orphan*/  node_src; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_4__ {TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ hsr_fill_frame_info (struct hsr_frame_info*,struct sk_buff*,struct hsr_port*) ; 
 int /*<<< orphan*/  hsr_forward_do (struct hsr_frame_info*) ; 
 int /*<<< orphan*/  hsr_register_frame_in (int /*<<< orphan*/ ,struct hsr_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 

void hsr_forward_skb(struct sk_buff *skb, struct hsr_port *port)
{
	struct hsr_frame_info frame;

	if (skb_mac_header(skb) != skb->data) {
		WARN_ONCE(1, "%s:%d: Malformed frame (port_src %s)\n",
			  __FILE__, __LINE__, port->dev->name);
		goto out_drop;
	}

	if (hsr_fill_frame_info(&frame, skb, port) < 0)
		goto out_drop;
	hsr_register_frame_in(frame.node_src, port, frame.sequence_nr);
	hsr_forward_do(&frame);

	if (frame.skb_hsr != NULL)
		kfree_skb(frame.skb_hsr);
	if (frame.skb_std != NULL)
		kfree_skb(frame.skb_std);
	return;

out_drop:
	port->dev->stats.tx_dropped++;
	kfree_skb(skb);
}