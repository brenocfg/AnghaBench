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
struct r8152 {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EEE_CLKDIV_EN ; 
 int EN_10M_CLKDIV ; 
 int EN_EEE_1000 ; 
 int EN_EEE_CMODE ; 
 int /*<<< orphan*/  GREEN_ETHERNET ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  MCU_TYPE_USB ; 
 int MDIO_EEE_1000T ; 
 int MDIO_EEE_100TX ; 
 int OCP_ADC_IOFFSET ; 
 int OCP_DOWN_SPEED ; 
 int OCP_EEE_ADV ; 
 int OCP_NCTL_CFG ; 
 int OCP_POWER_CFG ; 
 int OCP_SYSCLK_CFG ; 
 int PFM_PWM_SWITCH ; 
 int PGA_RETURN_EN ; 
 int /*<<< orphan*/  PHY_RESET ; 
 int /*<<< orphan*/  PLA_PHY_PWR ; 
 int R_TUNE_EN ; 
 int SAW_CNT_1MS_MASK ; 
 int /*<<< orphan*/  SRAM_GREEN_CFG ; 
 int UPS_FLAGS_250M_CKDIV ; 
 int UPS_FLAGS_EEE_CMOD_LV_EN ; 
 int UPS_FLAGS_EEE_PLLOFF_GIGA ; 
 int UPS_FLAGS_EN_10M_CKDIV ; 
 int UPS_FLAGS_EN_EEE_CKDIV ; 
 int /*<<< orphan*/  USB_UPS_CFG ; 
 int clk_div_expo (int) ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_reg_read (struct r8152*,int) ; 
 int /*<<< orphan*/  ocp_reg_write (struct r8152*,int,int) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int r8152_efuse_read (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_patch_request (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u2p3en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153b_aldps_en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153b_eee_en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153b_enable_fc (struct r8152*) ; 
 int /*<<< orphan*/  r8153b_green_en (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8153b_ups_flags_w1w0 (struct r8152*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sram_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sram_write (struct r8152*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r8153b_hw_phy_cfg(struct r8152 *tp)
{
	u32 ocp_data, ups_flags = 0;
	u16 data;

	/* disable ALDPS before updating the PHY parameters */
	r8153b_aldps_en(tp, false);

	/* disable EEE before updating the PHY parameters */
	r8153b_eee_en(tp, false);
	ocp_reg_write(tp, OCP_EEE_ADV, 0);

	r8153b_green_en(tp, test_bit(GREEN_ETHERNET, &tp->flags));

	data = sram_read(tp, SRAM_GREEN_CFG);
	data |= R_TUNE_EN;
	sram_write(tp, SRAM_GREEN_CFG, data);
	data = ocp_reg_read(tp, OCP_NCTL_CFG);
	data |= PGA_RETURN_EN;
	ocp_reg_write(tp, OCP_NCTL_CFG, data);

	/* ADC Bias Calibration:
	 * read efuse offset 0x7d to get a 17-bit data. Remove the dummy/fake
	 * bit (bit3) to rebuild the real 16-bit data. Write the data to the
	 * ADC ioffset.
	 */
	ocp_data = r8152_efuse_read(tp, 0x7d);
	data = (u16)(((ocp_data & 0x1fff0) >> 1) | (ocp_data & 0x7));
	if (data != 0xffff)
		ocp_reg_write(tp, OCP_ADC_IOFFSET, data);

	/* ups mode tx-link-pulse timing adjustment:
	 * rg_saw_cnt = OCP reg 0xC426 Bit[13:0]
	 * swr_cnt_1ms_ini = 16000000 / rg_saw_cnt
	 */
	ocp_data = ocp_reg_read(tp, 0xc426);
	ocp_data &= 0x3fff;
	if (ocp_data) {
		u32 swr_cnt_1ms_ini;

		swr_cnt_1ms_ini = (16000000 / ocp_data) & SAW_CNT_1MS_MASK;
		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_UPS_CFG);
		ocp_data = (ocp_data & ~SAW_CNT_1MS_MASK) | swr_cnt_1ms_ini;
		ocp_write_word(tp, MCU_TYPE_USB, USB_UPS_CFG, ocp_data);
	}

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

	/* Advnace EEE */
	if (!r8153_patch_request(tp, true)) {
		data = ocp_reg_read(tp, OCP_POWER_CFG);
		data |= EEE_CLKDIV_EN;
		ocp_reg_write(tp, OCP_POWER_CFG, data);

		data = ocp_reg_read(tp, OCP_DOWN_SPEED);
		data |= EN_EEE_CMODE | EN_EEE_1000 | EN_10M_CLKDIV;
		ocp_reg_write(tp, OCP_DOWN_SPEED, data);

		ocp_reg_write(tp, OCP_SYSCLK_CFG, 0);
		ocp_reg_write(tp, OCP_SYSCLK_CFG, clk_div_expo(5));

		ups_flags |= UPS_FLAGS_EN_10M_CKDIV | UPS_FLAGS_250M_CKDIV |
			     UPS_FLAGS_EN_EEE_CKDIV | UPS_FLAGS_EEE_CMOD_LV_EN |
			     UPS_FLAGS_EEE_PLLOFF_GIGA;

		r8153_patch_request(tp, false);
	}

	r8153b_ups_flags_w1w0(tp, ups_flags, 0);

	r8153b_eee_en(tp, true);
	ocp_reg_write(tp, OCP_EEE_ADV, MDIO_EEE_1000T | MDIO_EEE_100TX);

	r8153b_aldps_en(tp, true);
	r8153b_enable_fc(tp);
	r8153_u2p3en(tp, true);

	set_bit(PHY_RESET, &tp->flags);
}