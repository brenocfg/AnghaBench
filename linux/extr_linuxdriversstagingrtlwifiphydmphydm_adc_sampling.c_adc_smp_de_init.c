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
struct rt_adcsmp_string {int length; int /*<<< orphan*/  octet; } ;
struct rt_adcsmp {struct rt_adcsmp_string adc_smp_buf; } ;
struct phy_dm_struct {struct rt_adcsmp adcsmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  adc_smp_stop (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_free_memory (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 

void adc_smp_de_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rt_adcsmp *adc_smp = &dm->adcsmp;
	struct rt_adcsmp_string *adc_smp_buf = &adc_smp->adc_smp_buf;

	adc_smp_stop(dm);

	if (adc_smp_buf->length != 0x0) {
		odm_free_memory(dm, adc_smp_buf->octet, adc_smp_buf->length);
		adc_smp_buf->length = 0x0;
	}
}