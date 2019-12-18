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
struct mii_bus {int /*<<< orphan*/  (* write ) (struct mii_bus*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_RESET ; 
 int BMCR_SPEED1000 ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mynet_n750_mdio_fixup(struct mii_bus *bus)
{
	int i;

	for (i = 0; i < 5; i++)
		bus->write(bus, i, MII_BMCR,
			   (BMCR_RESET | BMCR_ANENABLE | BMCR_SPEED1000));

	mdelay(1000);
}