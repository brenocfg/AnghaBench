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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCR_TVM ; 
 int /*<<< orphan*/  stage2_flush_vm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_toggle_cache (int /*<<< orphan*/ ,int,int) ; 
 int vcpu_has_cache_enabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * vcpu_hcr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * vcpu_pc (struct kvm_vcpu*) ; 

void kvm_toggle_cache(struct kvm_vcpu *vcpu, bool was_enabled)
{
	bool now_enabled = vcpu_has_cache_enabled(vcpu);

	/*
	 * If switching the MMU+caches on, need to invalidate the caches.
	 * If switching it off, need to clean the caches.
	 * Clean + invalidate does the trick always.
	 */
	if (now_enabled != was_enabled)
		stage2_flush_vm(vcpu->kvm);

	/* Caches are now on, stop trapping VM ops (until a S/W op) */
	if (now_enabled)
		*vcpu_hcr(vcpu) &= ~HCR_TVM;

	trace_kvm_toggle_cache(*vcpu_pc(vcpu), was_enabled, now_enabled);
}