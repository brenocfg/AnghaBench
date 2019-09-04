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
struct TYPE_2__ {int /*<<< orphan*/  ani_poll_interval; int /*<<< orphan*/  cck_trig_low; int /*<<< orphan*/  cck_trig_high; int /*<<< orphan*/  ofdm_trig_low; int /*<<< orphan*/  ofdm_trig_high; } ;
struct ar5416AniState {int mrcCCK; int ofdmsTurn; int ofdmWeakSigDetect; int /*<<< orphan*/  ofdmNoiseImmunityLevel; int /*<<< orphan*/  cckNoiseImmunityLevel; int /*<<< orphan*/  firstepLevel; int /*<<< orphan*/  spurImmunityLevel; } ;
struct ath_hw {TYPE_1__ config; int /*<<< orphan*/  aniperiod; struct ar5416AniState ani; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANI ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  ATH9K_ANI_CCK_DEF_LEVEL ; 
 int /*<<< orphan*/  ATH9K_ANI_CCK_TRIG_HIGH ; 
 int /*<<< orphan*/  ATH9K_ANI_CCK_TRIG_HIGH_OLD ; 
 int /*<<< orphan*/  ATH9K_ANI_CCK_TRIG_LOW ; 
 int /*<<< orphan*/  ATH9K_ANI_CCK_TRIG_LOW_OLD ; 
 int /*<<< orphan*/  ATH9K_ANI_FIRSTEP_LVL ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_DEF_LEVEL ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_TRIG_HIGH ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_TRIG_HIGH_OLD ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_TRIG_LOW ; 
 int /*<<< orphan*/  ATH9K_ANI_OFDM_TRIG_LOW_OLD ; 
 int /*<<< orphan*/  ATH9K_ANI_PERIOD ; 
 int /*<<< orphan*/  ATH9K_ANI_POLLINTERVAL ; 
 int /*<<< orphan*/  ATH9K_ANI_SPUR_IMMUNE_LVL ; 
 int /*<<< orphan*/  ath9k_ani_restart (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_enable_mib_counters (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

void ath9k_hw_ani_init(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ar5416AniState *ani = &ah->ani;

	ath_dbg(common, ANI, "Initialize ANI\n");

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW;
		ah->config.cck_trig_high = ATH9K_ANI_CCK_TRIG_HIGH;
		ah->config.cck_trig_low = ATH9K_ANI_CCK_TRIG_LOW;
	} else {
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH_OLD;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW_OLD;
		ah->config.cck_trig_high = ATH9K_ANI_CCK_TRIG_HIGH_OLD;
		ah->config.cck_trig_low = ATH9K_ANI_CCK_TRIG_LOW_OLD;
	}

	ani->spurImmunityLevel = ATH9K_ANI_SPUR_IMMUNE_LVL;
	ani->firstepLevel = ATH9K_ANI_FIRSTEP_LVL;
	ani->mrcCCK = AR_SREV_9300_20_OR_LATER(ah) ? true : false;
	ani->ofdmsTurn = true;
	ani->ofdmWeakSigDetect = true;
	ani->cckNoiseImmunityLevel = ATH9K_ANI_CCK_DEF_LEVEL;
	ani->ofdmNoiseImmunityLevel = ATH9K_ANI_OFDM_DEF_LEVEL;

	/*
	 * since we expect some ongoing maintenance on the tables, let's sanity
	 * check here default level should not modify INI setting.
	 */
	ah->aniperiod = ATH9K_ANI_PERIOD;
	ah->config.ani_poll_interval = ATH9K_ANI_POLLINTERVAL;

	ath9k_ani_restart(ah);
	ath9k_enable_mib_counters(ah);
}