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
typedef  int u16 ;
struct TYPE_2__ {int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 int MAX_205x_RCAL_WAITLOOPS ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int RADIO_2056_SYN ; 
 int RADIO_2056_SYN_PLL_MAST2 ; 
 int RADIO_2056_SYN_RCAL_CODE_OUT ; 
 int RADIO_2056_SYN_RCAL_MASTER ; 
 int /*<<< orphan*/  RADIO_2057_BANDGAP_RCAL_TRIM ; 
 int /*<<< orphan*/  RADIO_2057_IQTEST_SEL_PU ; 
 int /*<<< orphan*/  RADIO_2057_RCAL_CONFIG ; 
 int RADIO_2057_RCAL_STATUS ; 
 int /*<<< orphan*/  RADIO_2057_TEMPSENSE_CONFIG ; 
 int /*<<< orphan*/  RADIO_2057v7_IQTEST_SEL_PU2 ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int read_radio_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static u16 wlc_phy_radio205x_rcal(struct brcms_phy *pi)
{
	u16 rcal_reg = 0;
	int i;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {

		if (pi->pubpi.radiorev == 5) {

			and_phy_reg(pi, 0x342, ~(0x1 << 1));

			udelay(10);

			mod_radio_reg(pi, RADIO_2057_IQTEST_SEL_PU, 0x1, 0x1);
			mod_radio_reg(pi, RADIO_2057v7_IQTEST_SEL_PU2, 0x2,
				      0x1);
		}
		mod_radio_reg(pi, RADIO_2057_RCAL_CONFIG, 0x1, 0x1);

		udelay(10);

		mod_radio_reg(pi, RADIO_2057_RCAL_CONFIG, 0x3, 0x3);

		for (i = 0; i < MAX_205x_RCAL_WAITLOOPS; i++) {
			rcal_reg = read_radio_reg(pi, RADIO_2057_RCAL_STATUS);
			if (rcal_reg & 0x1)
				break;

			udelay(100);
		}

		if (WARN(i == MAX_205x_RCAL_WAITLOOPS,
			 "HW error: radio calib2"))
			return 0;

		mod_radio_reg(pi, RADIO_2057_RCAL_CONFIG, 0x2, 0x0);

		rcal_reg = read_radio_reg(pi, RADIO_2057_RCAL_STATUS) & 0x3e;

		mod_radio_reg(pi, RADIO_2057_RCAL_CONFIG, 0x1, 0x0);
		if (pi->pubpi.radiorev == 5) {

			mod_radio_reg(pi, RADIO_2057_IQTEST_SEL_PU, 0x1, 0x0);
			mod_radio_reg(pi, RADIO_2057v7_IQTEST_SEL_PU2, 0x2,
				      0x0);
		}

		if ((pi->pubpi.radiorev <= 4) || (pi->pubpi.radiorev == 6)) {

			mod_radio_reg(pi, RADIO_2057_TEMPSENSE_CONFIG, 0x3c,
				      rcal_reg);
			mod_radio_reg(pi, RADIO_2057_BANDGAP_RCAL_TRIM, 0xf0,
				      rcal_reg << 2);
		}

	} else if (NREV_IS(pi->pubpi.phy_rev, 3)) {
		u16 savereg;

		savereg =
			read_radio_reg(
				pi,
				RADIO_2056_SYN_PLL_MAST2 |
				RADIO_2056_SYN);
		write_radio_reg(pi, RADIO_2056_SYN_PLL_MAST2 | RADIO_2056_SYN,
				savereg | 0x7);
		udelay(10);

		write_radio_reg(pi, RADIO_2056_SYN_RCAL_MASTER | RADIO_2056_SYN,
				0x1);
		udelay(10);

		write_radio_reg(pi, RADIO_2056_SYN_RCAL_MASTER | RADIO_2056_SYN,
				0x9);

		for (i = 0; i < MAX_205x_RCAL_WAITLOOPS; i++) {
			rcal_reg = read_radio_reg(
				pi,
				RADIO_2056_SYN_RCAL_CODE_OUT |
				RADIO_2056_SYN);
			if (rcal_reg & 0x80)
				break;

			udelay(100);
		}

		if (WARN(i == MAX_205x_RCAL_WAITLOOPS,
			 "HW error: radio calib3"))
			return 0;

		write_radio_reg(pi, RADIO_2056_SYN_RCAL_MASTER | RADIO_2056_SYN,
				0x1);

		rcal_reg =
			read_radio_reg(pi,
				       RADIO_2056_SYN_RCAL_CODE_OUT |
				       RADIO_2056_SYN);

		write_radio_reg(pi, RADIO_2056_SYN_RCAL_MASTER | RADIO_2056_SYN,
				0x0);

		write_radio_reg(pi, RADIO_2056_SYN_PLL_MAST2 | RADIO_2056_SYN,
				savereg);

		return rcal_reg & 0x1f;
	}
	return rcal_reg & 0x3e;
}