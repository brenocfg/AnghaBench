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
struct switchdev_trans {int dummy; } ;
struct switchdev_obj_port_mdb {int /*<<< orphan*/  addr; } ;
struct net_device {int dummy; } ;
struct ethsw_port_priv {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int dev_mc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int ethsw_port_fdb_add_mc (struct ethsw_port_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethsw_port_fdb_del_mc (struct ethsw_port_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ port_lookup_address (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

__attribute__((used)) static int port_mdb_add(struct net_device *netdev,
			const struct switchdev_obj_port_mdb *mdb,
			struct switchdev_trans *trans)
{
	struct ethsw_port_priv *port_priv = netdev_priv(netdev);
	int err;

	if (switchdev_trans_ph_prepare(trans))
		return 0;

	/* Check if address is already set on this port */
	if (port_lookup_address(netdev, 0, mdb->addr))
		return -EEXIST;

	err = ethsw_port_fdb_add_mc(port_priv, mdb->addr);
	if (err)
		return err;

	err = dev_mc_add(netdev, mdb->addr);
	if (err) {
		netdev_err(netdev, "dev_mc_add err %d\n", err);
		ethsw_port_fdb_del_mc(port_priv, mdb->addr);
	}

	return err;
}