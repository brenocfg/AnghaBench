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
typedef  int u32 ;
struct phy_device {TYPE_1__* drv; } ;
struct TYPE_2__ {int phy_id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  VILLA_GLOBAL_CHIP_ID_LSB ; 
 int /*<<< orphan*/  VILLA_GLOBAL_CHIP_ID_MSB ; 
 int cortina_read_reg (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_err (struct phy_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cortina_probe(struct phy_device *phydev)
{
	u32 phy_id = 0;
	int id_lsb = 0, id_msb = 0;

	/* Read device id from phy registers. */
	id_lsb = cortina_read_reg(phydev, VILLA_GLOBAL_CHIP_ID_LSB);
	if (id_lsb < 0)
		return -ENXIO;

	phy_id = id_lsb << 16;

	id_msb = cortina_read_reg(phydev, VILLA_GLOBAL_CHIP_ID_MSB);
	if (id_msb < 0)
		return -ENXIO;

	phy_id |= id_msb;

	/* Make sure the device tree binding matched the driver with the
	 * right device.
	 */
	if (phy_id != phydev->drv->phy_id) {
		phydev_err(phydev, "Error matching phy with %s driver\n",
			   phydev->drv->name);
		return -ENODEV;
	}

	return 0;
}