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

/* Variables and functions */
 int /*<<< orphan*/ ** iucv_irq_data ; 
 int /*<<< orphan*/ ** iucv_param ; 
 int /*<<< orphan*/ ** iucv_param_irq ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iucv_cpu_dead(unsigned int cpu)
{
	kfree(iucv_param_irq[cpu]);
	iucv_param_irq[cpu] = NULL;
	kfree(iucv_param[cpu]);
	iucv_param[cpu] = NULL;
	kfree(iucv_irq_data[cpu]);
	iucv_irq_data[cpu] = NULL;
	return 0;
}