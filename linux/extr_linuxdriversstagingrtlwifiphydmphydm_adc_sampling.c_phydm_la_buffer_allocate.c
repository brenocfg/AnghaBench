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
struct rt_adcsmp_string {scalar_t__ length; scalar_t__ buffer_size; int /*<<< orphan*/  octet; } ;
struct rt_adcsmp {struct rt_adcsmp_string adc_smp_buf; } ;
struct phy_dm_struct {struct rt_adcsmp adcsmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_UNCOND ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_allocate_memory (struct phy_dm_struct*,void**,scalar_t__) ; 

__attribute__((used)) static bool phydm_la_buffer_allocate(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rt_adcsmp *adc_smp = &dm->adcsmp;
	struct rt_adcsmp_string *adc_smp_buf = &adc_smp->adc_smp_buf;
	bool ret = false;

	ODM_RT_TRACE(dm, ODM_COMP_UNCOND, "[LA mode BufferAllocate]\n");

	if (adc_smp_buf->length == 0) {
		odm_allocate_memory(dm, (void **)&adc_smp_buf->octet,
				    adc_smp_buf->buffer_size);
		if (!adc_smp_buf->octet) {
			ret = false;
		} else {
			adc_smp_buf->length = adc_smp_buf->buffer_size;
			ret = true;
		}
	}

	return ret;
}