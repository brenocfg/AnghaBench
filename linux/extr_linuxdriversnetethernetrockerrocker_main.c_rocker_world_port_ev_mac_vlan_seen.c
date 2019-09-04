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
struct rocker_world_ops {int (* port_ev_mac_vlan_seen ) (struct rocker_port*,unsigned char const*,int /*<<< orphan*/ ) ;} ;
struct rocker_port {TYPE_1__* rocker; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {struct rocker_world_ops* wops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct rocker_port*,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rocker_world_port_ev_mac_vlan_seen(struct rocker_port *rocker_port,
					      const unsigned char *addr,
					      __be16 vlan_id)
{
	struct rocker_world_ops *wops = rocker_port->rocker->wops;

	if (!wops->port_ev_mac_vlan_seen)
		return -EOPNOTSUPP;
	return wops->port_ev_mac_vlan_seen(rocker_port, addr, vlan_id);
}