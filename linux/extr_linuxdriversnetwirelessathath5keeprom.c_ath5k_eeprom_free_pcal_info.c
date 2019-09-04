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
typedef  size_t u8 ;
struct ath5k_pdgain_info {struct ath5k_pdgain_info* pd_pwr; struct ath5k_pdgain_info* pd_step; } ;
struct ath5k_eeprom_info {size_t* ee_n_piers; struct ath5k_chan_pcal_info* ee_pwr_cal_g; int /*<<< orphan*/  ee_header; struct ath5k_chan_pcal_info* ee_pwr_cal_b; struct ath5k_chan_pcal_info* ee_pwr_cal_a; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;
struct ath5k_chan_pcal_info {struct ath5k_pdgain_info* pd_curves; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_EEPROM_HDR_11A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_EEPROM_HDR_11B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_EEPROM_HDR_11G (int /*<<< orphan*/ ) ; 
#define  AR5K_EEPROM_MODE_11A 130 
#define  AR5K_EEPROM_MODE_11B 129 
#define  AR5K_EEPROM_MODE_11G 128 
 size_t AR5K_EEPROM_N_PD_CURVES ; 
 int EINVAL ; 
 int /*<<< orphan*/  kfree (struct ath5k_pdgain_info*) ; 

__attribute__((used)) static int
ath5k_eeprom_free_pcal_info(struct ath5k_hw *ah, int mode)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_chan_pcal_info *chinfo;
	u8 pier, pdg;

	switch (mode) {
	case AR5K_EEPROM_MODE_11A:
		if (!AR5K_EEPROM_HDR_11A(ee->ee_header))
			return 0;
		chinfo = ee->ee_pwr_cal_a;
		break;
	case AR5K_EEPROM_MODE_11B:
		if (!AR5K_EEPROM_HDR_11B(ee->ee_header))
			return 0;
		chinfo = ee->ee_pwr_cal_b;
		break;
	case AR5K_EEPROM_MODE_11G:
		if (!AR5K_EEPROM_HDR_11G(ee->ee_header))
			return 0;
		chinfo = ee->ee_pwr_cal_g;
		break;
	default:
		return -EINVAL;
	}

	for (pier = 0; pier < ee->ee_n_piers[mode]; pier++) {
		if (!chinfo[pier].pd_curves)
			continue;

		for (pdg = 0; pdg < AR5K_EEPROM_N_PD_CURVES; pdg++) {
			struct ath5k_pdgain_info *pd =
					&chinfo[pier].pd_curves[pdg];

			kfree(pd->pd_step);
			kfree(pd->pd_pwr);
		}

		kfree(chinfo[pier].pd_curves);
	}

	return 0;
}