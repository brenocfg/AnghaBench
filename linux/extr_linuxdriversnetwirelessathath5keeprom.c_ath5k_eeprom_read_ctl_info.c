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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ath5k_eeprom_info {scalar_t__ ee_version; int ee_ctls; int* ee_ctl; struct ath5k_edge_power* ee_ctl_pwr; int /*<<< orphan*/  ee_misc1; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;
struct ath5k_edge_power {int freq; int edge; int flag; } ;

/* Variables and functions */
#define  AR5K_CTL_11A 129 
 int AR5K_CTL_MODE_M ; 
#define  AR5K_CTL_TURBO 128 
 scalar_t__ AR5K_EEPROM_CTL (scalar_t__) ; 
 unsigned int AR5K_EEPROM_FREQ_M (scalar_t__) ; 
 scalar_t__ AR5K_EEPROM_GROUP5_OFFSET ; 
 scalar_t__ AR5K_EEPROM_GROUP8_OFFSET ; 
 scalar_t__ AR5K_EEPROM_GROUPS_START (scalar_t__) ; 
 unsigned int AR5K_EEPROM_MODE_11A ; 
 unsigned int AR5K_EEPROM_MODE_11G ; 
 int AR5K_EEPROM_N_CTLS (scalar_t__) ; 
 int AR5K_EEPROM_N_EDGES ; 
 unsigned int AR5K_EEPROM_POWER_M ; 
 int /*<<< orphan*/  AR5K_EEPROM_READ (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AR5K_EEPROM_TARGET_PWRSTART (int /*<<< orphan*/ ) ; 
 scalar_t__ AR5K_EEPROM_VERSION_3_3 ; 
 scalar_t__ AR5K_EEPROM_VERSION_4_0 ; 
 int ath5k_eeprom_bin2freq (struct ath5k_eeprom_info*,int,unsigned int) ; 

__attribute__((used)) static int
ath5k_eeprom_read_ctl_info(struct ath5k_hw *ah)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_edge_power *rep;
	unsigned int fmask, pmask;
	unsigned int ctl_mode;
	int i, j;
	u32 offset;
	u16 val;

	pmask = AR5K_EEPROM_POWER_M;
	fmask = AR5K_EEPROM_FREQ_M(ee->ee_version);
	offset = AR5K_EEPROM_CTL(ee->ee_version);
	ee->ee_ctls = AR5K_EEPROM_N_CTLS(ee->ee_version);
	for (i = 0; i < ee->ee_ctls; i += 2) {
		AR5K_EEPROM_READ(offset++, val);
		ee->ee_ctl[i] = (val >> 8) & 0xff;
		ee->ee_ctl[i + 1] = val & 0xff;
	}

	offset = AR5K_EEPROM_GROUP8_OFFSET;
	if (ee->ee_version >= AR5K_EEPROM_VERSION_4_0)
		offset += AR5K_EEPROM_TARGET_PWRSTART(ee->ee_misc1) -
			AR5K_EEPROM_GROUP5_OFFSET;
	else
		offset += AR5K_EEPROM_GROUPS_START(ee->ee_version);

	rep = ee->ee_ctl_pwr;
	for (i = 0; i < ee->ee_ctls; i++) {
		switch (ee->ee_ctl[i] & AR5K_CTL_MODE_M) {
		case AR5K_CTL_11A:
		case AR5K_CTL_TURBO:
			ctl_mode = AR5K_EEPROM_MODE_11A;
			break;
		default:
			ctl_mode = AR5K_EEPROM_MODE_11G;
			break;
		}
		if (ee->ee_ctl[i] == 0) {
			if (ee->ee_version >= AR5K_EEPROM_VERSION_3_3)
				offset += 8;
			else
				offset += 7;
			rep += AR5K_EEPROM_N_EDGES;
			continue;
		}
		if (ee->ee_version >= AR5K_EEPROM_VERSION_3_3) {
			for (j = 0; j < AR5K_EEPROM_N_EDGES; j += 2) {
				AR5K_EEPROM_READ(offset++, val);
				rep[j].freq = (val >> 8) & fmask;
				rep[j + 1].freq = val & fmask;
			}
			for (j = 0; j < AR5K_EEPROM_N_EDGES; j += 2) {
				AR5K_EEPROM_READ(offset++, val);
				rep[j].edge = (val >> 8) & pmask;
				rep[j].flag = (val >> 14) & 1;
				rep[j + 1].edge = val & pmask;
				rep[j + 1].flag = (val >> 6) & 1;
			}
		} else {
			AR5K_EEPROM_READ(offset++, val);
			rep[0].freq = (val >> 9) & fmask;
			rep[1].freq = (val >> 2) & fmask;
			rep[2].freq = (val << 5) & fmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[2].freq |= (val >> 11) & 0x1f;
			rep[3].freq = (val >> 4) & fmask;
			rep[4].freq = (val << 3) & fmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[4].freq |= (val >> 13) & 0x7;
			rep[5].freq = (val >> 6) & fmask;
			rep[6].freq = (val << 1) & fmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[6].freq |= (val >> 15) & 0x1;
			rep[7].freq = (val >> 8) & fmask;

			rep[0].edge = (val >> 2) & pmask;
			rep[1].edge = (val << 4) & pmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[1].edge |= (val >> 12) & 0xf;
			rep[2].edge = (val >> 6) & pmask;
			rep[3].edge = val & pmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[4].edge = (val >> 10) & pmask;
			rep[5].edge = (val >> 4) & pmask;
			rep[6].edge = (val << 2) & pmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[6].edge |= (val >> 14) & 0x3;
			rep[7].edge = (val >> 8) & pmask;
		}
		for (j = 0; j < AR5K_EEPROM_N_EDGES; j++) {
			rep[j].freq = ath5k_eeprom_bin2freq(ee,
				rep[j].freq, ctl_mode);
		}
		rep += AR5K_EEPROM_N_EDGES;
	}

	return 0;
}