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
struct vgic_vmcr {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ VGIC_V2 ; 
 TYPE_1__ kvm_vgic_global_state ; 
 int /*<<< orphan*/  vgic_v2_set_vmcr (struct kvm_vcpu*,struct vgic_vmcr*) ; 
 int /*<<< orphan*/  vgic_v3_set_vmcr (struct kvm_vcpu*,struct vgic_vmcr*) ; 

void vgic_set_vmcr(struct kvm_vcpu *vcpu, struct vgic_vmcr *vmcr)
{
	if (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_set_vmcr(vcpu, vmcr);
	else
		vgic_v3_set_vmcr(vcpu, vmcr);
}