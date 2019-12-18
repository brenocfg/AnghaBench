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
struct vgic_state_iter {scalar_t__ dist_id; scalar_t__ vcpu_id; scalar_t__ nr_cpus; int /*<<< orphan*/  intid; } ;
struct vgic_irq {int /*<<< orphan*/  irq_lock; } ;
struct seq_file {scalar_t__ private; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  initialized; } ;
struct TYPE_3__ {TYPE_2__ vgic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,scalar_t__) ; 
 int /*<<< orphan*/  print_dist_state (struct seq_file*,TYPE_2__*) ; 
 int /*<<< orphan*/  print_irq_state (struct seq_file*,struct vgic_irq*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 struct vgic_irq* vgic_get_irq (struct kvm*,struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_put_irq (struct kvm*,struct vgic_irq*) ; 

__attribute__((used)) static int vgic_debug_show(struct seq_file *s, void *v)
{
	struct kvm *kvm = (struct kvm *)s->private;
	struct vgic_state_iter *iter = (struct vgic_state_iter *)v;
	struct vgic_irq *irq;
	struct kvm_vcpu *vcpu = NULL;
	unsigned long flags;

	if (iter->dist_id == 0) {
		print_dist_state(s, &kvm->arch.vgic);
		return 0;
	}

	if (!kvm->arch.vgic.initialized)
		return 0;

	if (iter->vcpu_id < iter->nr_cpus)
		vcpu = kvm_get_vcpu(kvm, iter->vcpu_id);

	irq = vgic_get_irq(kvm, vcpu, iter->intid);
	if (!irq) {
		seq_printf(s, "       LPI %4d freed\n", iter->intid);
		return 0;
	}

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	print_irq_state(s, irq, vcpu);
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

	vgic_put_irq(kvm, irq);
	return 0;
}