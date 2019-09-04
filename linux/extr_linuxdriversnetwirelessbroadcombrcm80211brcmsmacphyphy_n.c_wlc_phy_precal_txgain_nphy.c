#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int* nphy_txcal_pwr_idx; int /*<<< orphan*/  nphy_txcal_bbmult; int /*<<< orphan*/  radio_chanspec; TYPE_2__ pubpi; TYPE_1__* sh; scalar_t__ use_int_tx_iqlo_cal_nphy; } ;
struct TYPE_3__ {int hw_phytxchain; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_cal_txgainctrl_nphy (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_phy_internal_cal_txgain_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlc_phy_txpwr_index_nphy (struct brcms_phy*,int,int,int) ; 

__attribute__((used)) static void wlc_phy_precal_txgain_nphy(struct brcms_phy *pi)
{
	bool save_bbmult = false;
	u8 txcal_index_2057_rev5n7 = 0;
	u8 txcal_index_2057_rev3n4n6 = 10;

	if (pi->use_int_tx_iqlo_cal_nphy) {
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			if ((pi->pubpi.radiorev == 3) ||
			    (pi->pubpi.radiorev == 4) ||
			    (pi->pubpi.radiorev == 6)) {

				pi->nphy_txcal_pwr_idx[0] =
					txcal_index_2057_rev3n4n6;
				pi->nphy_txcal_pwr_idx[1] =
					txcal_index_2057_rev3n4n6;
				wlc_phy_txpwr_index_nphy(
					pi, 3,
					txcal_index_2057_rev3n4n6,
					false);
			} else {

				pi->nphy_txcal_pwr_idx[0] =
					txcal_index_2057_rev5n7;
				pi->nphy_txcal_pwr_idx[1] =
					txcal_index_2057_rev5n7;
				wlc_phy_txpwr_index_nphy(
					pi, 3,
					txcal_index_2057_rev5n7,
					false);
			}
			save_bbmult = true;

		} else if (NREV_LT(pi->pubpi.phy_rev, 5)) {
			wlc_phy_cal_txgainctrl_nphy(pi, 11, false);
			if (pi->sh->hw_phytxchain != 3) {
				pi->nphy_txcal_pwr_idx[1] =
					pi->nphy_txcal_pwr_idx[0];
				wlc_phy_txpwr_index_nphy(pi, 3,
							 pi->
							 nphy_txcal_pwr_idx[0],
							 true);
				save_bbmult = true;
			}

		} else if (NREV_IS(pi->pubpi.phy_rev, 5)) {
			if (PHY_IPA(pi)) {
				if (CHSPEC_IS2G(pi->radio_chanspec)) {
					wlc_phy_cal_txgainctrl_nphy(pi, 12,
								    false);
				} else {
					pi->nphy_txcal_pwr_idx[0] = 80;
					pi->nphy_txcal_pwr_idx[1] = 80;
					wlc_phy_txpwr_index_nphy(pi, 3, 80,
								 false);
					save_bbmult = true;
				}
			} else {
				wlc_phy_internal_cal_txgain_nphy(pi);
				save_bbmult = true;
			}

		} else if (NREV_IS(pi->pubpi.phy_rev, 6)) {
			if (PHY_IPA(pi)) {
				if (CHSPEC_IS2G(pi->radio_chanspec))
					wlc_phy_cal_txgainctrl_nphy(pi, 12,
								    false);
				else
					wlc_phy_cal_txgainctrl_nphy(pi, 14,
								    false);
			} else {
				wlc_phy_internal_cal_txgain_nphy(pi);
				save_bbmult = true;
			}
		}

	} else {
		wlc_phy_cal_txgainctrl_nphy(pi, 10, false);
	}

	if (save_bbmult)
		wlc_phy_table_read_nphy(pi, 15, 1, 87, 16,
					&pi->nphy_txcal_bbmult);
}