#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vgic_v2_cpu_if {int /*<<< orphan*/  vgic_vmcr; } ;
struct TYPE_4__ {struct vgic_v2_cpu_if vgic_v2; } ;
struct TYPE_5__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_6__ {scalar_t__ vctrl_base; } ;

/* Variables and functions */
 scalar_t__ GICH_VMCR ; 
 TYPE_3__ kvm_vgic_global_state ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

void vgic_v2_vmcr_sync(struct kvm_vcpu *vcpu)
{
	struct vgic_v2_cpu_if *cpu_if = &vcpu->arch.vgic_cpu.vgic_v2;

	cpu_if->vgic_vmcr = readl_relaxed(kvm_vgic_global_state.vctrl_base + GICH_VMCR);
}