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
typedef  int u8 ;
typedef  int u16 ;
struct nphy_papd_restore_state {void** intpa_master; void** fbmix; void** vga_master; void** afeoverride; void** afectrl; void** atten; void** pwrup; } ;
struct TYPE_2__ {int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTPAA_MASTER ; 
 int /*<<< orphan*/  INTPAG_MASTER ; 
 int NPHY_PAPD_COMP_OFF ; 
 int NPHY_PAPD_COMP_ON ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID0 ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID1 ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID2 ; 
 int /*<<< orphan*/  NPHY_REV7_RfctrlOverride_cmd_tx_pu ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int PHY_CORE_0 ; 
 int /*<<< orphan*/  RADIO_2056 ; 
 int /*<<< orphan*/  RADIO_2057 ; 
 void* READ_RADIO_REG2 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* READ_RADIO_REG3 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  TXFBMIX_A ; 
 int /*<<< orphan*/  TXFBMIX_G ; 
 int /*<<< orphan*/  TXRXCOUPLE_2G_ATTEN ; 
 int /*<<< orphan*/  TXRXCOUPLE_2G_PWRUP ; 
 int /*<<< orphan*/  TXRXCOUPLE_5G_ATTEN ; 
 int /*<<< orphan*/  TXRXCOUPLE_5G_PWRUP ; 
 int /*<<< orphan*/  VGA_MASTER ; 
 int /*<<< orphan*/  WRITE_RADIO_REG2 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_RADIO_REG3 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 void* read_phy_reg (struct brcms_phy*,int) ; 
 int wlc_phy_read_lpf_bw_ctl_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_1tomany_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy (struct brcms_phy*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy_rev7 (struct brcms_phy*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_tx_tone_nphy (struct brcms_phy*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wlc_phy_papd_cal_setup_nphy(struct brcms_phy *pi,
			    struct nphy_papd_restore_state *state, u8 core)
{
	s32 tone_freq;
	u8 off_core;
	u16 mixgain = 0;

	off_core = core ^ 0x1;
	if (NREV_GE(pi->pubpi.phy_rev, 7)) {

		if (NREV_IS(pi->pubpi.phy_rev, 7)
		    || NREV_GE(pi->pubpi.phy_rev, 8))
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 7),
				wlc_phy_read_lpf_bw_ctl_nphy
					(pi,
					0), 0, 0,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);

		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			if (pi->pubpi.radiorev == 5)
				mixgain = (core == 0) ? 0x20 : 0x00;
			else if ((pi->pubpi.radiorev == 7)
				 || (pi->pubpi.radiorev == 8))
				mixgain = 0x00;
			else if ((pi->pubpi.radiorev <= 4)
				 || (pi->pubpi.radiorev == 6))
				mixgain = 0x00;
		} else {
			if ((pi->pubpi.radiorev == 4) ||
			    (pi->pubpi.radiorev == 6))
				mixgain = 0x50;
			else if ((pi->pubpi.radiorev == 3)
				 || (pi->pubpi.radiorev == 7)
				 || (pi->pubpi.radiorev == 8))
				mixgain = 0x0;
		}

		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 11),
						  mixgain, (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID0);

		wlc_phy_rfctrl_override_1tomany_nphy(
			pi,
			NPHY_REV7_RfctrlOverride_cmd_tx_pu,
			1, (1 << core), 0);
		wlc_phy_rfctrl_override_1tomany_nphy(
			pi,
			NPHY_REV7_RfctrlOverride_cmd_tx_pu,
			0, (1 << off_core), 0);

		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 3),
						  0, 0x3, 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID0);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 2), 1,
						  (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID1);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 0), 0,
						  (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID1);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 1), 1,
						  (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID2);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 8), 0,
						  (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID1);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 9), 1,
						  (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID1);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 10), 0,
						  (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID1);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 3), 1,
						  (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID1);

		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 5),
						  0, (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID1);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 4), 0,
						  (1 << core), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID1);

		state->afectrl[core] = read_phy_reg(pi, (core == PHY_CORE_0) ?
						    0xa6 : 0xa7);
		state->afeoverride[core] =
			read_phy_reg(pi, (core == PHY_CORE_0) ? 0x8f : 0xa5);
		state->afectrl[off_core] =
			read_phy_reg(pi, (core == PHY_CORE_0) ? 0xa7 : 0xa6);
		state->afeoverride[off_core] =
			read_phy_reg(pi, (core == PHY_CORE_0) ? 0xa5 : 0x8f);

		mod_phy_reg(pi, ((core == PHY_CORE_0) ? 0xa6 : 0xa7),
			    (0x1 << 2), 0);
		mod_phy_reg(pi, ((core == PHY_CORE_0) ? 0x8f :
				 0xa5), (0x1 << 2), (0x1 << 2));

		mod_phy_reg(pi, ((core == PHY_CORE_0) ? 0xa7 : 0xa6),
			    (0x1 << 2), (0x1 << 2));
		mod_phy_reg(pi, ((core == PHY_CORE_0) ? 0xa5 :
				 0x8f), (0x1 << 2), (0x1 << 2));

		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			state->pwrup[core] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						TXRXCOUPLE_2G_PWRUP);
			state->atten[core] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						TXRXCOUPLE_2G_ATTEN);
			state->pwrup[off_core] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, off_core,
						TXRXCOUPLE_2G_PWRUP);
			state->atten[off_core] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, off_core,
						TXRXCOUPLE_2G_ATTEN);

			WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
					 TXRXCOUPLE_2G_PWRUP, 0xc);

			if ((pi->pubpi.radiorev == 3) ||
			    (pi->pubpi.radiorev == 4) ||
			    (pi->pubpi.radiorev == 6))
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TXRXCOUPLE_2G_ATTEN, 0xf0);
			else if (pi->pubpi.radiorev == 5)
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TXRXCOUPLE_2G_ATTEN,
						 (core == 0) ? 0xf7 : 0xf2);
			else if ((pi->pubpi.radiorev == 7)
				 || (pi->pubpi.radiorev == 8))
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TXRXCOUPLE_2G_ATTEN, 0xf0);

			WRITE_RADIO_REG3(pi, RADIO_2057, TX, off_core,
					 TXRXCOUPLE_2G_PWRUP, 0x0);
			WRITE_RADIO_REG3(pi, RADIO_2057, TX, off_core,
					 TXRXCOUPLE_2G_ATTEN, 0xff);
		} else {
			state->pwrup[core] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						TXRXCOUPLE_5G_PWRUP);
			state->atten[core] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						TXRXCOUPLE_5G_ATTEN);
			state->pwrup[off_core] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, off_core,
						TXRXCOUPLE_5G_PWRUP);
			state->atten[off_core] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, off_core,
						TXRXCOUPLE_5G_ATTEN);

			WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
					 TXRXCOUPLE_5G_PWRUP, 0xc);

			if ((pi->pubpi.radiorev == 7)
			    || (pi->pubpi.radiorev == 8))
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TXRXCOUPLE_5G_ATTEN, 0xf4);

			else
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TXRXCOUPLE_5G_ATTEN, 0xf0);

			WRITE_RADIO_REG3(pi, RADIO_2057, TX, off_core,
					 TXRXCOUPLE_5G_PWRUP, 0x0);
			WRITE_RADIO_REG3(pi, RADIO_2057, TX, off_core,
					 TXRXCOUPLE_5G_ATTEN, 0xff);
		}

		tone_freq = 4000;

		wlc_phy_tx_tone_nphy(pi, tone_freq, 181, 0, 0, false);

		mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (NPHY_PAPD_COMP_ON) << 0);

		mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
			    0x2a4, (0x1 << 13), (1) << 13);

		mod_phy_reg(pi, (off_core == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (NPHY_PAPD_COMP_OFF) << 0);

		mod_phy_reg(pi, (off_core == PHY_CORE_0) ? 0x2a3 :
			    0x2a4, (0x1 << 13), (0) << 13);

	} else {

		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 12), 0, 0x3, 0);

		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 3), 1, 0, 0);

		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 0), 0, 0x3, 0);

		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 2), 1, 0x3, 0);
		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 1), 1, 0x3, 0);

		state->afectrl[core] = read_phy_reg(pi, (core == PHY_CORE_0) ?
						    0xa6 : 0xa7);
		state->afeoverride[core] =
			read_phy_reg(pi, (core == PHY_CORE_0) ? 0x8f : 0xa5);

		mod_phy_reg(pi, ((core == PHY_CORE_0) ? 0xa6 : 0xa7),
			    (0x1 << 0) | (0x1 << 1) | (0x1 << 2), 0);
		mod_phy_reg(pi, ((core == PHY_CORE_0) ? 0x8f :
				 0xa5),
			    (0x1 << 0) |
			    (0x1 << 1) |
			    (0x1 << 2), (0x1 << 0) | (0x1 << 1) | (0x1 << 2));

		state->vga_master[core] =
			READ_RADIO_REG2(pi, RADIO_2056, RX, core, VGA_MASTER);
		WRITE_RADIO_REG2(pi, RADIO_2056, RX, core, VGA_MASTER, 0x2b);
		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			state->fbmix[core] =
				READ_RADIO_REG2(pi, RADIO_2056, RX, core,
						TXFBMIX_G);
			state->intpa_master[core] =
				READ_RADIO_REG2(pi, RADIO_2056, TX, core,
						INTPAG_MASTER);

			WRITE_RADIO_REG2(pi, RADIO_2056, RX, core, TXFBMIX_G,
					 0x03);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 INTPAG_MASTER, 0x04);
		} else {
			state->fbmix[core] =
				READ_RADIO_REG2(pi, RADIO_2056, RX, core,
						TXFBMIX_A);
			state->intpa_master[core] =
				READ_RADIO_REG2(pi, RADIO_2056, TX, core,
						INTPAA_MASTER);

			WRITE_RADIO_REG2(pi, RADIO_2056, RX, core, TXFBMIX_A,
					 0x03);
			WRITE_RADIO_REG2(pi, RADIO_2056, TX, core,
					 INTPAA_MASTER, 0x04);

		}

		tone_freq = 4000;

		wlc_phy_tx_tone_nphy(pi, tone_freq, 181, 0, 0, false);

		mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (1) << 0);

		mod_phy_reg(pi, (off_core == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (0) << 0);

		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 3), 0, 0x3, 0);
	}
}