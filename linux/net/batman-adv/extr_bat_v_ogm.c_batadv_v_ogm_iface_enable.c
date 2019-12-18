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
struct batadv_priv {int dummy; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_v_ogm_start_queue_timer (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_v_ogm_start_timer (struct batadv_priv*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 

int batadv_v_ogm_iface_enable(struct batadv_hard_iface *hard_iface)
{
	struct batadv_priv *bat_priv = netdev_priv(hard_iface->soft_iface);

	batadv_v_ogm_start_queue_timer(hard_iface);
	batadv_v_ogm_start_timer(bat_priv);

	return 0;
}