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
typedef  scalar_t__ u64 ;
struct vcpu_runstate_info {scalar_t__* time; } ;

/* Variables and functions */
 size_t RUNSTATE_offline ; 
 size_t RUNSTATE_runnable ; 
 int /*<<< orphan*/  xen_get_runstate_snapshot_cpu (struct vcpu_runstate_info*,int) ; 

u64 xen_steal_clock(int cpu)
{
	struct vcpu_runstate_info state;

	xen_get_runstate_snapshot_cpu(&state, cpu);
	return state.time[RUNSTATE_runnable] + state.time[RUNSTATE_offline];
}