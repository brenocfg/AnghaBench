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
typedef  int u32 ;
struct vgic_vmcr {int grpen0; int grpen1; int ackctl; int fiqen; int cbpr; int eoim; int abpr; int bpr; int pmr; } ;
struct vgic_v2_cpu_if {int vgic_vmcr; } ;
struct TYPE_3__ {struct vgic_v2_cpu_if vgic_v2; } ;
struct TYPE_4__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int GICH_VMCR_ACK_CTL_MASK ; 
 int GICH_VMCR_ACK_CTL_SHIFT ; 
 int GICH_VMCR_ALIAS_BINPOINT_MASK ; 
 int GICH_VMCR_ALIAS_BINPOINT_SHIFT ; 
 int GICH_VMCR_BINPOINT_MASK ; 
 int GICH_VMCR_BINPOINT_SHIFT ; 
 int GICH_VMCR_CBPR_MASK ; 
 int GICH_VMCR_CBPR_SHIFT ; 
 int GICH_VMCR_ENABLE_GRP0_MASK ; 
 int GICH_VMCR_ENABLE_GRP0_SHIFT ; 
 int GICH_VMCR_ENABLE_GRP1_MASK ; 
 int GICH_VMCR_ENABLE_GRP1_SHIFT ; 
 int GICH_VMCR_EOI_MODE_MASK ; 
 int GICH_VMCR_EOI_MODE_SHIFT ; 
 int GICH_VMCR_FIQ_EN_MASK ; 
 int GICH_VMCR_FIQ_EN_SHIFT ; 
 int GICH_VMCR_PRIMASK_MASK ; 
 int GICH_VMCR_PRIMASK_SHIFT ; 
 int GICV_PMR_PRIORITY_SHIFT ; 

void vgic_v2_set_vmcr(struct kvm_vcpu *vcpu, struct vgic_vmcr *vmcrp)
{
	struct vgic_v2_cpu_if *cpu_if = &vcpu->arch.vgic_cpu.vgic_v2;
	u32 vmcr;

	vmcr = (vmcrp->grpen0 << GICH_VMCR_ENABLE_GRP0_SHIFT) &
		GICH_VMCR_ENABLE_GRP0_MASK;
	vmcr |= (vmcrp->grpen1 << GICH_VMCR_ENABLE_GRP1_SHIFT) &
		GICH_VMCR_ENABLE_GRP1_MASK;
	vmcr |= (vmcrp->ackctl << GICH_VMCR_ACK_CTL_SHIFT) &
		GICH_VMCR_ACK_CTL_MASK;
	vmcr |= (vmcrp->fiqen << GICH_VMCR_FIQ_EN_SHIFT) &
		GICH_VMCR_FIQ_EN_MASK;
	vmcr |= (vmcrp->cbpr << GICH_VMCR_CBPR_SHIFT) &
		GICH_VMCR_CBPR_MASK;
	vmcr |= (vmcrp->eoim << GICH_VMCR_EOI_MODE_SHIFT) &
		GICH_VMCR_EOI_MODE_MASK;
	vmcr |= (vmcrp->abpr << GICH_VMCR_ALIAS_BINPOINT_SHIFT) &
		GICH_VMCR_ALIAS_BINPOINT_MASK;
	vmcr |= (vmcrp->bpr << GICH_VMCR_BINPOINT_SHIFT) &
		GICH_VMCR_BINPOINT_MASK;
	vmcr |= ((vmcrp->pmr >> GICV_PMR_PRIORITY_SHIFT) <<
		 GICH_VMCR_PRIMASK_SHIFT) & GICH_VMCR_PRIMASK_MASK;

	cpu_if->vgic_vmcr = vmcr;
}