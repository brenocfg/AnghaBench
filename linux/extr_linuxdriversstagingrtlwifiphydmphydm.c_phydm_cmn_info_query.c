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
typedef  int u32 ;
struct phy_dm_struct {int dummy; } ;
struct false_alarm_stat {int cnt_ofdm_fail; int cnt_cck_fail; int cnt_all; int cnt_ofdm_cca; int cnt_cck_cca; int cnt_cca_all; int cnt_vht_crc32_ok; int cnt_ht_crc32_ok; int cnt_ofdm_crc32_ok; int cnt_cck_crc32_ok; int cnt_vht_crc32_error; int cnt_ht_crc32_error; int cnt_ofdm_crc32_error; int cnt_cck_crc32_error; int edcca_flag; int ofdm_block_enable; int cck_block_enable; int dbg_port0; } ;
typedef  enum phydm_info_query { ____Placeholder_phydm_info_query } phydm_info_query ;

/* Variables and functions */
 int /*<<< orphan*/  PHYDM_FALSEALMCNT ; 
#define  PHYDM_INFO_CCA_ALL 145 
#define  PHYDM_INFO_CCA_CCK 144 
#define  PHYDM_INFO_CCA_OFDM 143 
#define  PHYDM_INFO_CCK_ENABLE 142 
#define  PHYDM_INFO_CRC32_ERROR_CCK 141 
#define  PHYDM_INFO_CRC32_ERROR_HT 140 
#define  PHYDM_INFO_CRC32_ERROR_LEGACY 139 
#define  PHYDM_INFO_CRC32_ERROR_VHT 138 
#define  PHYDM_INFO_CRC32_OK_CCK 137 
#define  PHYDM_INFO_CRC32_OK_HT 136 
#define  PHYDM_INFO_CRC32_OK_LEGACY 135 
#define  PHYDM_INFO_CRC32_OK_VHT 134 
#define  PHYDM_INFO_DBG_PORT_0 133 
#define  PHYDM_INFO_EDCCA_FLAG 132 
#define  PHYDM_INFO_FA_CCK 131 
#define  PHYDM_INFO_FA_OFDM 130 
#define  PHYDM_INFO_FA_TOTAL 129 
#define  PHYDM_INFO_OFDM_ENABLE 128 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

u32 phydm_cmn_info_query(struct phy_dm_struct *dm,
			 enum phydm_info_query info_type)
{
	struct false_alarm_stat *false_alm_cnt =
		(struct false_alarm_stat *)phydm_get_structure(
			dm, PHYDM_FALSEALMCNT);

	switch (info_type) {
	case PHYDM_INFO_FA_OFDM:
		return false_alm_cnt->cnt_ofdm_fail;

	case PHYDM_INFO_FA_CCK:
		return false_alm_cnt->cnt_cck_fail;

	case PHYDM_INFO_FA_TOTAL:
		return false_alm_cnt->cnt_all;

	case PHYDM_INFO_CCA_OFDM:
		return false_alm_cnt->cnt_ofdm_cca;

	case PHYDM_INFO_CCA_CCK:
		return false_alm_cnt->cnt_cck_cca;

	case PHYDM_INFO_CCA_ALL:
		return false_alm_cnt->cnt_cca_all;

	case PHYDM_INFO_CRC32_OK_VHT:
		return false_alm_cnt->cnt_vht_crc32_ok;

	case PHYDM_INFO_CRC32_OK_HT:
		return false_alm_cnt->cnt_ht_crc32_ok;

	case PHYDM_INFO_CRC32_OK_LEGACY:
		return false_alm_cnt->cnt_ofdm_crc32_ok;

	case PHYDM_INFO_CRC32_OK_CCK:
		return false_alm_cnt->cnt_cck_crc32_ok;

	case PHYDM_INFO_CRC32_ERROR_VHT:
		return false_alm_cnt->cnt_vht_crc32_error;

	case PHYDM_INFO_CRC32_ERROR_HT:
		return false_alm_cnt->cnt_ht_crc32_error;

	case PHYDM_INFO_CRC32_ERROR_LEGACY:
		return false_alm_cnt->cnt_ofdm_crc32_error;

	case PHYDM_INFO_CRC32_ERROR_CCK:
		return false_alm_cnt->cnt_cck_crc32_error;

	case PHYDM_INFO_EDCCA_FLAG:
		return false_alm_cnt->edcca_flag;

	case PHYDM_INFO_OFDM_ENABLE:
		return false_alm_cnt->ofdm_block_enable;

	case PHYDM_INFO_CCK_ENABLE:
		return false_alm_cnt->cck_block_enable;

	case PHYDM_INFO_DBG_PORT_0:
		return false_alm_cnt->dbg_port0;

	default:
		return 0xffffffff;
	}
}