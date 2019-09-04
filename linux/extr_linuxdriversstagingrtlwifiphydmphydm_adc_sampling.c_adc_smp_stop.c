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
struct rt_adcsmp {int /*<<< orphan*/  adc_smp_state; } ;
struct phy_dm_struct {struct rt_adcsmp adcsmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADCSMP_STATE_IDLE ; 
 int /*<<< orphan*/  ODM_COMP_UNCOND ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void adc_smp_stop(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rt_adcsmp *adc_smp = &dm->adcsmp;

	adc_smp->adc_smp_state = ADCSMP_STATE_IDLE;
	ODM_RT_TRACE(dm, ODM_COMP_UNCOND, "[LA_Stop] LA_state = ((%d))\n",
		     adc_smp->adc_smp_state);
}