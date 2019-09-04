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
typedef  int u16 ;
struct r8152 {scalar_t__ version; int /*<<< orphan*/  coalesce; TYPE_1__* udev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int speed; } ;

/* Variables and functions */
 int ADC_EN ; 
 int AUTOLOAD_DONE ; 
 int BMCR_PDOWN ; 
 int CKADSEL_L ; 
 int /*<<< orphan*/  COALESCE_HIGH ; 
 int /*<<< orphan*/  COALESCE_SLOW ; 
 int /*<<< orphan*/  COALESCE_SUPER ; 
 int /*<<< orphan*/  DELL_TB_RX_AGG_BUG ; 
 int DYNAMIC_BURST ; 
 int ECM_ALDPS ; 
 int EN_EMI_L ; 
 int EP4_FULL_FC ; 
 int FIFO_EMPTY_1FB ; 
 int LED_MODE_MASK ; 
 int LPM_TIMER_500MS ; 
 int LPM_TIMER_500US ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  MCU_TYPE_USB ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  OCP_ADC_CFG ; 
 int /*<<< orphan*/  PHY_STAT_LAN_ON ; 
 int /*<<< orphan*/  PLA_BOOT_CTRL ; 
 int /*<<< orphan*/  PLA_DMY_REG0 ; 
 int /*<<< orphan*/  PLA_LED_FEATURE ; 
 int ROK_EXIT_LPM ; 
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 scalar_t__ RTL_VER_03 ; 
 scalar_t__ RTL_VER_04 ; 
 scalar_t__ RTL_VER_05 ; 
 scalar_t__ RTL_VER_06 ; 
 int RX_AGG_DISABLE ; 
 int RX_ZERO_EN ; 
 int SEL_RXIDLE ; 
 int SEN_VAL_MASK ; 
 int SEN_VAL_NORMAL ; 
 int TIMER11_EN ; 
 int USB2PHY_L1 ; 
 int USB2PHY_SUSPEND ; 
 int /*<<< orphan*/  USB_AFE_CTRL2 ; 
 int /*<<< orphan*/  USB_BURST_SIZE ; 
 int /*<<< orphan*/  USB_CONNECT_TIMER ; 
 int /*<<< orphan*/  USB_CSR_DUMMY1 ; 
 int /*<<< orphan*/  USB_CSR_DUMMY2 ; 
 int /*<<< orphan*/  USB_LPM_CTRL ; 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_SUPER 129 
#define  USB_SPEED_SUPER_PLUS 128 
 int /*<<< orphan*/  USB_SSPHYLINK2 ; 
 int /*<<< orphan*/  USB_USB2PHY ; 
 int /*<<< orphan*/  USB_USB_CTRL ; 
 int /*<<< orphan*/  USB_WDT11_CTRL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int ocp_read_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_reg_write (struct r8152*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pwd_dn_scale (int) ; 
 int pwd_dn_scale_mask ; 
 int r8152_mdio_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152_mdio_write (struct r8152*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8153_mac_clk_spd (struct r8152*,int) ; 
 int r8153_phy_status (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8153_power_cut_en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u1u2en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u2p3en (struct r8152*,int) ; 
 int /*<<< orphan*/  rtl_tally_reset (struct r8152*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_enable_lpm (TYPE_1__*) ; 

__attribute__((used)) static void r8153_init(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;
	int i;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153_u1u2en(tp, false);

	for (i = 0; i < 500; i++) {
		if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			break;
		msleep(20);
	}

	data = r8153_phy_status(tp, 0);

	if (tp->version == RTL_VER_03 || tp->version == RTL_VER_04 ||
	    tp->version == RTL_VER_05)
		ocp_reg_write(tp, OCP_ADC_CFG, CKADSEL_L | ADC_EN | EN_EMI_L);

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	if (tp->version == RTL_VER_04) {
		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_SSPHYLINK2);
		ocp_data &= ~pwd_dn_scale_mask;
		ocp_data |= pwd_dn_scale(96);
		ocp_write_word(tp, MCU_TYPE_USB, USB_SSPHYLINK2, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_USB2PHY);
		ocp_data |= USB2PHY_L1 | USB2PHY_SUSPEND;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_USB2PHY, ocp_data);
	} else if (tp->version == RTL_VER_05) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_DMY_REG0);
		ocp_data &= ~ECM_ALDPS;
		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_DMY_REG0, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1);
		if (ocp_read_word(tp, MCU_TYPE_USB, USB_BURST_SIZE) == 0)
			ocp_data &= ~DYNAMIC_BURST;
		else
			ocp_data |= DYNAMIC_BURST;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1, ocp_data);
	} else if (tp->version == RTL_VER_06) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1);
		if (ocp_read_word(tp, MCU_TYPE_USB, USB_BURST_SIZE) == 0)
			ocp_data &= ~DYNAMIC_BURST;
		else
			ocp_data |= DYNAMIC_BURST;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1, ocp_data);
	}

	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY2);
	ocp_data |= EP4_FULL_FC;
	ocp_write_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY2, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_WDT11_CTRL);
	ocp_data &= ~TIMER11_EN;
	ocp_write_word(tp, MCU_TYPE_USB, USB_WDT11_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE);
	ocp_data &= ~LED_MODE_MASK;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE, ocp_data);

	ocp_data = FIFO_EMPTY_1FB | ROK_EXIT_LPM;
	if (tp->version == RTL_VER_04 && tp->udev->speed < USB_SPEED_SUPER)
		ocp_data |= LPM_TIMER_500MS;
	else
		ocp_data |= LPM_TIMER_500US;
	ocp_write_byte(tp, MCU_TYPE_USB, USB_LPM_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_AFE_CTRL2);
	ocp_data &= ~SEN_VAL_MASK;
	ocp_data |= SEN_VAL_NORMAL | SEL_RXIDLE;
	ocp_write_word(tp, MCU_TYPE_USB, USB_AFE_CTRL2, ocp_data);

	ocp_write_word(tp, MCU_TYPE_USB, USB_CONNECT_TIMER, 0x0001);

	r8153_power_cut_en(tp, false);
	r8153_u1u2en(tp, true);
	r8153_mac_clk_spd(tp, false);
	usb_enable_lpm(tp->udev);

	/* rx aggregation */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	if (test_bit(DELL_TB_RX_AGG_BUG, &tp->flags))
		ocp_data |= RX_AGG_DISABLE;

	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	rtl_tally_reset(tp);

	switch (tp->udev->speed) {
	case USB_SPEED_SUPER:
	case USB_SPEED_SUPER_PLUS:
		tp->coalesce = COALESCE_SUPER;
		break;
	case USB_SPEED_HIGH:
		tp->coalesce = COALESCE_HIGH;
		break;
	default:
		tp->coalesce = COALESCE_SLOW;
		break;
	}
}