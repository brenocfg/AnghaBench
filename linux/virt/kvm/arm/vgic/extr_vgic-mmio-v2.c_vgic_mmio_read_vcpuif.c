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
typedef  unsigned long u32 ;
struct vgic_vmcr {unsigned long grpen0; unsigned long grpen1; unsigned long ackctl; unsigned long fiqen; unsigned long cbpr; unsigned long eoim; unsigned long pmr; unsigned long bpr; unsigned long abpr; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int GICC_ARCH_VERSION_V2 ; 
 unsigned long GICV_PMR_PRIORITY_MASK ; 
 unsigned long GICV_PMR_PRIORITY_SHIFT ; 
#define  GIC_CPU_ALIAS_BINPOINT 132 
#define  GIC_CPU_BINPOINT 131 
#define  GIC_CPU_CTRL 130 
 unsigned long GIC_CPU_CTRL_AckCtl_SHIFT ; 
 unsigned long GIC_CPU_CTRL_CBPR_SHIFT ; 
 unsigned long GIC_CPU_CTRL_EOImodeNS_SHIFT ; 
 unsigned long GIC_CPU_CTRL_EnableGrp0_SHIFT ; 
 unsigned long GIC_CPU_CTRL_EnableGrp1_SHIFT ; 
 unsigned long GIC_CPU_CTRL_FIQEn_SHIFT ; 
#define  GIC_CPU_IDENT 129 
#define  GIC_CPU_PRIMASK 128 
 int IMPLEMENTER_ARM ; 
 int PRODUCT_ID_KVM ; 
 int /*<<< orphan*/  vgic_get_vmcr (struct kvm_vcpu*,struct vgic_vmcr*) ; 

__attribute__((used)) static unsigned long vgic_mmio_read_vcpuif(struct kvm_vcpu *vcpu,
					   gpa_t addr, unsigned int len)
{
	struct vgic_vmcr vmcr;
	u32 val;

	vgic_get_vmcr(vcpu, &vmcr);

	switch (addr & 0xff) {
	case GIC_CPU_CTRL:
		val = vmcr.grpen0 << GIC_CPU_CTRL_EnableGrp0_SHIFT;
		val |= vmcr.grpen1 << GIC_CPU_CTRL_EnableGrp1_SHIFT;
		val |= vmcr.ackctl << GIC_CPU_CTRL_AckCtl_SHIFT;
		val |= vmcr.fiqen << GIC_CPU_CTRL_FIQEn_SHIFT;
		val |= vmcr.cbpr << GIC_CPU_CTRL_CBPR_SHIFT;
		val |= vmcr.eoim << GIC_CPU_CTRL_EOImodeNS_SHIFT;

		break;
	case GIC_CPU_PRIMASK:
		/*
		 * Our KVM_DEV_TYPE_ARM_VGIC_V2 device ABI exports the
		 * the PMR field as GICH_VMCR.VMPriMask rather than
		 * GICC_PMR.Priority, so we expose the upper five bits of
		 * priority mask to userspace using the lower bits in the
		 * unsigned long.
		 */
		val = (vmcr.pmr & GICV_PMR_PRIORITY_MASK) >>
			GICV_PMR_PRIORITY_SHIFT;
		break;
	case GIC_CPU_BINPOINT:
		val = vmcr.bpr;
		break;
	case GIC_CPU_ALIAS_BINPOINT:
		val = vmcr.abpr;
		break;
	case GIC_CPU_IDENT:
		val = ((PRODUCT_ID_KVM << 20) |
		       (GICC_ARCH_VERSION_V2 << 16) |
		       IMPLEMENTER_ARM);
		break;
	default:
		return 0;
	}

	return val;
}