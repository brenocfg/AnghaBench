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
struct kvm_memory_slot {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 unsigned long KVM_HVA_ERR_RO_BAD ; 
 int /*<<< orphan*/  KVM_PFN_ERR_RO_FAULT ; 
 int /*<<< orphan*/  KVM_PFN_NOSLOT ; 
 unsigned long __gfn_to_hva_many (struct kvm_memory_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hva_to_pfn (unsigned long,int,int*,int,int*) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 
 scalar_t__ memslot_is_readonly (struct kvm_memory_slot*) ; 

kvm_pfn_t __gfn_to_pfn_memslot(struct kvm_memory_slot *slot, gfn_t gfn,
			       bool atomic, bool *async, bool write_fault,
			       bool *writable)
{
	unsigned long addr = __gfn_to_hva_many(slot, gfn, NULL, write_fault);

	if (addr == KVM_HVA_ERR_RO_BAD) {
		if (writable)
			*writable = false;
		return KVM_PFN_ERR_RO_FAULT;
	}

	if (kvm_is_error_hva(addr)) {
		if (writable)
			*writable = false;
		return KVM_PFN_NOSLOT;
	}

	/* Do not map writable pfn in the readonly memslot. */
	if (writable && memslot_is_readonly(slot)) {
		*writable = false;
		writable = NULL;
	}

	return hva_to_pfn(addr, atomic, async, write_fault,
			  writable);
}