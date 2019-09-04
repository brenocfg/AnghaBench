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
struct vcpu_runstate_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  xen_get_runstate_snapshot_cpu (struct vcpu_runstate_info*,int /*<<< orphan*/ ) ; 

void xen_get_runstate_snapshot(struct vcpu_runstate_info *res)
{
	xen_get_runstate_snapshot_cpu(res, smp_processor_id());
}