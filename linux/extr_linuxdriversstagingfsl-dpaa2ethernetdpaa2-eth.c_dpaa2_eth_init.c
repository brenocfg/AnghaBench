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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct net_device {int features; int hw_features; int /*<<< orphan*/  priv_flags; } ;
struct TYPE_2__ {int options; } ;
struct dpaa2_eth_priv {TYPE_1__ dpni_attrs; } ;

/* Variables and functions */
 int DPNI_OPT_NO_MAC_FILTER ; 
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dpaa2_eth_init(struct net_device *net_dev)
{
	u64 supported = 0;
	u64 not_supported = 0;
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	u32 options = priv->dpni_attrs.options;

	/* Capabilities listing */
	supported |= IFF_LIVE_ADDR_CHANGE;

	if (options & DPNI_OPT_NO_MAC_FILTER)
		not_supported |= IFF_UNICAST_FLT;
	else
		supported |= IFF_UNICAST_FLT;

	net_dev->priv_flags |= supported;
	net_dev->priv_flags &= ~not_supported;

	/* Features */
	net_dev->features = NETIF_F_RXCSUM |
			    NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			    NETIF_F_SG | NETIF_F_HIGHDMA |
			    NETIF_F_LLTX;
	net_dev->hw_features = net_dev->features;

	return 0;
}