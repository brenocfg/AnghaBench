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
struct batadv_forw_packet {int /*<<< orphan*/  skb; } ;
struct TYPE_2__ {scalar_t__ num_bcasts; } ;

/* Variables and functions */
 TYPE_1__* BATADV_SKB_CB (int /*<<< orphan*/ ) ; 

bool batadv_forw_packet_is_rebroadcast(struct batadv_forw_packet *forw_packet)
{
	return BATADV_SKB_CB(forw_packet->skb)->num_bcasts > 0;
}