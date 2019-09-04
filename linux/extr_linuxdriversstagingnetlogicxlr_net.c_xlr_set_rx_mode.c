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
typedef  int u32 ;
struct xlr_net_priv {int /*<<< orphan*/  base_addr; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int O_MAC_FILTER_CONFIG__ALL_MCAST_EN ; 
 int O_MAC_FILTER_CONFIG__ALL_UCAST_EN ; 
 int O_MAC_FILTER_CONFIG__BROADCAST_EN ; 
 int O_MAC_FILTER_CONFIG__PAUSE_FRAME_EN ; 
 int /*<<< orphan*/  R_MAC_FILTER_CONFIG ; 
 struct xlr_net_priv* netdev_priv (struct net_device*) ; 
 int xlr_nae_rdreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_nae_wreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlr_set_rx_mode(struct net_device *ndev)
{
	struct xlr_net_priv *priv = netdev_priv(ndev);
	u32 regval;

	regval = xlr_nae_rdreg(priv->base_addr, R_MAC_FILTER_CONFIG);

	if (ndev->flags & IFF_PROMISC) {
		regval |= (1 << O_MAC_FILTER_CONFIG__BROADCAST_EN) |
		(1 << O_MAC_FILTER_CONFIG__PAUSE_FRAME_EN) |
		(1 << O_MAC_FILTER_CONFIG__ALL_MCAST_EN) |
		(1 << O_MAC_FILTER_CONFIG__ALL_UCAST_EN);
	} else {
		regval &= ~((1 << O_MAC_FILTER_CONFIG__PAUSE_FRAME_EN) |
		(1 << O_MAC_FILTER_CONFIG__ALL_UCAST_EN));
	}

	xlr_nae_wreg(priv->base_addr, R_MAC_FILTER_CONFIG, regval);
}