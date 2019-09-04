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
struct batadv_ogm_packet {int /*<<< orphan*/  prev_sender; int /*<<< orphan*/  orig; } ;
struct TYPE_3__ {unsigned char* ogm_buff; } ;
struct batadv_hard_iface {TYPE_2__* net_dev; TYPE_1__ bat_iv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_iv_ogm_iface_update_mac(struct batadv_hard_iface *hard_iface)
{
	struct batadv_ogm_packet *batadv_ogm_packet;
	unsigned char *ogm_buff = hard_iface->bat_iv.ogm_buff;

	batadv_ogm_packet = (struct batadv_ogm_packet *)ogm_buff;
	ether_addr_copy(batadv_ogm_packet->orig,
			hard_iface->net_dev->dev_addr);
	ether_addr_copy(batadv_ogm_packet->prev_sender,
			hard_iface->net_dev->dev_addr);
}