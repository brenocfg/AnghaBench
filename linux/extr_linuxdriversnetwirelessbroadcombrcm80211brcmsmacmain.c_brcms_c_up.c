#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int /*<<< orphan*/  hw_value; } ;
struct brcms_c_info {int clk; int bandinit_pending; int WDarmed; TYPE_5__* stf; int /*<<< orphan*/  wdtimer; TYPE_6__* hw; TYPE_4__* pub; int /*<<< orphan*/  wl; struct brcms_bss_cfg* bsscfg; } ;
struct brcms_bss_cfg {scalar_t__ type; } ;
struct TYPE_15__ {int /*<<< orphan*/  d11core; int /*<<< orphan*/  sih; } ;
struct TYPE_14__ {int /*<<< orphan*/  ldpc; } ;
struct TYPE_13__ {int hw_up; int boardflags; int boardrev; int up; TYPE_3__* ieee_hw; scalar_t__ radio_disabled; int /*<<< orphan*/  unit; scalar_t__ hw_off; } ;
struct TYPE_10__ {struct ieee80211_channel* chan; } ;
struct TYPE_11__ {TYPE_1__ chandef; } ;
struct TYPE_12__ {TYPE_2__ conf; } ;

/* Variables and functions */
 scalar_t__ BCMA_CHIP_ID_BCM4313 ; 
 int BFL_FEM ; 
 int BFL_FEM_BT ; 
 scalar_t__ BRCMS_TYPE_ADHOC ; 
 scalar_t__ BRCMS_TYPE_STATION ; 
 int /*<<< orphan*/  BRCM_BAND_ALL ; 
 int ENOMEDIUM ; 
 int /*<<< orphan*/  MHF1 ; 
 int /*<<< orphan*/  MHF1_EDCF ; 
 int /*<<< orphan*/  MHF4 ; 
 int /*<<< orphan*/  MHF4_EXTPA_ENABLE ; 
 int /*<<< orphan*/  MHF5 ; 
 int /*<<< orphan*/  MHF5_4313_GPIOCTRL ; 
 int /*<<< orphan*/  TIMER_INTERVAL_WATCHDOG ; 
 int /*<<< orphan*/  WL_RADIO_HW_DISABLE ; 
 scalar_t__ ai_get_chip_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_add_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_b_hw_up (TYPE_6__*) ; 
 int /*<<< orphan*/  brcms_b_mhf (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_up_finish (TYPE_6__*) ; 
 int brcms_b_up_prep (TYPE_6__*) ; 
 int /*<<< orphan*/  brcms_c_enable_mac (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_ht_update_ldpc (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_radio_monitor_start (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_radio_monitor_stop (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_set_chanspec (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_stf_phy_txant_upd (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_suspend_mac_and_wait (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_wme_retries_write (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_dbg_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ brcms_deviceremoved (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ch20mhz_chspec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mboolisset (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mboolset (scalar_t__,int /*<<< orphan*/ ) ; 

int brcms_c_up(struct brcms_c_info *wlc)
{
	struct ieee80211_channel *ch;

	brcms_dbg_info(wlc->hw->d11core, "wl%d\n", wlc->pub->unit);

	/* HW is turned off so don't try to access it */
	if (wlc->pub->hw_off || brcms_deviceremoved(wlc))
		return -ENOMEDIUM;

	if (!wlc->pub->hw_up) {
		brcms_b_hw_up(wlc->hw);
		wlc->pub->hw_up = true;
	}

	if ((wlc->pub->boardflags & BFL_FEM)
	    && (ai_get_chip_id(wlc->hw->sih) == BCMA_CHIP_ID_BCM4313)) {
		if (wlc->pub->boardrev >= 0x1250
		    && (wlc->pub->boardflags & BFL_FEM_BT))
			brcms_b_mhf(wlc->hw, MHF5, MHF5_4313_GPIOCTRL,
				MHF5_4313_GPIOCTRL, BRCM_BAND_ALL);
		else
			brcms_b_mhf(wlc->hw, MHF4, MHF4_EXTPA_ENABLE,
				    MHF4_EXTPA_ENABLE, BRCM_BAND_ALL);
	}

	/*
	 * Need to read the hwradio status here to cover the case where the
	 * system is loaded with the hw radio disabled. We do not want to bring
	 * the driver up in this case. If radio is disabled, abort up, lower
	 * power, start radio timer and return 0(for NDIS) don't call
	 * radio_update to avoid looping brcms_c_up.
	 *
	 * brcms_b_up_prep() returns either 0 or -BCME_RADIOOFF only
	 */
	if (!wlc->pub->radio_disabled) {
		int status = brcms_b_up_prep(wlc->hw);
		if (status == -ENOMEDIUM) {
			if (!mboolisset
			    (wlc->pub->radio_disabled, WL_RADIO_HW_DISABLE)) {
				struct brcms_bss_cfg *bsscfg = wlc->bsscfg;
				mboolset(wlc->pub->radio_disabled,
					 WL_RADIO_HW_DISABLE);
				if (bsscfg->type == BRCMS_TYPE_STATION ||
				    bsscfg->type == BRCMS_TYPE_ADHOC)
					brcms_err(wlc->hw->d11core,
						  "wl%d: up: rfdisable -> "
						  "bsscfg_disable()\n",
						   wlc->pub->unit);
			}
		}
	}

	if (wlc->pub->radio_disabled) {
		brcms_c_radio_monitor_start(wlc);
		return 0;
	}

	/* brcms_b_up_prep has done brcms_c_corereset(). so clk is on, set it */
	wlc->clk = true;

	brcms_c_radio_monitor_stop(wlc);

	/* Set EDCF hostflags */
	brcms_b_mhf(wlc->hw, MHF1, MHF1_EDCF, MHF1_EDCF, BRCM_BAND_ALL);

	brcms_init(wlc->wl);
	wlc->pub->up = true;

	if (wlc->bandinit_pending) {
		ch = wlc->pub->ieee_hw->conf.chandef.chan;
		brcms_c_suspend_mac_and_wait(wlc);
		brcms_c_set_chanspec(wlc, ch20mhz_chspec(ch->hw_value));
		wlc->bandinit_pending = false;
		brcms_c_enable_mac(wlc);
	}

	brcms_b_up_finish(wlc->hw);

	/* Program the TX wme params with the current settings */
	brcms_c_wme_retries_write(wlc);

	/* start one second watchdog timer */
	brcms_add_timer(wlc->wdtimer, TIMER_INTERVAL_WATCHDOG, true);
	wlc->WDarmed = true;

	/* ensure antenna config is up to date */
	brcms_c_stf_phy_txant_upd(wlc);
	/* ensure LDPC config is in sync */
	brcms_c_ht_update_ldpc(wlc, wlc->stf->ldpc);

	return 0;
}