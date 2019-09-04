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
struct mdio_if_info {int (* mdio_read ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;int prtad; int mmds; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MDIO_DEVS1 ; 
 int /*<<< orphan*/  MDIO_DEVS2 ; 
 int /*<<< orphan*/  MDIO_STAT2 ; 
 int MDIO_STAT2_DEVPRST ; 
 int MDIO_STAT2_DEVPRST_VAL ; 
 int stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int mdio45_probe(struct mdio_if_info *mdio, int prtad)
{
	int mmd, stat2, devs1, devs2;

	/* Assume PHY must have at least one of PMA/PMD, WIS, PCS, PHY
	 * XS or DTE XS; give up if none is present. */
	for (mmd = 1; mmd <= 5; mmd++) {
		/* Is this MMD present? */
		stat2 = mdio->mdio_read(mdio->dev, prtad, mmd, MDIO_STAT2);
		if (stat2 < 0 ||
		    (stat2 & MDIO_STAT2_DEVPRST) != MDIO_STAT2_DEVPRST_VAL)
			continue;

		/* It should tell us about all the other MMDs */
		devs1 = mdio->mdio_read(mdio->dev, prtad, mmd, MDIO_DEVS1);
		devs2 = mdio->mdio_read(mdio->dev, prtad, mmd, MDIO_DEVS2);
		if (devs1 < 0 || devs2 < 0)
			continue;

		mdio->prtad = prtad;
		mdio->mmds = devs1 | (devs2 << 16);
		return 0;
	}

	return -ENODEV;
}