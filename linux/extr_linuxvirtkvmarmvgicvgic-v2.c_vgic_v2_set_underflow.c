#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vgic_v2_cpu_if {int /*<<< orphan*/  vgic_hcr; } ;
struct TYPE_3__ {struct vgic_v2_cpu_if vgic_v2; } ;
struct TYPE_4__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  GICH_HCR_UIE ; 

void vgic_v2_set_underflow(struct kvm_vcpu *vcpu)
{
	struct vgic_v2_cpu_if *cpuif = &vcpu->arch.vgic_cpu.vgic_v2;

	cpuif->vgic_hcr |= GICH_HCR_UIE;
}