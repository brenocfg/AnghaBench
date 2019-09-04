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
struct sk_buff {int dummy; } ;
struct hsr_port {TYPE_2__* dev; } ;
struct hsr_frame_info {int /*<<< orphan*/  node_src; TYPE_1__* port_rcv; } ;
struct TYPE_6__ {int /*<<< orphan*/  h_source; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ HSR_PT_MASTER ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 TYPE_3__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsr_addr_subst_dest (int /*<<< orphan*/ ,struct sk_buff*,struct hsr_port*) ; 

__attribute__((used)) static int hsr_xmit(struct sk_buff *skb, struct hsr_port *port,
		    struct hsr_frame_info *frame)
{
	if (frame->port_rcv->type == HSR_PT_MASTER) {
		hsr_addr_subst_dest(frame->node_src, skb, port);

		/* Address substitution (IEC62439-3 pp 26, 50): replace mac
		 * address of outgoing frame with that of the outgoing slave's.
		 */
		ether_addr_copy(eth_hdr(skb)->h_source, port->dev->dev_addr);
	}
	return dev_queue_xmit(skb);
}