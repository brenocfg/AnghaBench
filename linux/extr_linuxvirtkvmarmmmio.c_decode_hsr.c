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
struct TYPE_3__ {int sign_extend; unsigned long rt; } ;
struct TYPE_4__ {TYPE_1__ mmio_decode; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_inject_dabt (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_vcpu_dabt_get_as (struct kvm_vcpu*) ; 
 unsigned long kvm_vcpu_dabt_get_rd (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_dabt_iss1tw (struct kvm_vcpu*) ; 
 int kvm_vcpu_dabt_issext (struct kvm_vcpu*) ; 
 int kvm_vcpu_dabt_iswrite (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_get_hfar (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int decode_hsr(struct kvm_vcpu *vcpu, bool *is_write, int *len)
{
	unsigned long rt;
	int access_size;
	bool sign_extend;

	if (kvm_vcpu_dabt_iss1tw(vcpu)) {
		/* page table accesses IO mem: tell guest to fix its TTBR */
		kvm_inject_dabt(vcpu, kvm_vcpu_get_hfar(vcpu));
		return 1;
	}

	access_size = kvm_vcpu_dabt_get_as(vcpu);
	if (unlikely(access_size < 0))
		return access_size;

	*is_write = kvm_vcpu_dabt_iswrite(vcpu);
	sign_extend = kvm_vcpu_dabt_issext(vcpu);
	rt = kvm_vcpu_dabt_get_rd(vcpu);

	*len = access_size;
	vcpu->arch.mmio_decode.sign_extend = sign_extend;
	vcpu->arch.mmio_decode.rt = rt;

	return 0;
}