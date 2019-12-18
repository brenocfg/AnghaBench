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
struct vgic_vmcr {int grpen0; int grpen1; int ackctl; int fiqen; int cbpr; int eoim; unsigned long pmr; unsigned long bpr; unsigned long abpr; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 unsigned long GICV_PMR_PRIORITY_MASK ; 
 unsigned long GICV_PMR_PRIORITY_SHIFT ; 
#define  GIC_CPU_ALIAS_BINPOINT 131 
#define  GIC_CPU_BINPOINT 130 
#define  GIC_CPU_CTRL 129 
 unsigned long GIC_CPU_CTRL_AckCtl ; 
 unsigned long GIC_CPU_CTRL_CBPR ; 
 unsigned long GIC_CPU_CTRL_EOImodeNS ; 
 unsigned long GIC_CPU_CTRL_EnableGrp0 ; 
 unsigned long GIC_CPU_CTRL_EnableGrp1 ; 
 unsigned long GIC_CPU_CTRL_FIQEn ; 
#define  GIC_CPU_PRIMASK 128 
 int /*<<< orphan*/  vgic_get_vmcr (struct kvm_vcpu*,struct vgic_vmcr*) ; 
 int /*<<< orphan*/  vgic_set_vmcr (struct kvm_vcpu*,struct vgic_vmcr*) ; 

__attribute__((used)) static void vgic_mmio_write_vcpuif(struct kvm_vcpu *vcpu,
				   gpa_t addr, unsigned int len,
				   unsigned long val)
{
	struct vgic_vmcr vmcr;

	vgic_get_vmcr(vcpu, &vmcr);

	switch (addr & 0xff) {
	case GIC_CPU_CTRL:
		vmcr.grpen0 = !!(val & GIC_CPU_CTRL_EnableGrp0);
		vmcr.grpen1 = !!(val & GIC_CPU_CTRL_EnableGrp1);
		vmcr.ackctl = !!(val & GIC_CPU_CTRL_AckCtl);
		vmcr.fiqen = !!(val & GIC_CPU_CTRL_FIQEn);
		vmcr.cbpr = !!(val & GIC_CPU_CTRL_CBPR);
		vmcr.eoim = !!(val & GIC_CPU_CTRL_EOImodeNS);

		break;
	case GIC_CPU_PRIMASK:
		/*
		 * Our KVM_DEV_TYPE_ARM_VGIC_V2 device ABI exports the
		 * the PMR field as GICH_VMCR.VMPriMask rather than
		 * GICC_PMR.Priority, so we expose the upper five bits of
		 * priority mask to userspace using the lower bits in the
		 * unsigned long.
		 */
		vmcr.pmr = (val << GICV_PMR_PRIORITY_SHIFT) &
			GICV_PMR_PRIORITY_MASK;
		break;
	case GIC_CPU_BINPOINT:
		vmcr.bpr = val;
		break;
	case GIC_CPU_ALIAS_BINPOINT:
		vmcr.abpr = val;
		break;
	}

	vgic_set_vmcr(vcpu, &vmcr);
}