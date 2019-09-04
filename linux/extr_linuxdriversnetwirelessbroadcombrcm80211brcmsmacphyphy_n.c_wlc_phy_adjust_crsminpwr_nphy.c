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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int nphy_crsminpwr_adjusted; int* nphy_crsminpwr; int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; } ;

/* Variables and functions */
 int CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_adjust_crsminpwr_nphy(struct brcms_phy *pi, u8 minpwr)
{
	u16 regval;

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		if ((CHSPEC_CHANNEL(pi->radio_chanspec) == 11) &&
		    CHSPEC_IS40(pi->radio_chanspec)) {
			if (!pi->nphy_crsminpwr_adjusted) {
				regval = read_phy_reg(pi, 0x27d);
				pi->nphy_crsminpwr[0] = regval & 0xff;
				regval &= 0xff00;
				regval |= (u16) minpwr;
				write_phy_reg(pi, 0x27d, regval);

				regval = read_phy_reg(pi, 0x280);
				pi->nphy_crsminpwr[1] = regval & 0xff;
				regval &= 0xff00;
				regval |= (u16) minpwr;
				write_phy_reg(pi, 0x280, regval);

				regval = read_phy_reg(pi, 0x283);
				pi->nphy_crsminpwr[2] = regval & 0xff;
				regval &= 0xff00;
				regval |= (u16) minpwr;
				write_phy_reg(pi, 0x283, regval);

				pi->nphy_crsminpwr_adjusted = true;
			}
		} else {
			if (pi->nphy_crsminpwr_adjusted) {
				regval = read_phy_reg(pi, 0x27d);
				regval &= 0xff00;
				regval |= pi->nphy_crsminpwr[0];
				write_phy_reg(pi, 0x27d, regval);

				regval = read_phy_reg(pi, 0x280);
				regval &= 0xff00;
				regval |= pi->nphy_crsminpwr[1];
				write_phy_reg(pi, 0x280, regval);

				regval = read_phy_reg(pi, 0x283);
				regval &= 0xff00;
				regval |= pi->nphy_crsminpwr[2];
				write_phy_reg(pi, 0x283, regval);

				pi->nphy_crsminpwr_adjusted = false;
			}
		}
	}
}