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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID0 ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID1 ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID2 ; 
#define  NPHY_REV7_RfctrlOverride_cmd_rx_pu 132 
#define  NPHY_REV7_RfctrlOverride_cmd_rxgain 131 
#define  NPHY_REV7_RfctrlOverride_cmd_rxrf_pu 130 
#define  NPHY_REV7_RfctrlOverride_cmd_tx_pu 129 
#define  NPHY_REV7_RfctrlOverride_cmd_txgain 128 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy_rev7 (struct brcms_phy*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wlc_phy_rfctrl_override_1tomany_nphy(struct brcms_phy *pi, u16 cmd, u16 value,
				     u8 core_mask, u8 off)
{
	u16 rfmxgain = 0, lpfgain = 0;
	u16 tgain = 0;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {

		switch (cmd) {
		case NPHY_REV7_RfctrlOverride_cmd_rxrf_pu:
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 5),
				value, core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 4), value,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 3), value,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			break;
		case NPHY_REV7_RfctrlOverride_cmd_rx_pu:
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 2),
				value, core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 1), value,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 0), value,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 1), value,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID2);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 11), 0,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			break;
		case NPHY_REV7_RfctrlOverride_cmd_tx_pu:
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 2),
				value, core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID0);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 1), value,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 0), value,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID2);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 2), value,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID2);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 11), 1,
				core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			break;
		case NPHY_REV7_RfctrlOverride_cmd_rxgain:
			rfmxgain = value & 0x000ff;
			lpfgain = value & 0x0ff00;
			lpfgain = lpfgain >> 8;

			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 11),
				rfmxgain, core_mask,
				off,
				NPHY_REV7_RFCTRLOVERRIDE_ID0);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x3 << 13),
				lpfgain, core_mask,
				off,
				NPHY_REV7_RFCTRLOVERRIDE_ID0);
			break;
		case NPHY_REV7_RfctrlOverride_cmd_txgain:
			tgain = value & 0x7fff;
			lpfgain = value & 0x8000;
			lpfgain = lpfgain >> 14;

			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 12),
				tgain, core_mask, off,
				NPHY_REV7_RFCTRLOVERRIDE_ID0);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 13),
				lpfgain, core_mask,
				off,
				NPHY_REV7_RFCTRLOVERRIDE_ID0);
			break;
		}
	}
}