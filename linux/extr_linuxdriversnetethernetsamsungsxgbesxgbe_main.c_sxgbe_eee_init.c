#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  expires; } ;
struct TYPE_8__ {scalar_t__ eee; } ;
struct sxgbe_priv_data {int eee_active; int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  ioaddr; TYPE_2__* hw; TYPE_4__ eee_ctrl_timer; TYPE_3__ hw_cap; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;
struct TYPE_7__ {TYPE_1__* mac; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_eee_timer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SXGBE_DEFAULT_LPI_TIMER ; 
 int /*<<< orphan*/  SXGBE_LPI_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  eee_timer ; 
 scalar_t__ phy_init_eee (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sxgbe_eee_ctrl_timer ; 
 int /*<<< orphan*/  timer_setup (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool sxgbe_eee_init(struct sxgbe_priv_data * const priv)
{
	struct net_device *ndev = priv->dev;
	bool ret = false;

	/* MAC core supports the EEE feature. */
	if (priv->hw_cap.eee) {
		/* Check if the PHY supports EEE */
		if (phy_init_eee(ndev->phydev, 1))
			return false;

		priv->eee_active = 1;
		timer_setup(&priv->eee_ctrl_timer, sxgbe_eee_ctrl_timer, 0);
		priv->eee_ctrl_timer.expires = SXGBE_LPI_TIMER(eee_timer);
		add_timer(&priv->eee_ctrl_timer);

		priv->hw->mac->set_eee_timer(priv->ioaddr,
					     SXGBE_DEFAULT_LPI_TIMER,
					     priv->tx_lpi_timer);

		pr_info("Energy-Efficient Ethernet initialized\n");

		ret = true;
	}

	return ret;
}