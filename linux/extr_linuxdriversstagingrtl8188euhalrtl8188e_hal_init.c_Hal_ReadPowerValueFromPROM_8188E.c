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
typedef  int u8 ;
typedef  size_t u32 ;
struct txpowerinfo24g {int** IndexCCK_Base; int** IndexBW40_Base; int** BW20_Diff; int** OFDM_Diff; int** BW40_Diff; int** CCK_Diff; } ;

/* Variables and functions */
 int BIT (int) ; 
 void* EEPROM_DEFAULT_24G_HT20_DIFF ; 
 void* EEPROM_DEFAULT_24G_INDEX ; 
 void* EEPROM_DEFAULT_24G_OFDM_DIFF ; 
 void* EEPROM_DEFAULT_DIFF ; 
 size_t EEPROM_TX_PWR_INX_88E ; 
 size_t MAX_CHNL_GROUP_24G ; 
 size_t MAX_RF_PATH ; 
 size_t MAX_TX_COUNT ; 
 int /*<<< orphan*/  memset (struct txpowerinfo24g*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Hal_ReadPowerValueFromPROM_8188E(struct txpowerinfo24g *pwrInfo24G, u8 *PROMContent, bool AutoLoadFail)
{
	u32 rfPath, eeAddr = EEPROM_TX_PWR_INX_88E, group, TxCount = 0;

	memset(pwrInfo24G, 0, sizeof(struct txpowerinfo24g));

	if (AutoLoadFail) {
		for (rfPath = 0; rfPath < MAX_RF_PATH; rfPath++) {
			/* 2.4G default value */
			for (group = 0; group < MAX_CHNL_GROUP_24G; group++) {
				pwrInfo24G->IndexCCK_Base[rfPath][group] =	EEPROM_DEFAULT_24G_INDEX;
				pwrInfo24G->IndexBW40_Base[rfPath][group] =	EEPROM_DEFAULT_24G_INDEX;
			}
			for (TxCount = 0; TxCount < MAX_TX_COUNT; TxCount++) {
				if (TxCount == 0) {
					pwrInfo24G->BW20_Diff[rfPath][0] = EEPROM_DEFAULT_24G_HT20_DIFF;
					pwrInfo24G->OFDM_Diff[rfPath][0] = EEPROM_DEFAULT_24G_OFDM_DIFF;
				} else {
					pwrInfo24G->BW20_Diff[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
					pwrInfo24G->BW40_Diff[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
					pwrInfo24G->CCK_Diff[rfPath][TxCount] =	EEPROM_DEFAULT_DIFF;
					pwrInfo24G->OFDM_Diff[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
				}
			}
		}
		return;
	}

	for (rfPath = 0; rfPath < MAX_RF_PATH; rfPath++) {
		/* 2.4G default value */
		for (group = 0; group < MAX_CHNL_GROUP_24G; group++) {
			pwrInfo24G->IndexCCK_Base[rfPath][group] =	PROMContent[eeAddr++];
			if (pwrInfo24G->IndexCCK_Base[rfPath][group] == 0xFF)
				pwrInfo24G->IndexCCK_Base[rfPath][group] = EEPROM_DEFAULT_24G_INDEX;
		}
		for (group = 0; group < MAX_CHNL_GROUP_24G-1; group++) {
			pwrInfo24G->IndexBW40_Base[rfPath][group] =	PROMContent[eeAddr++];
			if (pwrInfo24G->IndexBW40_Base[rfPath][group] == 0xFF)
				pwrInfo24G->IndexBW40_Base[rfPath][group] =	EEPROM_DEFAULT_24G_INDEX;
		}
		for (TxCount = 0; TxCount < MAX_TX_COUNT; TxCount++) {
			if (TxCount == 0) {
				pwrInfo24G->BW40_Diff[rfPath][TxCount] = 0;
				if (PROMContent[eeAddr] == 0xFF) {
					pwrInfo24G->BW20_Diff[rfPath][TxCount] = EEPROM_DEFAULT_24G_HT20_DIFF;
				} else {
					pwrInfo24G->BW20_Diff[rfPath][TxCount] = (PROMContent[eeAddr]&0xf0)>>4;
					if (pwrInfo24G->BW20_Diff[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->BW20_Diff[rfPath][TxCount] |= 0xF0;
				}

				if (PROMContent[eeAddr] == 0xFF) {
					pwrInfo24G->OFDM_Diff[rfPath][TxCount] =	EEPROM_DEFAULT_24G_OFDM_DIFF;
				} else {
					pwrInfo24G->OFDM_Diff[rfPath][TxCount] =	(PROMContent[eeAddr]&0x0f);
					if (pwrInfo24G->OFDM_Diff[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->OFDM_Diff[rfPath][TxCount] |= 0xF0;
				}
				pwrInfo24G->CCK_Diff[rfPath][TxCount] = 0;
				eeAddr++;
			} else {
				if (PROMContent[eeAddr] == 0xFF) {
					pwrInfo24G->BW40_Diff[rfPath][TxCount] =	EEPROM_DEFAULT_DIFF;
				} else {
					pwrInfo24G->BW40_Diff[rfPath][TxCount] =	(PROMContent[eeAddr]&0xf0)>>4;
					if (pwrInfo24G->BW40_Diff[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->BW40_Diff[rfPath][TxCount] |= 0xF0;
				}

				if (PROMContent[eeAddr] == 0xFF) {
					pwrInfo24G->BW20_Diff[rfPath][TxCount] =	EEPROM_DEFAULT_DIFF;
				} else {
					pwrInfo24G->BW20_Diff[rfPath][TxCount] =	(PROMContent[eeAddr]&0x0f);
					if (pwrInfo24G->BW20_Diff[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->BW20_Diff[rfPath][TxCount] |= 0xF0;
				}
				eeAddr++;

				if (PROMContent[eeAddr] == 0xFF) {
					pwrInfo24G->OFDM_Diff[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
				} else {
					pwrInfo24G->OFDM_Diff[rfPath][TxCount] =	(PROMContent[eeAddr]&0xf0)>>4;
					if (pwrInfo24G->OFDM_Diff[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->OFDM_Diff[rfPath][TxCount] |= 0xF0;
				}

				if (PROMContent[eeAddr] == 0xFF) {
					pwrInfo24G->CCK_Diff[rfPath][TxCount] =	EEPROM_DEFAULT_DIFF;
				} else {
					pwrInfo24G->CCK_Diff[rfPath][TxCount] =	(PROMContent[eeAddr]&0x0f);
					if (pwrInfo24G->CCK_Diff[rfPath][TxCount] & BIT(3))		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->CCK_Diff[rfPath][TxCount] |= 0xF0;
				}
				eeAddr++;
			}
		}
	}
}