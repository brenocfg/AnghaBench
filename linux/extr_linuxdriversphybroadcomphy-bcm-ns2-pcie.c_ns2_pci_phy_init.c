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
struct phy {int dummy; } ;
struct mdio_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_ADDR_REG_OFFSET ; 
 int /*<<< orphan*/  PLL_AFE1_100MHZ_BLK ; 
 int /*<<< orphan*/  PLL_CLK_AMP_2P05V ; 
 int /*<<< orphan*/  PLL_CLK_AMP_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mdiobus_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdio_device* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int ns2_pci_phy_init(struct phy *p)
{
	struct mdio_device *mdiodev = phy_get_drvdata(p);
	int rc;

	/* select the AFE 100MHz block page */
	rc = mdiobus_write(mdiodev->bus, mdiodev->addr,
			   BLK_ADDR_REG_OFFSET, PLL_AFE1_100MHZ_BLK);
	if (rc)
		goto err;

	/* set the 100 MHz reference clock amplitude to 2.05 v */
	rc = mdiobus_write(mdiodev->bus, mdiodev->addr,
			   PLL_CLK_AMP_OFFSET, PLL_CLK_AMP_2P05V);
	if (rc)
		goto err;

	return 0;

err:
	dev_err(&mdiodev->dev, "Error %d writing to phy\n", rc);
	return rc;
}