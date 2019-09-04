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
struct clock_event_device {int dummy; } ;
struct ce_unbind {int res; struct clock_event_device* ce; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  __clockevents_unbind ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,struct ce_unbind*,int) ; 

__attribute__((used)) static int clockevents_unbind(struct clock_event_device *ced, int cpu)
{
	struct ce_unbind cu = { .ce = ced, .res = -ENODEV };

	smp_call_function_single(cpu, __clockevents_unbind, &cu, 1);
	return cu.res;
}