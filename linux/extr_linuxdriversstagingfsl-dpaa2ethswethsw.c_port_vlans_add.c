#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct switchdev_trans {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  orig_dev; } ;
struct switchdev_obj_port_vlan {int vid_begin; int vid_end; int /*<<< orphan*/  flags; TYPE_1__ obj; } ;
struct net_device {int dummy; } ;
struct ethsw_port_priv {TYPE_2__* ethsw_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vlans; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETHSW_VLAN_GLOBAL ; 
 int ethsw_add_vlan (TYPE_2__*,int) ; 
 int ethsw_port_add_vlan (struct ethsw_port_priv*,int,int /*<<< orphan*/ ) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_is_bridge_master (int /*<<< orphan*/ ) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

__attribute__((used)) static int port_vlans_add(struct net_device *netdev,
			  const struct switchdev_obj_port_vlan *vlan,
			  struct switchdev_trans *trans)
{
	struct ethsw_port_priv *port_priv = netdev_priv(netdev);
	int vid, err;

	if (netif_is_bridge_master(vlan->obj.orig_dev))
		return -EOPNOTSUPP;

	if (switchdev_trans_ph_prepare(trans))
		return 0;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++) {
		if (!port_priv->ethsw_data->vlans[vid]) {
			/* this is a new VLAN */
			err = ethsw_add_vlan(port_priv->ethsw_data, vid);
			if (err)
				return err;

			port_priv->ethsw_data->vlans[vid] |= ETHSW_VLAN_GLOBAL;
		}
		err = ethsw_port_add_vlan(port_priv, vid, vlan->flags);
		if (err)
			break;
	}

	return err;
}