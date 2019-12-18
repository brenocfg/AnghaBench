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
struct net_device {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_hardif_min_mtu (struct net_device*) ; 
 int /*<<< orphan*/  batadv_tt_local_resize_to_mtu (struct net_device*) ; 

void batadv_update_min_mtu(struct net_device *soft_iface)
{
	soft_iface->mtu = batadv_hardif_min_mtu(soft_iface);

	/* Check if the local translate table should be cleaned up to match a
	 * new (and smaller) MTU.
	 */
	batadv_tt_local_resize_to_mtu(soft_iface);
}