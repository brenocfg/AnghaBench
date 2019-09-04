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
struct modal_eep_4k_header {int /*<<< orphan*/ * antennaGainCh; int /*<<< orphan*/  antdiv_ctl1; int /*<<< orphan*/  version; int /*<<< orphan*/  db1_1; int /*<<< orphan*/  ob_0; int /*<<< orphan*/ * noiseFloorThreshCh; } ;
struct base_eep_header_4k {int /*<<< orphan*/  txGainType; int /*<<< orphan*/  rxMask; int /*<<< orphan*/  txMask; int /*<<< orphan*/  rfSilent; int /*<<< orphan*/  opCapFlags; int /*<<< orphan*/  deviceCap; int /*<<< orphan*/ * regDmn; int /*<<< orphan*/  macAddr; } ;
struct ar5416_eeprom_4k {struct base_eep_header_4k baseEepHeader; struct modal_eep_4k_header modalHeader; } ;
struct TYPE_2__ {struct ar5416_eeprom_4k map4k; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
typedef  enum eeprom_param { ____Placeholder_eeprom_param } eeprom_param ;

/* Variables and functions */
 int /*<<< orphan*/  AR5416_PWR_TABLE_OFFSET_DB ; 
#define  EEP_ANTENNA_GAIN_2G 145 
#define  EEP_ANT_DIV_CTL1 144 
#define  EEP_DB_2 143 
#define  EEP_FRAC_N_5G 142 
#define  EEP_MAC_LSW 141 
#define  EEP_MAC_MID 140 
#define  EEP_MAC_MSW 139 
#define  EEP_MODAL_VER 138 
#define  EEP_NFTHRESH_2 137 
#define  EEP_OB_2 136 
#define  EEP_OP_CAP 135 
#define  EEP_OP_MODE 134 
#define  EEP_PWR_TABLE_OFFSET 133 
#define  EEP_REG_0 132 
#define  EEP_RF_SILENT 131 
#define  EEP_RX_MASK 130 
#define  EEP_TXGAIN_TYPE 129 
#define  EEP_TX_MASK 128 
 int /*<<< orphan*/  get_unaligned_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ath9k_hw_4k_get_eeprom(struct ath_hw *ah,
				  enum eeprom_param param)
{
	struct ar5416_eeprom_4k *eep = &ah->eeprom.map4k;
	struct modal_eep_4k_header *pModal = &eep->modalHeader;
	struct base_eep_header_4k *pBase = &eep->baseEepHeader;

	switch (param) {
	case EEP_NFTHRESH_2:
		return pModal->noiseFloorThreshCh[0];
	case EEP_MAC_LSW:
		return get_unaligned_be16(pBase->macAddr);
	case EEP_MAC_MID:
		return get_unaligned_be16(pBase->macAddr + 2);
	case EEP_MAC_MSW:
		return get_unaligned_be16(pBase->macAddr + 4);
	case EEP_REG_0:
		return le16_to_cpu(pBase->regDmn[0]);
	case EEP_OP_CAP:
		return le16_to_cpu(pBase->deviceCap);
	case EEP_OP_MODE:
		return pBase->opCapFlags;
	case EEP_RF_SILENT:
		return le16_to_cpu(pBase->rfSilent);
	case EEP_OB_2:
		return pModal->ob_0;
	case EEP_DB_2:
		return pModal->db1_1;
	case EEP_TX_MASK:
		return pBase->txMask;
	case EEP_RX_MASK:
		return pBase->rxMask;
	case EEP_FRAC_N_5G:
		return 0;
	case EEP_PWR_TABLE_OFFSET:
		return AR5416_PWR_TABLE_OFFSET_DB;
	case EEP_MODAL_VER:
		return pModal->version;
	case EEP_ANT_DIV_CTL1:
		return pModal->antdiv_ctl1;
	case EEP_TXGAIN_TYPE:
		return pBase->txGainType;
	case EEP_ANTENNA_GAIN_2G:
		return pModal->antennaGainCh[0];
	default:
		return 0;
	}
}