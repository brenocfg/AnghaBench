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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct psd_info {int psd_fc_channel; int psd_in_progress; int initial_gain_backup; size_t rf_0x18_bkp; size_t psd_bw_rf_reg; int fft_smp_point; int sw_avg_time; size_t psd_pwr_common_offset; size_t* psd_result; scalar_t__ noise_k_en; } ;
struct phy_dm_struct {int support_ic_type; int /*<<< orphan*/  support_ability; struct psd_info dm_psd_table; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MASKDWORD ; 
 int /*<<< orphan*/  ODM_BB_DIG ; 
 int /*<<< orphan*/  ODM_BB_FA_CNT ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int ODM_IC_11AC_SERIES ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int ODM_RTL8821 ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ODM_delay_us (int) ; 
 int RFREGOFFSETMASK ; 
 scalar_t__ STOP_TRX_FAIL ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int,int) ; 
 size_t odm_get_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  odm_move_memory (struct phy_dm_struct*,size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int,size_t) ; 
 scalar_t__ phydm_get_psd_data (struct phy_dm_struct*,int,int) ; 
 scalar_t__ phydm_psd_stop_trx (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  psd_result_cali_tone_8821 ; 
 int /*<<< orphan*/  psd_result_cali_val_8821 ; 

void phydm_psd(void *dm_void, u32 igi, u16 start_point, u16 stop_point)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct psd_info *dm_psd_table = &dm->dm_psd_table;
	u32 i = 0, mod_tone_idx;
	u32 t = 0;
	u16 fft_max_half_bw;
	u32 psd_igi_a_reg;
	u32 psd_igi_b_reg;
	u16 psd_fc_channel = dm_psd_table->psd_fc_channel;
	u8 ag_rf_mode_reg = 0;
	u8 rf_reg18_9_8 = 0;
	u32 psd_result_tmp = 0;
	u8 psd_result = 0;
	u8 psd_result_cali_tone[7] = {0};
	u8 psd_result_cali_val[7] = {0};
	u8 noise_table_idx = 0;

	if (dm->support_ic_type == ODM_RTL8821) {
		odm_move_memory(dm, psd_result_cali_tone,
				psd_result_cali_tone_8821, 7);
		odm_move_memory(dm, psd_result_cali_val,
				psd_result_cali_val_8821, 7);
	}

	dm_psd_table->psd_in_progress = 1;

	/*[Stop DIG]*/
	dm->support_ability &= ~(ODM_BB_DIG);
	dm->support_ability &= ~(ODM_BB_FA_CNT);

	ODM_RT_TRACE(dm, ODM_COMP_API, "PSD Start =>\n");

	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		psd_igi_a_reg = 0xc50;
		psd_igi_b_reg = 0xe50;
	} else {
		psd_igi_a_reg = 0xc50;
		psd_igi_b_reg = 0xc58;
	}

	/*[back up IGI]*/
	dm_psd_table->initial_gain_backup =
		odm_get_bb_reg(dm, psd_igi_a_reg, 0xff);
	odm_set_bb_reg(dm, psd_igi_a_reg, 0xff,
		       0x6e); /*IGI target at 0dBm & make it can't CCA*/
	odm_set_bb_reg(dm, psd_igi_b_reg, 0xff,
		       0x6e); /*IGI target at 0dBm & make it can't CCA*/
	ODM_delay_us(10);

	if (phydm_psd_stop_trx(dm) == STOP_TRX_FAIL) {
		ODM_RT_TRACE(dm, ODM_COMP_API, "STOP_TRX_FAIL\n");
		return;
	}

	/*[Set IGI]*/
	odm_set_bb_reg(dm, psd_igi_a_reg, 0xff, igi);
	odm_set_bb_reg(dm, psd_igi_b_reg, 0xff, igi);

	/*[Backup RF Reg]*/
	dm_psd_table->rf_0x18_bkp =
		odm_get_rf_reg(dm, ODM_RF_PATH_A, 0x18, RFREGOFFSETMASK);

	if (psd_fc_channel > 14) {
		rf_reg18_9_8 = 1;

		if (psd_fc_channel >= 36 && psd_fc_channel <= 64)
			ag_rf_mode_reg = 0x1;
		else if (psd_fc_channel >= 100 && psd_fc_channel <= 140)
			ag_rf_mode_reg = 0x3;
		else if (psd_fc_channel > 140)
			ag_rf_mode_reg = 0x5;
	}

	/* Set RF fc*/
	odm_set_rf_reg(dm, ODM_RF_PATH_A, 0x18, 0xff, psd_fc_channel);
	odm_set_rf_reg(dm, ODM_RF_PATH_A, 0x18, 0x300, rf_reg18_9_8);
	/*2b'11: 20MHz, 2b'10: 40MHz, 2b'01: 80MHz */
	odm_set_rf_reg(dm, ODM_RF_PATH_A, 0x18, 0xc00,
		       dm_psd_table->psd_bw_rf_reg);
	/* Set RF ag fc mode*/
	odm_set_rf_reg(dm, ODM_RF_PATH_A, 0x18, 0xf0000, ag_rf_mode_reg);

	ODM_RT_TRACE(dm, ODM_COMP_API, "0xc50=((0x%x))\n",
		     odm_get_bb_reg(dm, 0xc50, MASKDWORD));
	ODM_RT_TRACE(dm, ODM_COMP_API, "RF0x18=((0x%x))\n",
		     odm_get_rf_reg(dm, ODM_RF_PATH_A, 0x18, RFREGOFFSETMASK));

	/*[Stop 3-wires]*/
	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		odm_set_bb_reg(dm, 0xc00, 0xf, 0x4); /*	hardware 3-wire off */
		odm_set_bb_reg(dm, 0xe00, 0xf, 0x4); /*	hardware 3-wire off */
	} else {
		odm_set_bb_reg(dm, 0x88c, 0xf00000,
			       0xf); /* 3 wire Disable    88c[23:20]=0xf */
	}
	ODM_delay_us(10);

	if (stop_point > (dm_psd_table->fft_smp_point - 1))
		stop_point = (dm_psd_table->fft_smp_point - 1);

	if (start_point > (dm_psd_table->fft_smp_point - 1))
		start_point = (dm_psd_table->fft_smp_point - 1);

	if (start_point > stop_point)
		stop_point = start_point;

	if (stop_point > 127) /* limit of psd_result[128] */
		stop_point = 127;

	for (i = start_point; i <= stop_point; i++) {
		fft_max_half_bw = (dm_psd_table->fft_smp_point) >> 1;

		if (i < fft_max_half_bw)
			mod_tone_idx = i + fft_max_half_bw;
		else
			mod_tone_idx = i - fft_max_half_bw;

		psd_result_tmp = 0;
		for (t = 0; t < dm_psd_table->sw_avg_time; t++)
			psd_result_tmp +=
				phydm_get_psd_data(dm, mod_tone_idx, igi);
		psd_result =
			(u8)((psd_result_tmp / dm_psd_table->sw_avg_time)) -
			dm_psd_table->psd_pwr_common_offset;

		if (dm_psd_table->fft_smp_point == 128 &&
		    (dm_psd_table->noise_k_en)) {
			if (i > psd_result_cali_tone[noise_table_idx])
				noise_table_idx++;

			if (noise_table_idx > 6)
				noise_table_idx = 6;

			if (psd_result >= psd_result_cali_val[noise_table_idx])
				psd_result =
					psd_result -
					psd_result_cali_val[noise_table_idx];
			else
				psd_result = 0;

			dm_psd_table->psd_result[i] = psd_result;
		}

		ODM_RT_TRACE(dm, ODM_COMP_API, "[%d] N_cali = %d, PSD = %d\n",
			     mod_tone_idx, psd_result_cali_val[noise_table_idx],
			     psd_result);
	}

	/*[Start 3-wires]*/
	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		odm_set_bb_reg(dm, 0xc00, 0xf, 0x7); /*	hardware 3-wire on */
		odm_set_bb_reg(dm, 0xe00, 0xf, 0x7); /*	hardware 3-wire on */
	} else {
		odm_set_bb_reg(dm, 0x88c, 0xf00000,
			       0x0); /* 3 wire enable    88c[23:20]=0x0 */
	}
	ODM_delay_us(10);

	/*[Revert Reg]*/
	odm_set_bb_reg(dm, 0x520, 0xff0000, 0x0); /*start all TX queue*/
	odm_set_bb_reg(dm, 0x808, BIT(28), 1); /*enable CCK block*/
	odm_set_bb_reg(dm, 0x838, BIT(1), 0); /*enable OFDM RX CCA*/

	odm_set_bb_reg(dm, psd_igi_a_reg, 0xff,
		       dm_psd_table->initial_gain_backup);
	odm_set_bb_reg(dm, psd_igi_b_reg, 0xff,
		       dm_psd_table->initial_gain_backup);

	odm_set_rf_reg(dm, ODM_RF_PATH_A, 0x18, RFREGOFFSETMASK,
		       dm_psd_table->rf_0x18_bkp);

	ODM_RT_TRACE(dm, ODM_COMP_API, "PSD finished\n\n");

	dm->support_ability |= ODM_BB_DIG;
	dm->support_ability |= ODM_BB_FA_CNT;
	dm_psd_table->psd_in_progress = 0;
}