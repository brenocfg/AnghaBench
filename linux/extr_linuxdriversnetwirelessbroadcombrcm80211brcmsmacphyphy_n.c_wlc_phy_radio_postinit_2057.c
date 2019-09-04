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
struct brcms_phy {scalar_t__ phy_init_por; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIO_2057_RFPLL_MASTER ; 
 int /*<<< orphan*/  RADIO_2057_RFPLL_MISC_CAL_RESETN ; 
 int /*<<< orphan*/  RADIO_2057_XTALPUOVR_PINCTRL ; 
 int /*<<< orphan*/  RADIO_2057_XTAL_CONFIG2 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wlc_phy_radio2057_rccal (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_radio205x_rcal (struct brcms_phy*) ; 

__attribute__((used)) static void wlc_phy_radio_postinit_2057(struct brcms_phy *pi)
{

	mod_radio_reg(pi, RADIO_2057_XTALPUOVR_PINCTRL, 0x1, 0x1);

	mod_radio_reg(pi, RADIO_2057_RFPLL_MISC_CAL_RESETN, 0x78, 0x78);
	mod_radio_reg(pi, RADIO_2057_XTAL_CONFIG2, 0x80, 0x80);
	mdelay(2);
	mod_radio_reg(pi, RADIO_2057_RFPLL_MISC_CAL_RESETN, 0x78, 0x0);
	mod_radio_reg(pi, RADIO_2057_XTAL_CONFIG2, 0x80, 0x0);

	if (pi->phy_init_por) {
		wlc_phy_radio205x_rcal(pi);
		wlc_phy_radio2057_rccal(pi);
	}

	mod_radio_reg(pi, RADIO_2057_RFPLL_MASTER, 0x8, 0x0);
}