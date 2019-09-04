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
typedef  int u32 ;
typedef  int u16 ;
struct r8152 {scalar_t__ version; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BMCR_PDOWN ; 
 int D3_CLK_GATED_EN ; 
 int GPHY_STS_MSK ; 
 int LED_MODE_MASK ; 
 int MCU_CLK_RATIO ; 
 int MCU_CLK_RATIO_MASK ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  MCU_TYPE_USB ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PFM_PWM_SWITCH ; 
 int /*<<< orphan*/  PLA_GPHY_INTR_IMR ; 
 int /*<<< orphan*/  PLA_LED_FEATURE ; 
 int /*<<< orphan*/  PLA_MAC_PWR_CTRL ; 
 int /*<<< orphan*/  PLA_PHY_PWR ; 
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 scalar_t__ RTL_VER_01 ; 
 int RX_AGG_DISABLE ; 
 int RX_ZERO_EN ; 
 int SPDWN_LINKCHG_MSK ; 
 int SPDWN_RXDV_MSK ; 
 int SPEED_DOWN_MSK ; 
 int TX_10M_IDLE_EN ; 
 int /*<<< orphan*/  USB_USB_CTRL ; 
 int ocp_read_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8152_aldps_en (struct r8152*,int) ; 
 int r8152_mdio_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152_mdio_write (struct r8152*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8152_power_cut_en (struct r8152*,int) ; 
 int /*<<< orphan*/  rtl_tally_reset (struct r8152*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r8152b_init(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	r8152_aldps_en(tp, false);

	if (tp->version == RTL_VER_01) {
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE);
		ocp_data &= ~LED_MODE_MASK;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE, ocp_data);
	}

	r8152_power_cut_en(tp, false);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= TX_10M_IDLE_EN | PFM_PWM_SWITCH;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);
	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL);
	ocp_data &= ~MCU_CLK_RATIO_MASK;
	ocp_data |= MCU_CLK_RATIO | D3_CLK_GATED_EN;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL, ocp_data);
	ocp_data = GPHY_STS_MSK | SPEED_DOWN_MSK |
		   SPDWN_RXDV_MSK | SPDWN_LINKCHG_MSK;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_GPHY_INTR_IMR, ocp_data);

	rtl_tally_reset(tp);

	/* enable rx aggregation */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);
}