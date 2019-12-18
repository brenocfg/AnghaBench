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
struct vgic_cpu {int num_pri_bits; } ;
struct TYPE_2__ {struct vgic_cpu vgic_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */

__attribute__((used)) static inline int vgic_v3_max_apr_idx(struct kvm_vcpu *vcpu)
{
	struct vgic_cpu *cpu_if = &vcpu->arch.vgic_cpu;

	/*
	 * num_pri_bits are initialized with HW supported values.
	 * We can rely safely on num_pri_bits even if VM has not
	 * restored ICC_CTLR_EL1 before restoring APnR registers.
	 */
	switch (cpu_if->num_pri_bits) {
	case 7: return 3;
	case 6: return 1;
	default: return 0;
	}
}