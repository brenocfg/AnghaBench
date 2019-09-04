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
struct brcms_phy {TYPE_1__ pubpi; void** tx_rx_cal_radio_saveregs; int /*<<< orphan*/  radio_chanspec; int /*<<< orphan*/  internal_tx_iqlo_cal_tapoff_intpa_nphy; scalar_t__ use_int_tx_iqlo_cal_nphy; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IQCAL_IDAC ; 
 int /*<<< orphan*/  IQCAL_VCM_HG ; 
 int NPHY_BandControl_currentBand ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int PHY_CORE_0 ; 
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 int RADIO_2055_CORE1_TXRF_IQCAL1 ; 
 int RADIO_2055_CORE1_TXRF_IQCAL2 ; 
 int /*<<< orphan*/  RADIO_2055_CORE1_TX_BB_MXGM ; 
 int RADIO_2055_CORE2_TXRF_IQCAL1 ; 
 int RADIO_2055_CORE2_TXRF_IQCAL2 ; 
 int /*<<< orphan*/  RADIO_2055_CORE2_TX_BB_MXGM ; 
 int RADIO_2055_PWRDET_RXTX_CORE1 ; 
 int RADIO_2055_PWRDET_RXTX_CORE2 ; 
 int RADIO_2056_TX0 ; 
 int RADIO_2056_TX1 ; 
 int RADIO_2056_TX_IQCAL_IDAC ; 
 int RADIO_2056_TX_IQCAL_VCM_HG ; 
 int RADIO_2056_TX_TSSIA ; 
 int RADIO_2056_TX_TSSIG ; 
 int RADIO_2056_TX_TSSI_MISC1 ; 
 int RADIO_2056_TX_TSSI_MISC2 ; 
 int RADIO_2056_TX_TSSI_MISC3 ; 
 int RADIO_2056_TX_TSSI_VCM ; 
 int RADIO_2056_TX_TX_AMP_DET ; 
 int RADIO_2056_TX_TX_SSI_MASTER ; 
 int RADIO_2056_TX_TX_SSI_MUX ; 
 int /*<<< orphan*/  RADIO_2057 ; 
 void* READ_RADIO_REG3 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSSIA ; 
 int /*<<< orphan*/  TSSIG ; 
 int /*<<< orphan*/  TSSI_MISC1 ; 
 int /*<<< orphan*/  TSSI_VCM ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  TX_SSI_MASTER ; 
 int /*<<< orphan*/  TX_SSI_MUX ; 
 int /*<<< orphan*/  WRITE_RADIO_REG3 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  and_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  or_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 void* read_radio_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_txcal_radio_setup_nphy(struct brcms_phy *pi)
{
	u16 jtag_core, core;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {

		for (core = 0; core <= 1; core++) {

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 0] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						TX_SSI_MASTER);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 1] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						IQCAL_VCM_HG);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 2] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						IQCAL_IDAC);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 3] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						TSSI_VCM);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 4] = 0;

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 5] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						TX_SSI_MUX);

			if (pi->pubpi.radiorev != 5)
				pi->tx_rx_cal_radio_saveregs[(core * 11) + 6] =
					READ_RADIO_REG3(pi, RADIO_2057, TX,
							core,
							TSSIA);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 7] =
			       READ_RADIO_REG3(pi, RADIO_2057, TX, core, TSSIG);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 8] =
				READ_RADIO_REG3(pi, RADIO_2057, TX, core,
						TSSI_MISC1);

			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TX_SSI_MASTER, 0x0a);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 IQCAL_VCM_HG, 0x43);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 IQCAL_IDAC, 0x55);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TSSI_VCM, 0x00);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TSSIG, 0x00);
				if (pi->use_int_tx_iqlo_cal_nphy) {
					WRITE_RADIO_REG3(pi, RADIO_2057, TX,
							 core, TX_SSI_MUX, 0x4);
					if (!(pi->
					internal_tx_iqlo_cal_tapoff_intpa_nphy))
						WRITE_RADIO_REG3(pi, RADIO_2057,
								 TX, core,
								 TSSIA, 0x31);
					else
						WRITE_RADIO_REG3(pi, RADIO_2057,
								 TX, core,
								 TSSIA, 0x21);
				}
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TSSI_MISC1, 0x00);
			} else {
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TX_SSI_MASTER, 0x06);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 IQCAL_VCM_HG, 0x43);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 IQCAL_IDAC, 0x55);
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TSSI_VCM, 0x00);

				if (pi->pubpi.radiorev != 5)
					WRITE_RADIO_REG3(pi, RADIO_2057, TX,
							 core, TSSIA, 0x00);
				if (pi->use_int_tx_iqlo_cal_nphy) {
					WRITE_RADIO_REG3(pi, RADIO_2057, TX,
							 core, TX_SSI_MUX,
							 0x06);
					if (!(pi->
					internal_tx_iqlo_cal_tapoff_intpa_nphy))
						WRITE_RADIO_REG3(pi, RADIO_2057,
								 TX, core,
								 TSSIG, 0x31);
					else
						WRITE_RADIO_REG3(pi, RADIO_2057,
								 TX, core,
								 TSSIG, 0x21);
				}
				WRITE_RADIO_REG3(pi, RADIO_2057, TX, core,
						 TSSI_MISC1, 0x00);
			}
		}
	} else if (NREV_GE(pi->pubpi.phy_rev, 3)) {

		for (core = 0; core <= 1; core++) {
			jtag_core =
				(core ==
				 PHY_CORE_0) ? RADIO_2056_TX0 : RADIO_2056_TX1;

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 0] =
				read_radio_reg(pi,
					       RADIO_2056_TX_TX_SSI_MASTER |
					       jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 1] =
				read_radio_reg(pi,
					       RADIO_2056_TX_IQCAL_VCM_HG |
					       jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 2] =
				read_radio_reg(pi,
					       RADIO_2056_TX_IQCAL_IDAC |
					       jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 3] =
				read_radio_reg(
					pi,
					RADIO_2056_TX_TSSI_VCM |
					jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 4] =
				read_radio_reg(pi,
					       RADIO_2056_TX_TX_AMP_DET |
					       jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 5] =
				read_radio_reg(pi,
					       RADIO_2056_TX_TX_SSI_MUX |
					       jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 6] =
				read_radio_reg(pi,
					       RADIO_2056_TX_TSSIA | jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 7] =
				read_radio_reg(pi,
					       RADIO_2056_TX_TSSIG | jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 8] =
				read_radio_reg(pi,
					       RADIO_2056_TX_TSSI_MISC1 |
					       jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 9] =
				read_radio_reg(pi,
					       RADIO_2056_TX_TSSI_MISC2 |
					       jtag_core);

			pi->tx_rx_cal_radio_saveregs[(core * 11) + 10] =
				read_radio_reg(pi,
					       RADIO_2056_TX_TSSI_MISC3 |
					       jtag_core);

			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				write_radio_reg(pi,
						RADIO_2056_TX_TX_SSI_MASTER |
						jtag_core, 0x0a);
				write_radio_reg(pi,
						RADIO_2056_TX_IQCAL_VCM_HG |
						jtag_core, 0x40);
				write_radio_reg(pi,
						RADIO_2056_TX_IQCAL_IDAC |
						jtag_core, 0x55);
				write_radio_reg(pi,
						RADIO_2056_TX_TSSI_VCM |
						jtag_core, 0x00);
				write_radio_reg(pi,
						RADIO_2056_TX_TX_AMP_DET |
						jtag_core, 0x00);

				if (PHY_IPA(pi)) {
					write_radio_reg(
						pi,
						RADIO_2056_TX_TX_SSI_MUX
						| jtag_core, 0x4);
					write_radio_reg(pi,
							RADIO_2056_TX_TSSIA |
							jtag_core, 0x1);
				} else {
					write_radio_reg(
						pi,
						RADIO_2056_TX_TX_SSI_MUX
						| jtag_core, 0x00);
					write_radio_reg(pi,
							RADIO_2056_TX_TSSIA |
							jtag_core, 0x2f);
				}
				write_radio_reg(pi,
						RADIO_2056_TX_TSSIG | jtag_core,
						0x00);
				write_radio_reg(pi,
						RADIO_2056_TX_TSSI_MISC1 |
						jtag_core, 0x00);

				write_radio_reg(pi,
						RADIO_2056_TX_TSSI_MISC2 |
						jtag_core, 0x00);
				write_radio_reg(pi,
						RADIO_2056_TX_TSSI_MISC3 |
						jtag_core, 0x00);
			} else {
				write_radio_reg(pi,
						RADIO_2056_TX_TX_SSI_MASTER |
						jtag_core, 0x06);
				write_radio_reg(pi,
						RADIO_2056_TX_IQCAL_VCM_HG |
						jtag_core, 0x40);
				write_radio_reg(pi,
						RADIO_2056_TX_IQCAL_IDAC |
						jtag_core, 0x55);
				write_radio_reg(pi,
						RADIO_2056_TX_TSSI_VCM |
						jtag_core, 0x00);
				write_radio_reg(pi,
						RADIO_2056_TX_TX_AMP_DET |
						jtag_core, 0x00);
				write_radio_reg(pi,
						RADIO_2056_TX_TSSIA | jtag_core,
						0x00);

				if (PHY_IPA(pi)) {

					write_radio_reg(
						pi,
						RADIO_2056_TX_TX_SSI_MUX
						| jtag_core, 0x06);
					if (NREV_LT(pi->pubpi.phy_rev, 5))
						write_radio_reg(
							pi,
							RADIO_2056_TX_TSSIG
							| jtag_core,
							0x11);
					else
						write_radio_reg(
							pi,
							RADIO_2056_TX_TSSIG
							| jtag_core,
							0x1);
				} else {
					write_radio_reg(
						pi,
						RADIO_2056_TX_TX_SSI_MUX
						| jtag_core, 0x00);
					write_radio_reg(pi,
							RADIO_2056_TX_TSSIG |
							jtag_core, 0x20);
				}

				write_radio_reg(pi,
						RADIO_2056_TX_TSSI_MISC1 |
						jtag_core, 0x00);
				write_radio_reg(pi,
						RADIO_2056_TX_TSSI_MISC2 |
						jtag_core, 0x00);
				write_radio_reg(pi,
						RADIO_2056_TX_TSSI_MISC3 |
						jtag_core, 0x00);
			}
		}
	} else {

		pi->tx_rx_cal_radio_saveregs[0] =
			read_radio_reg(pi, RADIO_2055_CORE1_TXRF_IQCAL1);
		write_radio_reg(pi, RADIO_2055_CORE1_TXRF_IQCAL1, 0x29);
		pi->tx_rx_cal_radio_saveregs[1] =
			read_radio_reg(pi, RADIO_2055_CORE1_TXRF_IQCAL2);
		write_radio_reg(pi, RADIO_2055_CORE1_TXRF_IQCAL2, 0x54);

		pi->tx_rx_cal_radio_saveregs[2] =
			read_radio_reg(pi, RADIO_2055_CORE2_TXRF_IQCAL1);
		write_radio_reg(pi, RADIO_2055_CORE2_TXRF_IQCAL1, 0x29);
		pi->tx_rx_cal_radio_saveregs[3] =
			read_radio_reg(pi, RADIO_2055_CORE2_TXRF_IQCAL2);
		write_radio_reg(pi, RADIO_2055_CORE2_TXRF_IQCAL2, 0x54);

		pi->tx_rx_cal_radio_saveregs[4] =
			read_radio_reg(pi, RADIO_2055_PWRDET_RXTX_CORE1);
		pi->tx_rx_cal_radio_saveregs[5] =
			read_radio_reg(pi, RADIO_2055_PWRDET_RXTX_CORE2);

		if ((read_phy_reg(pi, 0x09) & NPHY_BandControl_currentBand) ==
		    0) {

			write_radio_reg(pi, RADIO_2055_PWRDET_RXTX_CORE1, 0x04);
			write_radio_reg(pi, RADIO_2055_PWRDET_RXTX_CORE2, 0x04);
		} else {

			write_radio_reg(pi, RADIO_2055_PWRDET_RXTX_CORE1, 0x20);
			write_radio_reg(pi, RADIO_2055_PWRDET_RXTX_CORE2, 0x20);
		}

		if (NREV_LT(pi->pubpi.phy_rev, 2)) {

			or_radio_reg(pi, RADIO_2055_CORE1_TX_BB_MXGM, 0x20);
			or_radio_reg(pi, RADIO_2055_CORE2_TX_BB_MXGM, 0x20);
		} else {

			and_radio_reg(pi, RADIO_2055_CORE1_TX_BB_MXGM, 0xdf);
			and_radio_reg(pi, RADIO_2055_CORE2_TX_BB_MXGM, 0xdf);
		}
	}
}