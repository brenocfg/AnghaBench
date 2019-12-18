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
struct page {int dummy; } ;
struct kvm_vcpu {int cpu; unsigned int vcpu_id; int pre_pcpu; int preempted; int ready; scalar_t__ run; int /*<<< orphan*/  blocked_vcpu_list; int /*<<< orphan*/  wq; int /*<<< orphan*/ * pid; struct kvm* kvm; int /*<<< orphan*/  mutex; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  init_swait_queue_head (int /*<<< orphan*/ *) ; 
 int kvm_arch_vcpu_init (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_async_pf_vcpu_init (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_set_dy_eligible (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_vcpu_set_in_spin_loop (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ page_address (struct page*) ; 

int kvm_vcpu_init(struct kvm_vcpu *vcpu, struct kvm *kvm, unsigned id)
{
	struct page *page;
	int r;

	mutex_init(&vcpu->mutex);
	vcpu->cpu = -1;
	vcpu->kvm = kvm;
	vcpu->vcpu_id = id;
	vcpu->pid = NULL;
	init_swait_queue_head(&vcpu->wq);
	kvm_async_pf_vcpu_init(vcpu);

	vcpu->pre_pcpu = -1;
	INIT_LIST_HEAD(&vcpu->blocked_vcpu_list);

	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page) {
		r = -ENOMEM;
		goto fail;
	}
	vcpu->run = page_address(page);

	kvm_vcpu_set_in_spin_loop(vcpu, false);
	kvm_vcpu_set_dy_eligible(vcpu, false);
	vcpu->preempted = false;
	vcpu->ready = false;

	r = kvm_arch_vcpu_init(vcpu);
	if (r < 0)
		goto fail_free_run;
	return 0;

fail_free_run:
	free_page((unsigned long)vcpu->run);
fail:
	return r;
}