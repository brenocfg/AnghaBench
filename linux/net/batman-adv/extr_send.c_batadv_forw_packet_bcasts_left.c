#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct batadv_hard_iface {unsigned int num_bcasts; } ;
struct batadv_forw_packet {int /*<<< orphan*/  skb; } ;
struct TYPE_2__ {unsigned int num_bcasts; } ;

/* Variables and functions */
 unsigned int BATADV_NUM_BCASTS_MAX ; 
 TYPE_1__* BATADV_SKB_CB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
batadv_forw_packet_bcasts_left(struct batadv_forw_packet *forw_packet,
			       struct batadv_hard_iface *hard_iface)
{
	unsigned int max;

	if (hard_iface)
		max = hard_iface->num_bcasts;
	else
		max = BATADV_NUM_BCASTS_MAX;

	return BATADV_SKB_CB(forw_packet->skb)->num_bcasts < max;
}