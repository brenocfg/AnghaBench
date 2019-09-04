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
struct u3phy_banks {scalar_t__ phya; scalar_t__ phyd; scalar_t__ chip; scalar_t__ spllc; } ;
struct u2phy_banks {scalar_t__ com; scalar_t__ fmreg; scalar_t__ misc; } ;
struct mtk_tphy {int /*<<< orphan*/  dev; } ;
struct mtk_phy_instance {int type; scalar_t__ port_base; struct u3phy_banks u3_banks; struct u2phy_banks u2_banks; } ;

/* Variables and functions */
#define  PHY_TYPE_PCIE 130 
#define  PHY_TYPE_USB2 129 
#define  PHY_TYPE_USB3 128 
 scalar_t__ SSUSB_SIFSLV_V2_CHIP ; 
 scalar_t__ SSUSB_SIFSLV_V2_MISC ; 
 scalar_t__ SSUSB_SIFSLV_V2_SPLLC ; 
 scalar_t__ SSUSB_SIFSLV_V2_U2FREQ ; 
 scalar_t__ SSUSB_SIFSLV_V2_U2PHY_COM ; 
 scalar_t__ SSUSB_SIFSLV_V2_U3PHYA ; 
 scalar_t__ SSUSB_SIFSLV_V2_U3PHYD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void phy_v2_banks_init(struct mtk_tphy *tphy,
			      struct mtk_phy_instance *instance)
{
	struct u2phy_banks *u2_banks = &instance->u2_banks;
	struct u3phy_banks *u3_banks = &instance->u3_banks;

	switch (instance->type) {
	case PHY_TYPE_USB2:
		u2_banks->misc = instance->port_base + SSUSB_SIFSLV_V2_MISC;
		u2_banks->fmreg = instance->port_base + SSUSB_SIFSLV_V2_U2FREQ;
		u2_banks->com = instance->port_base + SSUSB_SIFSLV_V2_U2PHY_COM;
		break;
	case PHY_TYPE_USB3:
	case PHY_TYPE_PCIE:
		u3_banks->spllc = instance->port_base + SSUSB_SIFSLV_V2_SPLLC;
		u3_banks->chip = instance->port_base + SSUSB_SIFSLV_V2_CHIP;
		u3_banks->phyd = instance->port_base + SSUSB_SIFSLV_V2_U3PHYD;
		u3_banks->phya = instance->port_base + SSUSB_SIFSLV_V2_U3PHYA;
		break;
	default:
		dev_err(tphy->dev, "incompatible PHY type\n");
		return;
	}
}