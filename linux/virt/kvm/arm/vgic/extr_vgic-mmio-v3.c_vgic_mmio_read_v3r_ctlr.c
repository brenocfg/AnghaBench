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
struct vgic_cpu {scalar_t__ lpis_enabled; } ;
struct TYPE_2__ {struct vgic_cpu vgic_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 unsigned long GICR_CTLR_ENABLE_LPIS ; 

__attribute__((used)) static unsigned long vgic_mmio_read_v3r_ctlr(struct kvm_vcpu *vcpu,
					     gpa_t addr, unsigned int len)
{
	struct vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;

	return vgic_cpu->lpis_enabled ? GICR_CTLR_ENABLE_LPIS : 0;
}