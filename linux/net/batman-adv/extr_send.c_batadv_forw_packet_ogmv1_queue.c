#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct batadv_priv {int /*<<< orphan*/  forw_bat_list; int /*<<< orphan*/  forw_bat_list_lock; } ;
struct batadv_forw_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_forw_packet_queue (struct batadv_forw_packet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

void batadv_forw_packet_ogmv1_queue(struct batadv_priv *bat_priv,
				    struct batadv_forw_packet *forw_packet,
				    unsigned long send_time)
{
	batadv_forw_packet_queue(forw_packet, &bat_priv->forw_bat_list_lock,
				 &bat_priv->forw_bat_list, send_time);
}