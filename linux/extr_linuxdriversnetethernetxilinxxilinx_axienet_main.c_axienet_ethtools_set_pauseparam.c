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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ rx_pause; scalar_t__ tx_pause; } ;
struct axienet_local {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  XAE_FCC_FCRX_MASK ; 
 int /*<<< orphan*/  XAE_FCC_FCTX_MASK ; 
 int /*<<< orphan*/  XAE_FCC_OFFSET ; 
 int /*<<< orphan*/  axienet_ior (struct axienet_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axienet_iow (struct axienet_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int
axienet_ethtools_set_pauseparam(struct net_device *ndev,
				struct ethtool_pauseparam *epauseparm)
{
	u32 regval = 0;
	struct axienet_local *lp = netdev_priv(ndev);

	if (netif_running(ndev)) {
		netdev_err(ndev,
			   "Please stop netif before applying configuration\n");
		return -EFAULT;
	}

	regval = axienet_ior(lp, XAE_FCC_OFFSET);
	if (epauseparm->tx_pause)
		regval |= XAE_FCC_FCTX_MASK;
	else
		regval &= ~XAE_FCC_FCTX_MASK;
	if (epauseparm->rx_pause)
		regval |= XAE_FCC_FCRX_MASK;
	else
		regval &= ~XAE_FCC_FCRX_MASK;
	axienet_iow(lp, XAE_FCC_OFFSET, regval);

	return 0;
}