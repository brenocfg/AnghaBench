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
struct TYPE_3__ {struct sk_buff* elp_skb; } ;
struct batadv_hard_iface {TYPE_2__* net_dev; TYPE_1__ bat_v; } ;
struct batadv_elp_packet {int /*<<< orphan*/  orig; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void batadv_v_elp_iface_activate(struct batadv_hard_iface *primary_iface,
				 struct batadv_hard_iface *hard_iface)
{
	struct batadv_elp_packet *elp_packet;
	struct sk_buff *skb;

	if (!hard_iface->bat_v.elp_skb)
		return;

	skb = hard_iface->bat_v.elp_skb;
	elp_packet = (struct batadv_elp_packet *)skb->data;
	ether_addr_copy(elp_packet->orig,
			primary_iface->net_dev->dev_addr);
}