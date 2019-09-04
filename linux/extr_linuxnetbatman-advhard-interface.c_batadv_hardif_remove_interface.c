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
struct batadv_hard_iface {scalar_t__ if_status; int /*<<< orphan*/  hardif_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BATADV_IF_CLEANUP_KEEP ; 
 scalar_t__ BATADV_IF_NOT_IN_USE ; 
 scalar_t__ BATADV_IF_TO_BE_REMOVED ; 
 int /*<<< orphan*/  batadv_debugfs_del_hardif (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_hardif_disable_interface (struct batadv_hard_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_sysfs_del_hardif (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_hardif_remove_interface(struct batadv_hard_iface *hard_iface)
{
	ASSERT_RTNL();

	/* first deactivate interface */
	if (hard_iface->if_status != BATADV_IF_NOT_IN_USE)
		batadv_hardif_disable_interface(hard_iface,
						BATADV_IF_CLEANUP_KEEP);

	if (hard_iface->if_status != BATADV_IF_NOT_IN_USE)
		return;

	hard_iface->if_status = BATADV_IF_TO_BE_REMOVED;
	batadv_debugfs_del_hardif(hard_iface);
	batadv_sysfs_del_hardif(&hard_iface->hardif_obj);
	batadv_hardif_put(hard_iface);
}