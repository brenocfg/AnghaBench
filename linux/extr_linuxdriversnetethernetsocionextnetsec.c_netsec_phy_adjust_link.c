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
struct netsec_priv {int dummy; } ;
struct net_device {TYPE_1__* phydev; } ;
struct TYPE_2__ {scalar_t__ link; } ;

/* Variables and functions */
 struct netsec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netsec_start_gmac (struct netsec_priv*) ; 
 int /*<<< orphan*/  netsec_stop_gmac (struct netsec_priv*) ; 
 int /*<<< orphan*/  phy_print_status (TYPE_1__*) ; 

__attribute__((used)) static void netsec_phy_adjust_link(struct net_device *ndev)
{
	struct netsec_priv *priv = netdev_priv(ndev);

	if (ndev->phydev->link)
		netsec_start_gmac(priv);
	else
		netsec_stop_gmac(priv);

	phy_print_status(ndev->phydev);
}