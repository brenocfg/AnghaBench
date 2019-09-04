#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sxgbe_priv_data {int /*<<< orphan*/  ioaddr; TYPE_2__* hw; scalar_t__ eee_enabled; struct net_device* dev; } ;
struct net_device {TYPE_3__* phydev; } ;
struct TYPE_6__ {int /*<<< orphan*/  link; } ;
struct TYPE_5__ {TYPE_1__* mac; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_eee_pls ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sxgbe_eee_adjust(const struct sxgbe_priv_data *priv)
{
	struct net_device *ndev = priv->dev;

	/* When the EEE has been already initialised we have to
	 * modify the PLS bit in the LPI ctrl & status reg according
	 * to the PHY link status. For this reason.
	 */
	if (priv->eee_enabled)
		priv->hw->mac->set_eee_pls(priv->ioaddr, ndev->phydev->link);
}