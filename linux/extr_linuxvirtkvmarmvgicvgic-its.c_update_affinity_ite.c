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
struct kvm_vcpu {int dummy; } ;
struct kvm {int dummy; } ;
struct its_ite {int /*<<< orphan*/  irq; TYPE_1__* collection; } ;
struct TYPE_2__ {int /*<<< orphan*/  target_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  its_is_collection_mapped (TYPE_1__*) ; 
 struct kvm_vcpu* kvm_get_vcpu (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_affinity (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 

__attribute__((used)) static void update_affinity_ite(struct kvm *kvm, struct its_ite *ite)
{
	struct kvm_vcpu *vcpu;

	if (!its_is_collection_mapped(ite->collection))
		return;

	vcpu = kvm_get_vcpu(kvm, ite->collection->target_addr);
	update_affinity(ite->irq, vcpu);
}