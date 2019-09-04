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
struct ath5k_ani_state {int listen_time; scalar_t__ ani_mode; int ofdm_errors; int cck_errors; } ;
struct ath5k_hw {struct ath5k_ani_state ani_state; } ;

/* Variables and functions */
 int ATH5K_ANI_CCK_TRIG_HIGH ; 
 int ATH5K_ANI_CCK_TRIG_LOW ; 
 int ATH5K_ANI_LISTEN_PERIOD ; 
 scalar_t__ ATH5K_ANI_MODE_AUTO ; 
 int ATH5K_ANI_OFDM_TRIG_HIGH ; 
 int ATH5K_ANI_OFDM_TRIG_LOW ; 
 int /*<<< orphan*/  ATH5K_DBG_UNLIMIT (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_ANI ; 
 int /*<<< orphan*/  ath5k_ani_lower_immunity (struct ath5k_hw*,struct ath5k_ani_state*) ; 
 int /*<<< orphan*/  ath5k_ani_period_restart (struct ath5k_ani_state*) ; 
 int /*<<< orphan*/  ath5k_ani_raise_immunity (struct ath5k_hw*,struct ath5k_ani_state*,int) ; 
 int /*<<< orphan*/  ath5k_ani_save_and_clear_phy_errors (struct ath5k_hw*,struct ath5k_ani_state*) ; 
 int ath5k_hw_ani_get_listen_time (struct ath5k_hw*,struct ath5k_ani_state*) ; 

void
ath5k_ani_calibration(struct ath5k_hw *ah)
{
	struct ath5k_ani_state *as = &ah->ani_state;
	int listen, ofdm_high, ofdm_low, cck_high, cck_low;

	/* get listen time since last call and add it to the counter because we
	 * might not have restarted the "ani period" last time.
	 * always do this to calculate the busy time also in manual mode */
	listen = ath5k_hw_ani_get_listen_time(ah, as);
	as->listen_time += listen;

	if (as->ani_mode != ATH5K_ANI_MODE_AUTO)
		return;

	ath5k_ani_save_and_clear_phy_errors(ah, as);

	ofdm_high = as->listen_time * ATH5K_ANI_OFDM_TRIG_HIGH / 1000;
	cck_high = as->listen_time * ATH5K_ANI_CCK_TRIG_HIGH / 1000;
	ofdm_low = as->listen_time * ATH5K_ANI_OFDM_TRIG_LOW / 1000;
	cck_low = as->listen_time * ATH5K_ANI_CCK_TRIG_LOW / 1000;

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
		"listen %d (now %d)", as->listen_time, listen);
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
		"check high ofdm %d/%d cck %d/%d",
		as->ofdm_errors, ofdm_high, as->cck_errors, cck_high);

	if (as->ofdm_errors > ofdm_high || as->cck_errors > cck_high) {
		/* too many PHY errors - we have to raise immunity */
		bool ofdm_flag = as->ofdm_errors > ofdm_high ? true : false;
		ath5k_ani_raise_immunity(ah, as, ofdm_flag);
		ath5k_ani_period_restart(as);

	} else if (as->listen_time > 5 * ATH5K_ANI_LISTEN_PERIOD) {
		/* If more than 5 (TODO: why 5?) periods have passed and we got
		 * relatively little errors we can try to lower immunity */
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
			"check low ofdm %d/%d cck %d/%d",
			as->ofdm_errors, ofdm_low, as->cck_errors, cck_low);

		if (as->ofdm_errors <= ofdm_low && as->cck_errors <= cck_low)
			ath5k_ani_lower_immunity(ah, as);

		ath5k_ani_period_restart(as);
	}
}