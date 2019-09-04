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
struct mxs_phy {int port_id; int /*<<< orphan*/  regmap_anatop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANADIG_USB1_VBUS_DET_STAT ; 
 int /*<<< orphan*/  ANADIG_USB2_VBUS_DET_STAT ; 
 unsigned int BM_ANADIG_USB1_VBUS_DET_STAT_VBUS_VALID ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static bool mxs_phy_get_vbus_status(struct mxs_phy *mxs_phy)
{
	unsigned int vbus_value = 0;

	if (!mxs_phy->regmap_anatop)
		return false;

	if (mxs_phy->port_id == 0)
		regmap_read(mxs_phy->regmap_anatop,
			ANADIG_USB1_VBUS_DET_STAT,
			&vbus_value);
	else if (mxs_phy->port_id == 1)
		regmap_read(mxs_phy->regmap_anatop,
			ANADIG_USB2_VBUS_DET_STAT,
			&vbus_value);

	if (vbus_value & BM_ANADIG_USB1_VBUS_DET_STAT_VBUS_VALID)
		return true;
	else
		return false;
}