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
typedef  int /*<<< orphan*/  smp_call_func_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  on_each_cpu_cond_mask (int (*) (int,void*),int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void on_each_cpu_cond(bool (*cond_func)(int cpu, void *info),
			smp_call_func_t func, void *info, bool wait,
			gfp_t gfp_flags)
{
	on_each_cpu_cond_mask(cond_func, func, info, wait, gfp_flags,
				cpu_online_mask);
}