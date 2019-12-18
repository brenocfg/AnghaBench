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
struct TYPE_2__ {int /*<<< orphan*/  remote_tlb_flush; } ;
struct kvm {int /*<<< orphan*/  tlbs_dirty; TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arch_flush_remote_tlb (struct kvm*) ; 
 scalar_t__ kvm_make_all_cpus_request (struct kvm*,int /*<<< orphan*/ ) ; 
 long smp_load_acquire (int /*<<< orphan*/ *) ; 

void kvm_flush_remote_tlbs(struct kvm *kvm)
{
	/*
	 * Read tlbs_dirty before setting KVM_REQ_TLB_FLUSH in
	 * kvm_make_all_cpus_request.
	 */
	long dirty_count = smp_load_acquire(&kvm->tlbs_dirty);

	/*
	 * We want to publish modifications to the page tables before reading
	 * mode. Pairs with a memory barrier in arch-specific code.
	 * - x86: smp_mb__after_srcu_read_unlock in vcpu_enter_guest
	 * and smp_mb in walk_shadow_page_lockless_begin/end.
	 * - powerpc: smp_mb in kvmppc_prepare_to_enter.
	 *
	 * There is already an smp_mb__after_atomic() before
	 * kvm_make_all_cpus_request() reads vcpu->mode. We reuse that
	 * barrier here.
	 */
	if (!kvm_arch_flush_remote_tlb(kvm)
	    || kvm_make_all_cpus_request(kvm, KVM_REQ_TLB_FLUSH))
		++kvm->stat.remote_tlb_flush;
	cmpxchg(&kvm->tlbs_dirty, dirty_count, 0);
}