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
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MASKBYTE0 ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 scalar_t__ ODM_REG_CCX_PERIOD_11AC ; 
 scalar_t__ ODM_REG_CCX_PERIOD_11N ; 
 scalar_t__ ODM_REG_FPGA0_IQK_11N ; 
 scalar_t__ ODM_REG_NHM_9E8_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH3_TO_TH0_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH3_TO_TH0_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH7_TO_TH4_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH7_TO_TH4_11N ; 
 scalar_t__ ODM_REG_NHM_TH8_11AC ; 
 scalar_t__ ODM_REG_NHM_TH9_TH10_11AC ; 
 scalar_t__ ODM_REG_NHM_TH9_TH10_11N ; 
 scalar_t__ ODM_REG_OFDM_FA_RSTC_11N ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  odm_write_2byte (struct phy_dm_struct*,scalar_t__,int) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 

void phydm_nhm_counter_statistics_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		/*PHY parameters initialize for n series*/

		/*0x894[31:16]=0x0xC350
		 *Time duration for NHM unit: us, 0xc350=200ms
		 */
		odm_write_2byte(dm, ODM_REG_CCX_PERIOD_11N + 2, 0xC350);
		/*0x890[31:16]=0xffff		th_9, th_10*/
		odm_write_2byte(dm, ODM_REG_NHM_TH9_TH10_11N + 2, 0xffff);
		/*0x898=0xffffff52		th_3, th_2, th_1, th_0*/
		odm_write_4byte(dm, ODM_REG_NHM_TH3_TO_TH0_11N, 0xffffff50);
		/*0x89c=0xffffffff		th_7, th_6, th_5, th_4*/
		odm_write_4byte(dm, ODM_REG_NHM_TH7_TO_TH4_11N, 0xffffffff);
		/*0xe28[7:0]=0xff		th_8*/
		odm_set_bb_reg(dm, ODM_REG_FPGA0_IQK_11N, MASKBYTE0, 0xff);
		/*0x890[10:8]=1		ignoreCCA ignore PHYTXON enable CCX*/
		odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N,
			       BIT(10) | BIT(9) | BIT(8), 0x1);
		/*0xc0c[7]=1			max power among all RX ants*/
		odm_set_bb_reg(dm, ODM_REG_OFDM_FA_RSTC_11N, BIT(7), 0x1);
	} else if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		/*PHY parameters initialize for ac series*/

		odm_write_2byte(dm, ODM_REG_CCX_PERIOD_11AC + 2, 0xC350);
		/*0x994[31:16]=0xffff		th_9, th_10*/
		odm_write_2byte(dm, ODM_REG_NHM_TH9_TH10_11AC + 2, 0xffff);
		/*0x998=0xffffff52		th_3, th_2, th_1, th_0*/
		odm_write_4byte(dm, ODM_REG_NHM_TH3_TO_TH0_11AC, 0xffffff50);
		/*0x99c=0xffffffff		th_7, th_6, th_5, th_4*/
		odm_write_4byte(dm, ODM_REG_NHM_TH7_TO_TH4_11AC, 0xffffffff);
		/*0x9a0[7:0]=0xff		th_8*/
		odm_set_bb_reg(dm, ODM_REG_NHM_TH8_11AC, MASKBYTE0, 0xff);
		/*0x994[10:8]=1		ignoreCCA ignore PHYTXON enable CCX*/
		odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC,
			       BIT(8) | BIT(9) | BIT(10), 0x1);
		/*0x9e8[7]=1			max power among all RX ants*/
		odm_set_bb_reg(dm, ODM_REG_NHM_9E8_11AC, BIT(0), 0x1);
	}
}