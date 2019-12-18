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
typedef  int uint32_t ;

/* Variables and functions */
 int F_CPU ; 
 int SCB_ICSR ; 
 int SCB_ICSR_PENDSTSET ; 
 int SYST_CVR ; 
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __enable_irq () ; 
 int systick_millis_count ; 

uint32_t micros(void)
{
	uint32_t count, current, istatus;

	__disable_irq();
	current = SYST_CVR;
	count = systick_millis_count;
	istatus = SCB_ICSR;	// bit 26 indicates if systick exception pending
	__enable_irq();
	 //systick_current = current;
	 //systick_count = count;
	 //systick_istatus = istatus & SCB_ICSR_PENDSTSET ? 1 : 0;
	if ((istatus & SCB_ICSR_PENDSTSET) && current > 50) count++;
	current = ((F_CPU / 1000) - 1) - current;
	return count * 1000 + current / (F_CPU / 1000000);
}