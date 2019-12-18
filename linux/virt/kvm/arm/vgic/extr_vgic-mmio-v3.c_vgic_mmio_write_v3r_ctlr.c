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
struct vgic_cpu {int lpis_enabled; } ;
struct TYPE_2__ {struct vgic_cpu vgic_cpu; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 unsigned long GICR_CTLR_ENABLE_LPIS ; 
 int /*<<< orphan*/  vgic_enable_lpis (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_flush_pending_lpis (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_has_its (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_its_invalidate_cache (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vgic_mmio_write_v3r_ctlr(struct kvm_vcpu *vcpu,
				     gpa_t addr, unsigned int len,
				     unsigned long val)
{
	struct vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	bool was_enabled = vgic_cpu->lpis_enabled;

	if (!vgic_has_its(vcpu->kvm))
		return;

	vgic_cpu->lpis_enabled = val & GICR_CTLR_ENABLE_LPIS;

	if (was_enabled && !vgic_cpu->lpis_enabled) {
		vgic_flush_pending_lpis(vcpu);
		vgic_its_invalidate_cache(vcpu->kvm);
	}

	if (!was_enabled && vgic_cpu->lpis_enabled)
		vgic_enable_lpis(vcpu);
}