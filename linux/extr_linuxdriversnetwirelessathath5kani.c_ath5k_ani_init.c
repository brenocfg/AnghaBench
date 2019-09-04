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
struct TYPE_4__ {int max_spur_level; int ani_mode; } ;
struct TYPE_3__ {scalar_t__ cap_has_phyerr_counters; } ;
struct ath5k_hw {scalar_t__ ah_version; scalar_t__ ah_mac_srev; TYPE_2__ ani_state; TYPE_1__ ah_capabilities; } ;
typedef  enum ath5k_ani_mode { ____Placeholder_ath5k_ani_mode } ath5k_ani_mode ;

/* Variables and functions */
 scalar_t__ AR5K_AR5212 ; 
 int AR5K_RX_FILTER_PHYERR ; 
 scalar_t__ AR5K_SREV_AR2414 ; 
 int /*<<< orphan*/  ATH5K_ANI_MAX_FIRSTEP_LVL ; 
 int /*<<< orphan*/  ATH5K_ANI_MAX_NOISE_IMM_LVL ; 
 int ATH5K_ANI_MODE_AUTO ; 
 int ATH5K_ANI_MODE_MANUAL_HIGH ; 
 int ATH5K_ANI_MODE_MANUAL_LOW ; 
 int ATH5K_ANI_MODE_OFF ; 
 int /*<<< orphan*/  ATH5K_DBG_UNLIMIT (struct ath5k_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_ANI ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*,int) ; 
 int /*<<< orphan*/  ath5k_ani_set_cck_weak_signal_detection (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_ani_set_firstep_level (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_ani_set_noise_immunity_level (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_ani_set_ofdm_weak_signal_detection (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_ani_set_spur_immunity_level (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_disable_phy_err_counters (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_enable_phy_err_counters (struct ath5k_hw*) ; 
 int ath5k_hw_get_rx_filter (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_rx_filter (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void
ath5k_ani_init(struct ath5k_hw *ah, enum ath5k_ani_mode mode)
{
	/* ANI is only possible on 5212 and newer */
	if (ah->ah_version < AR5K_AR5212)
		return;

	if (mode < ATH5K_ANI_MODE_OFF || mode > ATH5K_ANI_MODE_AUTO) {
		ATH5K_ERR(ah, "ANI mode %d out of range", mode);
		return;
	}

	/* clear old state information */
	memset(&ah->ani_state, 0, sizeof(ah->ani_state));

	/* older hardware has more spur levels than newer */
	if (ah->ah_mac_srev < AR5K_SREV_AR2414)
		ah->ani_state.max_spur_level = 7;
	else
		ah->ani_state.max_spur_level = 2;

	/* initial values for our ani parameters */
	if (mode == ATH5K_ANI_MODE_OFF) {
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "ANI off\n");
	} else if (mode == ATH5K_ANI_MODE_MANUAL_LOW) {
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
			"ANI manual low -> high sensitivity\n");
		ath5k_ani_set_noise_immunity_level(ah, 0);
		ath5k_ani_set_spur_immunity_level(ah, 0);
		ath5k_ani_set_firstep_level(ah, 0);
		ath5k_ani_set_ofdm_weak_signal_detection(ah, true);
		ath5k_ani_set_cck_weak_signal_detection(ah, true);
	} else if (mode == ATH5K_ANI_MODE_MANUAL_HIGH) {
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
			"ANI manual high -> low sensitivity\n");
		ath5k_ani_set_noise_immunity_level(ah,
					ATH5K_ANI_MAX_NOISE_IMM_LVL);
		ath5k_ani_set_spur_immunity_level(ah,
					ah->ani_state.max_spur_level);
		ath5k_ani_set_firstep_level(ah, ATH5K_ANI_MAX_FIRSTEP_LVL);
		ath5k_ani_set_ofdm_weak_signal_detection(ah, false);
		ath5k_ani_set_cck_weak_signal_detection(ah, false);
	} else if (mode == ATH5K_ANI_MODE_AUTO) {
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "ANI auto\n");
		ath5k_ani_set_noise_immunity_level(ah, 0);
		ath5k_ani_set_spur_immunity_level(ah, 0);
		ath5k_ani_set_firstep_level(ah, 0);
		ath5k_ani_set_ofdm_weak_signal_detection(ah, true);
		ath5k_ani_set_cck_weak_signal_detection(ah, false);
	}

	/* newer hardware has PHY error counter registers which we can use to
	 * get OFDM and CCK error counts. older hardware has to set rxfilter and
	 * report every single PHY error by calling ath5k_ani_phy_error_report()
	 */
	if (mode == ATH5K_ANI_MODE_AUTO) {
		if (ah->ah_capabilities.cap_has_phyerr_counters)
			ath5k_enable_phy_err_counters(ah);
		else
			ath5k_hw_set_rx_filter(ah, ath5k_hw_get_rx_filter(ah) |
						   AR5K_RX_FILTER_PHYERR);
	} else {
		if (ah->ah_capabilities.cap_has_phyerr_counters)
			ath5k_disable_phy_err_counters(ah);
		else
			ath5k_hw_set_rx_filter(ah, ath5k_hw_get_rx_filter(ah) &
						   ~AR5K_RX_FILTER_PHYERR);
	}

	ah->ani_state.ani_mode = mode;
}