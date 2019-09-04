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
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct ethsw_port_priv {size_t pvid; int /*<<< orphan*/  idx; int /*<<< orphan*/ * vlans; struct net_device* netdev; struct ethsw_core* ethsw_data; } ;
struct ethsw_core {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;
struct dpsw_tci_cfg {size_t vlan_id; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHSW_VLAN_PVID ; 
 int dpsw_if_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpsw_if_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dpsw_if_get_tci (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpsw_tci_cfg*) ; 
 int dpsw_if_set_tci (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpsw_tci_cfg*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int netif_oper_up (struct net_device*) ; 

__attribute__((used)) static int ethsw_port_set_pvid(struct ethsw_port_priv *port_priv, u16 pvid)
{
	struct ethsw_core *ethsw = port_priv->ethsw_data;
	struct net_device *netdev = port_priv->netdev;
	struct dpsw_tci_cfg tci_cfg = { 0 };
	bool is_oper;
	int err, ret;

	err = dpsw_if_get_tci(ethsw->mc_io, 0, ethsw->dpsw_handle,
			      port_priv->idx, &tci_cfg);
	if (err) {
		netdev_err(netdev, "dpsw_if_get_tci err %d\n", err);
		return err;
	}

	tci_cfg.vlan_id = pvid;

	/* Interface needs to be down to change PVID */
	is_oper = netif_oper_up(netdev);
	if (is_oper) {
		err = dpsw_if_disable(ethsw->mc_io, 0,
				      ethsw->dpsw_handle,
				      port_priv->idx);
		if (err) {
			netdev_err(netdev, "dpsw_if_disable err %d\n", err);
			return err;
		}
	}

	err = dpsw_if_set_tci(ethsw->mc_io, 0, ethsw->dpsw_handle,
			      port_priv->idx, &tci_cfg);
	if (err) {
		netdev_err(netdev, "dpsw_if_set_tci err %d\n", err);
		goto set_tci_error;
	}

	/* Delete previous PVID info and mark the new one */
	port_priv->vlans[port_priv->pvid] &= ~ETHSW_VLAN_PVID;
	port_priv->vlans[pvid] |= ETHSW_VLAN_PVID;
	port_priv->pvid = pvid;

set_tci_error:
	if (is_oper) {
		ret = dpsw_if_enable(ethsw->mc_io, 0,
				     ethsw->dpsw_handle,
				     port_priv->idx);
		if (ret) {
			netdev_err(netdev, "dpsw_if_enable err %d\n", ret);
			return ret;
		}
	}

	return err;
}