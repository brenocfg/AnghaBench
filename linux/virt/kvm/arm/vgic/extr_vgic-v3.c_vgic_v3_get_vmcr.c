#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vgic_vmcr {int fiqen; scalar_t__ grpen1; scalar_t__ grpen0; scalar_t__ pmr; scalar_t__ bpr; scalar_t__ abpr; scalar_t__ eoim; scalar_t__ cbpr; scalar_t__ ackctl; } ;
struct vgic_v3_cpu_if {scalar_t__ vgic_vmcr; } ;
struct TYPE_6__ {struct vgic_v3_cpu_if vgic_v3; } ;
struct TYPE_7__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_5__* kvm; TYPE_2__ arch; } ;
struct TYPE_8__ {scalar_t__ vgic_model; } ;
struct TYPE_9__ {TYPE_3__ vgic; } ;
struct TYPE_10__ {TYPE_4__ arch; } ;

/* Variables and functions */
 scalar_t__ ICH_VMCR_ACK_CTL_MASK ; 
 scalar_t__ ICH_VMCR_ACK_CTL_SHIFT ; 
 scalar_t__ ICH_VMCR_BPR0_MASK ; 
 scalar_t__ ICH_VMCR_BPR0_SHIFT ; 
 scalar_t__ ICH_VMCR_BPR1_MASK ; 
 scalar_t__ ICH_VMCR_BPR1_SHIFT ; 
 scalar_t__ ICH_VMCR_CBPR_MASK ; 
 scalar_t__ ICH_VMCR_CBPR_SHIFT ; 
 scalar_t__ ICH_VMCR_ENG0_MASK ; 
 scalar_t__ ICH_VMCR_ENG0_SHIFT ; 
 scalar_t__ ICH_VMCR_ENG1_MASK ; 
 scalar_t__ ICH_VMCR_ENG1_SHIFT ; 
 scalar_t__ ICH_VMCR_EOIM_MASK ; 
 scalar_t__ ICH_VMCR_EOIM_SHIFT ; 
 scalar_t__ ICH_VMCR_FIQ_EN_MASK ; 
 scalar_t__ ICH_VMCR_FIQ_EN_SHIFT ; 
 scalar_t__ ICH_VMCR_PMR_MASK ; 
 scalar_t__ ICH_VMCR_PMR_SHIFT ; 
 scalar_t__ KVM_DEV_TYPE_ARM_VGIC_V2 ; 

void vgic_v3_get_vmcr(struct kvm_vcpu *vcpu, struct vgic_vmcr *vmcrp)
{
	struct vgic_v3_cpu_if *cpu_if = &vcpu->arch.vgic_cpu.vgic_v3;
	u32 model = vcpu->kvm->arch.vgic.vgic_model;
	u32 vmcr;

	vmcr = cpu_if->vgic_vmcr;

	if (model == KVM_DEV_TYPE_ARM_VGIC_V2) {
		vmcrp->ackctl = (vmcr & ICH_VMCR_ACK_CTL_MASK) >>
			ICH_VMCR_ACK_CTL_SHIFT;
		vmcrp->fiqen = (vmcr & ICH_VMCR_FIQ_EN_MASK) >>
			ICH_VMCR_FIQ_EN_SHIFT;
	} else {
		/*
		 * When emulating GICv3 on GICv3 with SRE=1 on the
		 * VFIQEn bit is RES1 and the VAckCtl bit is RES0.
		 */
		vmcrp->fiqen = 1;
		vmcrp->ackctl = 0;
	}

	vmcrp->cbpr = (vmcr & ICH_VMCR_CBPR_MASK) >> ICH_VMCR_CBPR_SHIFT;
	vmcrp->eoim = (vmcr & ICH_VMCR_EOIM_MASK) >> ICH_VMCR_EOIM_SHIFT;
	vmcrp->abpr = (vmcr & ICH_VMCR_BPR1_MASK) >> ICH_VMCR_BPR1_SHIFT;
	vmcrp->bpr  = (vmcr & ICH_VMCR_BPR0_MASK) >> ICH_VMCR_BPR0_SHIFT;
	vmcrp->pmr  = (vmcr & ICH_VMCR_PMR_MASK) >> ICH_VMCR_PMR_SHIFT;
	vmcrp->grpen0 = (vmcr & ICH_VMCR_ENG0_MASK) >> ICH_VMCR_ENG0_SHIFT;
	vmcrp->grpen1 = (vmcr & ICH_VMCR_ENG1_MASK) >> ICH_VMCR_ENG1_SHIFT;
}