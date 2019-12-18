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
struct TYPE_2__ {int /*<<< orphan*/  gicv3_cpuif; } ;

/* Variables and functions */
 scalar_t__ has_vhe () ; 
 TYPE_1__ kvm_vgic_global_state ; 
 int /*<<< orphan*/  static_branch_unlikely (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool can_access_vgic_from_kernel(void)
{
	/*
	 * GICv2 can always be accessed from the kernel because it is
	 * memory-mapped, and VHE systems can access GICv3 EL2 system
	 * registers.
	 */
	return !static_branch_unlikely(&kvm_vgic_global_state.gicv3_cpuif) || has_vhe();
}