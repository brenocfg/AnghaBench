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
typedef  void* u8 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ length; } ;
struct rt_adcsmp {scalar_t__ adc_smp_state; TYPE_1__ adc_smp_buf; void* la_trigger_time; void* la_dma_type; void* la_trig_sig_sel; void* la_trig_mode; } ;
struct phy_dm_struct {struct rt_adcsmp adcsmp; } ;

/* Variables and functions */
 scalar_t__ ADCSMP_STATE_IDLE ; 
 scalar_t__ ADCSMP_STATE_SET ; 
 int /*<<< orphan*/  ODM_COMP_UNCOND ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  phydm_adc_smp_start (struct phy_dm_struct*) ; 
 int phydm_la_buffer_allocate (struct phy_dm_struct*) ; 

void adc_smp_set(void *dm_void, u8 trig_mode, u32 trig_sig_sel,
		 u8 dma_data_sig_sel, u32 trigger_time, u16 polling_time)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	bool is_set_success = true;
	struct rt_adcsmp *adc_smp = &dm->adcsmp;

	adc_smp->la_trig_mode = trig_mode;
	adc_smp->la_trig_sig_sel = trig_sig_sel;
	adc_smp->la_dma_type = dma_data_sig_sel;
	adc_smp->la_trigger_time = trigger_time;

	if (adc_smp->adc_smp_state != ADCSMP_STATE_IDLE)
		is_set_success = false;
	else if (adc_smp->adc_smp_buf.length == 0)
		is_set_success = phydm_la_buffer_allocate(dm);

	if (is_set_success) {
		adc_smp->adc_smp_state = ADCSMP_STATE_SET;

		ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
			     "[LA Set Success] LA_State=((%d))\n",
			     adc_smp->adc_smp_state);

		phydm_adc_smp_start(dm);
	} else {
		ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
			     "[LA Set Fail] LA_State=((%d))\n",
			     adc_smp->adc_smp_state);
	}
}