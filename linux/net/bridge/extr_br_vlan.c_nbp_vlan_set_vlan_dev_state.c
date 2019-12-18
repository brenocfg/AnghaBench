#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct net_bridge_port {TYPE_1__* br; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_VLAN_BRIDGE_BINDING ; 
 int /*<<< orphan*/  br_opt_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct net_device* br_vlan_get_upper_bind_vlan_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_vlan_set_vlan_dev_state (TYPE_1__*,struct net_device*) ; 

__attribute__((used)) static void nbp_vlan_set_vlan_dev_state(struct net_bridge_port *p, u16 vid)
{
	struct net_device *vlan_dev;

	if (!br_opt_get(p->br, BROPT_VLAN_BRIDGE_BINDING))
		return;

	vlan_dev = br_vlan_get_upper_bind_vlan_dev(p->br->dev, vid);
	if (vlan_dev)
		br_vlan_set_vlan_dev_state(p->br, vlan_dev);
}