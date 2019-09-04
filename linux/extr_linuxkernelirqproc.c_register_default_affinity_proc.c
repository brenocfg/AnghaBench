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

__attribute__((used)) static void register_default_affinity_proc(void)
{
#ifdef CONFIG_SMP
	proc_create("irq/default_smp_affinity", 0644, NULL,
		    &default_affinity_proc_fops);
#endif
}