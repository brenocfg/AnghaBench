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
struct batadv_hard_iface {scalar_t__ if_status; int /*<<< orphan*/  soft_iface; TYPE_1__* net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BATADV_IF_ACTIVE ; 
 scalar_t__ BATADV_IF_INACTIVE ; 
 scalar_t__ BATADV_IF_TO_BE_ACTIVATED ; 
 int /*<<< orphan*/  batadv_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_update_min_mtu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
batadv_hardif_deactivate_interface(struct batadv_hard_iface *hard_iface)
{
	if (hard_iface->if_status != BATADV_IF_ACTIVE &&
	    hard_iface->if_status != BATADV_IF_TO_BE_ACTIVATED)
		return;

	hard_iface->if_status = BATADV_IF_INACTIVE;

	batadv_info(hard_iface->soft_iface, "Interface deactivated: %s\n",
		    hard_iface->net_dev->name);

	batadv_update_min_mtu(hard_iface->soft_iface);
}