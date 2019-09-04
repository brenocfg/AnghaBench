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
struct rt_adcsmp_string {int start_pos; int buffer_size; } ;
struct rt_adcsmp {int /*<<< orphan*/  adc_smp_state; struct rt_adcsmp_string adc_smp_buf; } ;
struct phy_dm_struct {int support_ic_type; struct rt_adcsmp adcsmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADCSMP_STATE_IDLE ; 
 int ODM_RTL8197F ; 
 int ODM_RTL8814A ; 
 int ODM_RTL8821C ; 
 int ODM_RTL8822B ; 

void adc_smp_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rt_adcsmp *adc_smp = &dm->adcsmp;
	struct rt_adcsmp_string *adc_smp_buf = &adc_smp->adc_smp_buf;

	adc_smp->adc_smp_state = ADCSMP_STATE_IDLE;

	if (dm->support_ic_type & ODM_RTL8814A) {
		adc_smp_buf->start_pos = 0x30000;
		adc_smp_buf->buffer_size = 0x10000;
	} else if (dm->support_ic_type & ODM_RTL8822B) {
		adc_smp_buf->start_pos = 0x20000;
		adc_smp_buf->buffer_size = 0x20000;
	} else if (dm->support_ic_type & ODM_RTL8197F) {
		adc_smp_buf->start_pos = 0x00000;
		adc_smp_buf->buffer_size = 0x10000;
	} else if (dm->support_ic_type & ODM_RTL8821C) {
		adc_smp_buf->start_pos = 0x8000;
		adc_smp_buf->buffer_size = 0x8000;
	}
}