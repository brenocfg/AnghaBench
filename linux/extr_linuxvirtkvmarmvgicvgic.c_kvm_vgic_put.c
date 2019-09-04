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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ VGIC_V2 ; 
 TYPE_1__ kvm_vgic_global_state ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vgic_initialized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_v2_put (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vgic_v3_put (struct kvm_vcpu*) ; 

void kvm_vgic_put(struct kvm_vcpu *vcpu)
{
	if (unlikely(!vgic_initialized(vcpu->kvm)))
		return;

	if (kvm_vgic_global_state.type == VGIC_V2)
		vgic_v2_put(vcpu);
	else
		vgic_v3_put(vcpu);
}