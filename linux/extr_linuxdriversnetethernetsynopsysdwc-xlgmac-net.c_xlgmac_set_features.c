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
struct xlgmac_hw_ops {int (* enable_rss ) (struct xlgmac_pdata*) ;int (* disable_rss ) (struct xlgmac_pdata*) ;int /*<<< orphan*/  (* disable_rx_vlan_filtering ) (struct xlgmac_pdata*) ;int /*<<< orphan*/  (* enable_rx_vlan_filtering ) (struct xlgmac_pdata*) ;int /*<<< orphan*/  (* disable_rx_vlan_stripping ) (struct xlgmac_pdata*) ;int /*<<< orphan*/  (* enable_rx_vlan_stripping ) (struct xlgmac_pdata*) ;int /*<<< orphan*/  (* disable_rx_csum ) (struct xlgmac_pdata*) ;int /*<<< orphan*/  (* enable_rx_csum ) (struct xlgmac_pdata*) ;} ;
struct xlgmac_pdata {int netdev_features; struct xlgmac_hw_ops hw_ops; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 struct xlgmac_pdata* netdev_priv (struct net_device*) ; 
 int stub1 (struct xlgmac_pdata*) ; 
 int stub2 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  stub3 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  stub4 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  stub5 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  stub6 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  stub7 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  stub8 (struct xlgmac_pdata*) ; 

__attribute__((used)) static int xlgmac_set_features(struct net_device *netdev,
			       netdev_features_t features)
{
	netdev_features_t rxhash, rxcsum, rxvlan, rxvlan_filter;
	struct xlgmac_pdata *pdata = netdev_priv(netdev);
	struct xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	int ret = 0;

	rxhash = pdata->netdev_features & NETIF_F_RXHASH;
	rxcsum = pdata->netdev_features & NETIF_F_RXCSUM;
	rxvlan = pdata->netdev_features & NETIF_F_HW_VLAN_CTAG_RX;
	rxvlan_filter = pdata->netdev_features & NETIF_F_HW_VLAN_CTAG_FILTER;

	if ((features & NETIF_F_RXHASH) && !rxhash)
		ret = hw_ops->enable_rss(pdata);
	else if (!(features & NETIF_F_RXHASH) && rxhash)
		ret = hw_ops->disable_rss(pdata);
	if (ret)
		return ret;

	if ((features & NETIF_F_RXCSUM) && !rxcsum)
		hw_ops->enable_rx_csum(pdata);
	else if (!(features & NETIF_F_RXCSUM) && rxcsum)
		hw_ops->disable_rx_csum(pdata);

	if ((features & NETIF_F_HW_VLAN_CTAG_RX) && !rxvlan)
		hw_ops->enable_rx_vlan_stripping(pdata);
	else if (!(features & NETIF_F_HW_VLAN_CTAG_RX) && rxvlan)
		hw_ops->disable_rx_vlan_stripping(pdata);

	if ((features & NETIF_F_HW_VLAN_CTAG_FILTER) && !rxvlan_filter)
		hw_ops->enable_rx_vlan_filtering(pdata);
	else if (!(features & NETIF_F_HW_VLAN_CTAG_FILTER) && rxvlan_filter)
		hw_ops->disable_rx_vlan_filtering(pdata);

	pdata->netdev_features = features;

	return 0;
}