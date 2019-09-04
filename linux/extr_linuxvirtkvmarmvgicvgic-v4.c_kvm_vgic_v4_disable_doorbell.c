#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int irq; } ;
struct TYPE_6__ {TYPE_1__ its_vpe; } ;
struct TYPE_7__ {TYPE_2__ vgic_v3; } ;
struct TYPE_8__ {TYPE_3__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_4__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int) ; 
 scalar_t__ vgic_supports_direct_msis (int /*<<< orphan*/ ) ; 

void kvm_vgic_v4_disable_doorbell(struct kvm_vcpu *vcpu)
{
	if (vgic_supports_direct_msis(vcpu->kvm)) {
		int irq = vcpu->arch.vgic_cpu.vgic_v3.its_vpe.irq;
		if (irq)
			disable_irq(irq);
	}
}