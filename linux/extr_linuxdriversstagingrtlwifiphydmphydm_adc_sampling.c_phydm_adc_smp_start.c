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
struct rt_adcsmp {scalar_t__ adc_smp_state; int /*<<< orphan*/  la_trigger_time; int /*<<< orphan*/  la_dma_type; int /*<<< orphan*/  la_trig_sig_sel; int /*<<< orphan*/  la_trig_mode; int /*<<< orphan*/  la_count; scalar_t__ is_bb_trigger; } ;
struct phy_dm_struct {int support_ic_type; struct rt_adcsmp adcsmp; } ;

/* Variables and functions */
 scalar_t__ ADCSMP_STATE_QUERY ; 
 scalar_t__ ADCSMP_STATE_SET ; 
 int BIT (int) ; 
 int /*<<< orphan*/  ODM_COMP_UNCOND ; 
 int ODM_RTL8197F ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ODM_delay_ms (int) ; 
 int /*<<< orphan*/  adc_smp_set (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc_smp_stop (struct phy_dm_struct*) ; 
 int odm_read_1byte (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  odm_write_1byte (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  phydm_la_get_tx_pkt_buf (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_la_mode_bb_setting (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_la_mode_set_dma_type (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_la_mode_set_mac_iq_dump (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_la_mode_set_trigger_time (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phydm_adc_smp_start(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rt_adcsmp *adc_smp = &dm->adcsmp;
	u8 tmp_u1b;
	u8 while_cnt = 0;
	u8 polling_ok = false, target_polling_bit;

	phydm_la_mode_bb_setting(dm);
	phydm_la_mode_set_dma_type(dm, adc_smp->la_dma_type);
	phydm_la_mode_set_trigger_time(dm, adc_smp->la_trigger_time);

	if (dm->support_ic_type & ODM_RTL8197F) {
		odm_set_bb_reg(dm, 0xd00, BIT(26), 0x1);
	} else { /*for 8814A and 8822B?*/
		odm_write_1byte(dm, 0x198c, 0x7);
		odm_write_1byte(dm, 0x8b4, 0x80);
		/* odm_set_bb_reg(dm, 0x8b4, BIT(7), 1); */
	}

	phydm_la_mode_set_mac_iq_dump(dm);
	/* return; */

	target_polling_bit = (adc_smp->is_bb_trigger) ? BIT(1) : BIT(2);
	do { /*Poll time always use 100ms, when it exceed 2s, break while loop*/
		tmp_u1b = odm_read_1byte(dm, 0x7c0);

		if (adc_smp->adc_smp_state != ADCSMP_STATE_SET) {
			ODM_RT_TRACE(
				dm, ODM_COMP_UNCOND,
				"[state Error] adc_smp_state != ADCSMP_STATE_SET\n");
			break;

		} else if (tmp_u1b & target_polling_bit) {
			ODM_delay_ms(100);
			while_cnt = while_cnt + 1;
			continue;
		} else {
			ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
				     "[LA Query OK] polling_bit=((0x%x))\n",
				     target_polling_bit);
			polling_ok = true;
			if (dm->support_ic_type & ODM_RTL8197F)
				odm_set_bb_reg(dm, 0x7c0, BIT(0), 0x0);
			break;
		}
	} while (while_cnt < 20);

	if (adc_smp->adc_smp_state == ADCSMP_STATE_SET) {
		if (polling_ok)
			phydm_la_get_tx_pkt_buf(dm);
		else
			ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
				     "[Polling timeout]\n");
	}

	if (adc_smp->adc_smp_state == ADCSMP_STATE_SET)
		adc_smp->adc_smp_state = ADCSMP_STATE_QUERY;

	ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
		     "[LA mode] LA_pattern_count = ((%d))\n",
		     adc_smp->la_count);

	adc_smp_stop(dm);

	if (adc_smp->la_count == 0) {
		ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
			     "LA Dump finished ---------->\n\n\n");
		/**/
	} else {
		adc_smp->la_count--;
		ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
			     "LA Dump more ---------->\n\n\n");
		adc_smp_set(dm, adc_smp->la_trig_mode, adc_smp->la_trig_sig_sel,
			    adc_smp->la_dma_type, adc_smp->la_trigger_time, 0);
	}
}