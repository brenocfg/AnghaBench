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
typedef  void* u8 ;
typedef  int u16 ;
struct psd_info {int fft_smp_point; void* noise_k_en; void* psd_fc_channel; void* sw_avg_time; } ;
struct phy_dm_struct {int support_ic_type; struct psd_info dm_psd_table; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ODM_IC_11AC_SERIES ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,void*) ; 

void phydm_psd_para_setting(void *dm_void, u8 sw_avg_time, u8 hw_avg_time,
			    u8 i_q_setting, u16 fft_smp_point, u8 ant_sel,
			    u8 psd_input, u8 channel, u8 noise_k_en)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct psd_info *dm_psd_table = &dm->dm_psd_table;
	u8 fft_smp_point_idx = 0;

	dm_psd_table->fft_smp_point = fft_smp_point;

	if (sw_avg_time == 0)
		sw_avg_time = 1;

	dm_psd_table->sw_avg_time = sw_avg_time;
	dm_psd_table->psd_fc_channel = channel;
	dm_psd_table->noise_k_en = noise_k_en;

	if (fft_smp_point == 128)
		fft_smp_point_idx = 0;
	else if (fft_smp_point == 256)
		fft_smp_point_idx = 1;
	else if (fft_smp_point == 512)
		fft_smp_point_idx = 2;
	else if (fft_smp_point == 1024)
		fft_smp_point_idx = 3;

	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		odm_set_bb_reg(dm, 0x910, BIT(11) | BIT(10), i_q_setting);
		odm_set_bb_reg(dm, 0x910, BIT(13) | BIT(12), hw_avg_time);
		odm_set_bb_reg(dm, 0x910, BIT(15) | BIT(14), fft_smp_point_idx);
		odm_set_bb_reg(dm, 0x910, BIT(17) | BIT(16), ant_sel);
		odm_set_bb_reg(dm, 0x910, BIT(23), psd_input);
	}

	/*bw = (*dm->band_width); //ODM_BW20M */
	/*channel = *(dm->channel);*/
}