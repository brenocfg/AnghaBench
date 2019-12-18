#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct its_vm {int nr_vpes; TYPE_3__** vpes; } ;
struct TYPE_4__ {struct its_vm its_vm; } ;
struct TYPE_5__ {TYPE_1__ vgic; } ;
struct kvm {TYPE_2__ arch; } ;
struct TYPE_6__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_IRQ_FLAGS ; 
 int /*<<< orphan*/  free_irq (int,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  irq_clear_status_flags (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_free_vcpu_irqs (struct its_vm*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__**) ; 
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,int) ; 

void vgic_v4_teardown(struct kvm *kvm)
{
	struct its_vm *its_vm = &kvm->arch.vgic.its_vm;
	int i;

	if (!its_vm->vpes)
		return;

	for (i = 0; i < its_vm->nr_vpes; i++) {
		struct kvm_vcpu *vcpu = kvm_get_vcpu(kvm, i);
		int irq = its_vm->vpes[i]->irq;

		irq_clear_status_flags(irq, DB_IRQ_FLAGS);
		free_irq(irq, vcpu);
	}

	its_free_vcpu_irqs(its_vm);
	kfree(its_vm->vpes);
	its_vm->nr_vpes = 0;
	its_vm->vpes = NULL;
}