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
struct rt_adcsmp_string {int length; } ;
struct rt_adcsmp {struct rt_adcsmp_string adc_smp_buf; } ;
struct phy_dm_struct {struct rt_adcsmp adcsmp; } ;
typedef  int s32 ;

/* Variables and functions */

s32 adc_smp_get_sample_counts(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rt_adcsmp *adc_smp = &dm->adcsmp;
	struct rt_adcsmp_string *adc_smp_buf = &adc_smp->adc_smp_buf;

	return (adc_smp_buf->length >> 2) - 2;
}