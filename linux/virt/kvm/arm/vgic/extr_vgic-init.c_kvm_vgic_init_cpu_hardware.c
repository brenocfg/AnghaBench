#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ VGIC_V2 ; 
 int /*<<< orphan*/  __vgic_v3_init_lrs ; 
 int /*<<< orphan*/  kvm_call_hyp (int /*<<< orphan*/ ) ; 
 TYPE_1__ kvm_vgic_global_state ; 
 int /*<<< orphan*/  preemptible () ; 
 int /*<<< orphan*/  vgic_v2_init_lrs () ; 

void kvm_vgic_init_cpu_hardware(void)
{
	BUG_ON(preemptible());

	/*
	 * We want to make sure the list registers start out clear so that we
	 * only have the program the used registers.
	 */
	if (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_init_lrs();
	else
		kvm_call_hyp(__vgic_v3_init_lrs);
}