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
struct rtl_priv {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct phy_device {TYPE_1__ mdio; struct rtl_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NRESTART ; 
 int /*<<< orphan*/  NWAY ; 
 int /*<<< orphan*/  RTL_PORT_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rtl8306_config_aneg(struct phy_device *pdev)
{
	struct rtl_priv *priv = pdev->priv;

	/* Only for WAN */
	if (pdev->mdio.addr == 0)
		return 0;

	/* Restart autonegotiation */
	rtl_set(&priv->dev, RTL_PORT_REG(4, NWAY), 1);
	rtl_set(&priv->dev, RTL_PORT_REG(4, NRESTART), 1);

	return 0;
}