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
typedef  int /*<<< orphan*/  u32 ;
struct rt_adcsmp {scalar_t__ la_trig_mode; int is_bb_trigger; int la_trigger_edge; int la_mac_ref_mask; int la_trig_sig_sel; int la_dbg_port; } ;
struct phy_dm_struct {struct rt_adcsmp adcsmp; } ;

/* Variables and functions */
 int ADCSMP_TRIG_REG ; 
 int BIT (int) ; 
 int MASKDWORD ; 
 int /*<<< orphan*/  ODM_COMP_UNCOND ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ PHYDM_ADC_MAC_TRIG ; 
 scalar_t__ PHYDM_MAC_TRIG ; 
 int /*<<< orphan*/  odm_get_bb_reg (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  odm_set_mac_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  odm_write_1byte (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phydm_la_mode_set_mac_iq_dump(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rt_adcsmp *adc_smp = &dm->adcsmp;
	u32 reg_value;

	odm_write_1byte(dm, 0x7c0, 0); /*clear all 0x7c0*/
	odm_set_mac_reg(dm, 0x7c0, BIT(0), 1); /*Enable LA mode HW block*/

	if (adc_smp->la_trig_mode == PHYDM_MAC_TRIG) {
		adc_smp->is_bb_trigger = 0;
		odm_set_mac_reg(dm, 0x7c0, BIT(2),
				1); /*polling bit for MAC mode*/
		odm_set_mac_reg(
			dm, 0x7c0, BIT(4) | BIT(3),
			adc_smp->la_trigger_edge); /*trigger mode for MAC*/

		ODM_RT_TRACE(
			dm, ODM_COMP_UNCOND,
			"[MAC_trig] ref_mask = ((0x%x)), ref_value = ((0x%x)), dbg_port = ((0x%x))\n",
			adc_smp->la_mac_ref_mask, adc_smp->la_trig_sig_sel,
			adc_smp->la_dbg_port);
		/*[Set MAC Debug Port]*/
		odm_set_mac_reg(dm, 0xF4, BIT(16), 1);
		odm_set_mac_reg(dm, 0x38, 0xff0000, adc_smp->la_dbg_port);
		odm_set_mac_reg(dm, 0x7c4, MASKDWORD, adc_smp->la_mac_ref_mask);
		odm_set_mac_reg(dm, 0x7c8, MASKDWORD, adc_smp->la_trig_sig_sel);

	} else {
		adc_smp->is_bb_trigger = 1;
		odm_set_mac_reg(dm, 0x7c0, BIT(1),
				1); /*polling bit for BB ADC mode*/

		if (adc_smp->la_trig_mode == PHYDM_ADC_MAC_TRIG) {
			odm_set_mac_reg(
				dm, 0x7c0, BIT(3),
				1); /*polling bit for MAC trigger event*/
			odm_set_mac_reg(dm, 0x7c0, BIT(7) | BIT(6),
					adc_smp->la_trig_sig_sel);

			if (adc_smp->la_trig_sig_sel == ADCSMP_TRIG_REG)
				odm_set_mac_reg(
					dm, 0x7c0, BIT(5),
					1); /* manual trigger 0x7C0[5] = 0->1*/
		}
	}

	reg_value = odm_get_bb_reg(dm, 0x7c0, 0xff);
	ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
		     "4. [Set MAC IQ dump] 0x7c0[7:0] = ((0x%x))\n", reg_value);
}