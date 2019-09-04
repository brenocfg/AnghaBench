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
struct kvm_vm {scalar_t__ gdt; } ;
struct kvm_dtable {int /*<<< orphan*/  limit; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_UTIL_MIN_VADDR ; 
 int /*<<< orphan*/  getpagesize () ; 
 scalar_t__ vm_vaddr_alloc (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void kvm_setup_gdt(struct kvm_vm *vm, struct kvm_dtable *dt, int gdt_memslot,
			  int pgd_memslot)
{
	if (!vm->gdt)
		vm->gdt = vm_vaddr_alloc(vm, getpagesize(),
			KVM_UTIL_MIN_VADDR, gdt_memslot, pgd_memslot);

	dt->base = vm->gdt;
	dt->limit = getpagesize();
}