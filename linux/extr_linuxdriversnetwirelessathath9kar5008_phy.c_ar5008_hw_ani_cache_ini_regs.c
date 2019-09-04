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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  macRev; int /*<<< orphan*/  macVersion; } ;
struct ath9k_ani_default {void* cycpwrThr1Ext; void* cycpwrThr1; void* firstepLow; void* firstep; void* m2ThreshLowExt; void* m1ThreshLowExt; void* m2ThreshExt; void* m1ThreshExt; void* m2CountThrLow; void* m2ThreshLow; void* m1ThreshLow; void* m2CountThr; void* m2Thresh; void* m1Thresh; } ;
struct ar5416AniState {int ofdmWeakSigDetect; int mrcCCK; int /*<<< orphan*/  firstepLevel; int /*<<< orphan*/  spurImmunityLevel; struct ath9k_ani_default iniDef; } ;
struct ath_hw {int /*<<< orphan*/  opmode; TYPE_1__ hw_version; struct ar5416AniState ani; struct ath9k_channel* curchan; } ;
struct ath_common {int dummy; } ;
struct ath9k_channel {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANI ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA ; 
 int /*<<< orphan*/  AR_PHY_EXT_TIMING5_CYCPWR_THR1 ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_FIRSTEP ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_FIRSTEP_LOW ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_M1_THRESH ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_M1_THRESH_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_M2_THRESH ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_M2_THRESH_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_LOW_M1_THRESH_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_LOW_M2_THRESH_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_M1_THRESH ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_M2COUNT_THR ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_M2_THRESH ; 
 int /*<<< orphan*/  AR_PHY_TIMING5 ; 
 int /*<<< orphan*/  AR_PHY_TIMING5_CYCPWR_THR1 ; 
 int /*<<< orphan*/  ATH9K_ANI_FIRSTEP_LVL ; 
 int /*<<< orphan*/  ATH9K_ANI_SPUR_IMMUNE_LVL ; 
 void* MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 void* REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar5008_hw_ani_cache_ini_regs(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_channel *chan = ah->curchan;
	struct ar5416AniState *aniState = &ah->ani;
	struct ath9k_ani_default *iniDef;
	u32 val;

	iniDef = &aniState->iniDef;

	ath_dbg(common, ANI, "ver %d.%d opmode %u chan %d Mhz\n",
		ah->hw_version.macVersion,
		ah->hw_version.macRev,
		ah->opmode,
		chan->channel);

	val = REG_READ(ah, AR_PHY_SFCORR);
	iniDef->m1Thresh = MS(val, AR_PHY_SFCORR_M1_THRESH);
	iniDef->m2Thresh = MS(val, AR_PHY_SFCORR_M2_THRESH);
	iniDef->m2CountThr = MS(val, AR_PHY_SFCORR_M2COUNT_THR);

	val = REG_READ(ah, AR_PHY_SFCORR_LOW);
	iniDef->m1ThreshLow = MS(val, AR_PHY_SFCORR_LOW_M1_THRESH_LOW);
	iniDef->m2ThreshLow = MS(val, AR_PHY_SFCORR_LOW_M2_THRESH_LOW);
	iniDef->m2CountThrLow = MS(val, AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW);

	val = REG_READ(ah, AR_PHY_SFCORR_EXT);
	iniDef->m1ThreshExt = MS(val, AR_PHY_SFCORR_EXT_M1_THRESH);
	iniDef->m2ThreshExt = MS(val, AR_PHY_SFCORR_EXT_M2_THRESH);
	iniDef->m1ThreshLowExt = MS(val, AR_PHY_SFCORR_EXT_M1_THRESH_LOW);
	iniDef->m2ThreshLowExt = MS(val, AR_PHY_SFCORR_EXT_M2_THRESH_LOW);
	iniDef->firstep = REG_READ_FIELD(ah,
					 AR_PHY_FIND_SIG,
					 AR_PHY_FIND_SIG_FIRSTEP);
	iniDef->firstepLow = REG_READ_FIELD(ah,
					    AR_PHY_FIND_SIG_LOW,
					    AR_PHY_FIND_SIG_FIRSTEP_LOW);
	iniDef->cycpwrThr1 = REG_READ_FIELD(ah,
					    AR_PHY_TIMING5,
					    AR_PHY_TIMING5_CYCPWR_THR1);
	iniDef->cycpwrThr1Ext = REG_READ_FIELD(ah,
					       AR_PHY_EXT_CCA,
					       AR_PHY_EXT_TIMING5_CYCPWR_THR1);

	/* these levels just got reset to defaults by the INI */
	aniState->spurImmunityLevel = ATH9K_ANI_SPUR_IMMUNE_LVL;
	aniState->firstepLevel = ATH9K_ANI_FIRSTEP_LVL;
	aniState->ofdmWeakSigDetect = true;
	aniState->mrcCCK = false; /* not available on pre AR9003 */
}