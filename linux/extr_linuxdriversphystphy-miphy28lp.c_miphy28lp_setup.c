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
struct miphy28lp_phy {int /*<<< orphan*/  miphy_rst; int /*<<< orphan*/ * syscfg_reg; scalar_t__ osc_force_ext; struct miphy28lp_dev* phydev; } ;
struct miphy28lp_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIPHY_CTRL_MASK ; 
 int /*<<< orphan*/  MIPHY_OSC_FORCE_EXT ; 
 size_t SYSCFG_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int miphy_osc_is_ready (struct miphy28lp_phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int miphy28lp_setup(struct miphy28lp_phy *miphy_phy, u32 miphy_val)
{
	int err;
	struct miphy28lp_dev *miphy_dev = miphy_phy->phydev;

	if (!miphy_phy->syscfg_reg[SYSCFG_CTRL])
		return -EINVAL;

	err = reset_control_assert(miphy_phy->miphy_rst);
	if (err) {
		dev_err(miphy_dev->dev, "unable to bring out of miphy reset\n");
		return err;
	}

	if (miphy_phy->osc_force_ext)
		miphy_val |= MIPHY_OSC_FORCE_EXT;

	regmap_update_bits(miphy_dev->regmap,
			   miphy_phy->syscfg_reg[SYSCFG_CTRL],
			   MIPHY_CTRL_MASK, miphy_val);

	err = reset_control_deassert(miphy_phy->miphy_rst);
	if (err) {
		dev_err(miphy_dev->dev, "unable to bring out of miphy reset\n");
		return err;
	}

	return miphy_osc_is_ready(miphy_phy);
}