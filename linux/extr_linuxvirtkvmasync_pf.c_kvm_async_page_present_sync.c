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
struct kvm_vcpu {int dummy; } ;
struct kvm_async_pf {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void kvm_async_page_present_sync(struct kvm_vcpu *vcpu,
					       struct kvm_async_pf *work)
{
#ifdef CONFIG_KVM_ASYNC_PF_SYNC
	kvm_arch_async_page_present(vcpu, work);
#endif
}