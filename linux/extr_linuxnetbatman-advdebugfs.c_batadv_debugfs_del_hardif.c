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
struct net {int dummy; } ;
struct batadv_hard_iface {int /*<<< orphan*/ * debug_dir; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 scalar_t__ batadv_debugfs ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 struct net init_net ; 

void batadv_debugfs_del_hardif(struct batadv_hard_iface *hard_iface)
{
	struct net *net = dev_net(hard_iface->net_dev);

	if (net != &init_net)
		return;

	if (batadv_debugfs) {
		debugfs_remove_recursive(hard_iface->debug_dir);
		hard_iface->debug_dir = NULL;
	}
}