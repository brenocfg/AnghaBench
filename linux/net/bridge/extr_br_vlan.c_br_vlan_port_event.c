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
struct net_bridge_port {int /*<<< orphan*/  br; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_VLAN_BRIDGE_BINDING ; 
#define  NETDEV_CHANGE 130 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  br_opt_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_vlan_set_all_vlan_dev_state (struct net_bridge_port*) ; 

void br_vlan_port_event(struct net_bridge_port *p, unsigned long event)
{
	if (!br_opt_get(p->br, BROPT_VLAN_BRIDGE_BINDING))
		return;

	switch (event) {
	case NETDEV_CHANGE:
	case NETDEV_DOWN:
	case NETDEV_UP:
		br_vlan_set_all_vlan_dev_state(p);
		break;
	}
}