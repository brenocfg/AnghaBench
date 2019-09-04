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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct rt_adcsmp {scalar_t__ la_trig_mode; scalar_t__ la_trig_sig_sel; scalar_t__ la_dbg_port; scalar_t__ la_trigger_edge; scalar_t__ la_smp_rate; } ;
struct phy_dm_struct {int support_ic_type; struct rt_adcsmp adcsmp; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MASKDWORD ; 
 int /*<<< orphan*/  ODM_COMP_UNCOND ; 
 int ODM_IC_11AC_SERIES ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ PHYDM_ADC_RF0_TRIG ; 
 scalar_t__ PHYDM_ADC_RF1_TRIG ; 
 scalar_t__ PHYDM_MAC_TRIG ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,scalar_t__) ; 

void phydm_la_mode_bb_setting(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rt_adcsmp *adc_smp = &dm->adcsmp;

	u8 trig_mode = adc_smp->la_trig_mode;
	u32 trig_sig_sel = adc_smp->la_trig_sig_sel;
	u32 dbg_port = adc_smp->la_dbg_port;
	u8 is_trigger_edge = adc_smp->la_trigger_edge;
	u8 sampling_rate = adc_smp->la_smp_rate;

	ODM_RT_TRACE(
		dm, ODM_COMP_UNCOND,
		"1. [LA mode bb_setting] trig_mode = ((%d)), dbg_port = ((0x%x)), Trig_Edge = ((%d)), smp_rate = ((%d)), Trig_Sel = ((0x%x))\n",
		trig_mode, dbg_port, is_trigger_edge, sampling_rate,
		trig_sig_sel);

	if (trig_mode == PHYDM_MAC_TRIG)
		trig_sig_sel = 0; /*ignore this setting*/

	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		if (trig_mode == PHYDM_ADC_RF0_TRIG) {
			/*DBGOUT_RFC_a[31:0]*/
			odm_set_bb_reg(dm, 0x8f8,
				       BIT(25) | BIT(24) | BIT(23) | BIT(22),
				       9);
		} else if (trig_mode == PHYDM_ADC_RF1_TRIG) {
			/*DBGOUT_RFC_b[31:0]*/
			odm_set_bb_reg(dm, 0x8f8,
				       BIT(25) | BIT(24) | BIT(23) | BIT(22),
				       8);
		} else {
			odm_set_bb_reg(dm, 0x8f8,
				       BIT(25) | BIT(24) | BIT(23) | BIT(22),
				       0);
		}
		/*
		 *	(0:) '{ofdm_dbg[31:0]}'
		 *	(1:) '{cca,crc32_fail,dbg_ofdm[29:0]}'
		 *	(2:) '{vbon,crc32_fail,dbg_ofdm[29:0]}'
		 *	(3:) '{cca,crc32_ok,dbg_ofdm[29:0]}'
		 *	(4:) '{vbon,crc32_ok,dbg_ofdm[29:0]}'
		 *	(5:) '{dbg_iqk_anta}'
		 *	(6:) '{cca,ofdm_crc_ok,dbg_dp_anta[29:0]}'
		 *	(7:) '{dbg_iqk_antb}'
		 *	(8:) '{DBGOUT_RFC_b[31:0]}'
		 *	(9:) '{DBGOUT_RFC_a[31:0]}'
		 *	(a:) '{dbg_ofdm}'
		 *	(b:) '{dbg_cck}'
		 */

		/*disable dbg clk gating*/
		odm_set_bb_reg(dm, 0x198C, BIT(2) | BIT(1) | BIT(0), 7);

		/*0x95C[4:0], BB debug port bit*/
		odm_set_bb_reg(dm, 0x95C, 0x1f, trig_sig_sel);
		odm_set_bb_reg(dm, 0x8FC, MASKDWORD, dbg_port);
		/*0: posedge, 1: negedge*/
		odm_set_bb_reg(dm, 0x95C, BIT(31), is_trigger_edge);
		odm_set_bb_reg(dm, 0x95c, 0xe0, sampling_rate);
		/*	(0:) '80MHz'
		 *	(1:) '40MHz'
		 *	(2:) '20MHz'
		 *	(3:) '10MHz'
		 *	(4:) '5MHz'
		 *	(5:) '2.5MHz'
		 *	(6:) '1.25MHz'
		 *	(7:) '160MHz (for BW160 ic)'
		 */
	} else {
		/*0x9A0[4:0], BB debug port bit*/
		odm_set_bb_reg(dm, 0x9a0, 0x1f, trig_sig_sel);
		odm_set_bb_reg(dm, 0x908, MASKDWORD, dbg_port);
		/*0: posedge, 1: negedge*/
		odm_set_bb_reg(dm, 0x9A0, BIT(31), is_trigger_edge);
		odm_set_bb_reg(dm, 0x9A0, 0xe0, sampling_rate);
		/*	(0:) '80MHz'
		 *	(1:) '40MHz'
		 *	(2:) '20MHz'
		 *	(3:) '10MHz'
		 *	(4:) '5MHz'
		 *	(5:) '2.5MHz'
		 *	(6:) '1.25MHz'
		 *	(7:) '160MHz (for BW160 ic)'
		 */
	}
}