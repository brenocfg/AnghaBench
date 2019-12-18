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
typedef  int vm_vaddr_t ;
typedef  int vm_paddr_t ;
typedef  size_t uint16_t ;
struct pageTableEntry {int address; int /*<<< orphan*/  present; } ;
struct pageMapL4Entry {int address; int /*<<< orphan*/  present; } ;
struct pageDirectoryPointerEntry {int address; int /*<<< orphan*/  present; } ;
struct pageDirectoryEntry {int address; int /*<<< orphan*/  present; } ;
struct kvm_vm {scalar_t__ mode; int pgd; int page_size; int /*<<< orphan*/  pgd_created; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int) ; 
 scalar_t__ VM_MODE_PXXV48_4K ; 
 void* addr_gpa2hva (struct kvm_vm*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

vm_paddr_t addr_gva2gpa(struct kvm_vm *vm, vm_vaddr_t gva)
{
	uint16_t index[4];
	struct pageMapL4Entry *pml4e;
	struct pageDirectoryPointerEntry *pdpe;
	struct pageDirectoryEntry *pde;
	struct pageTableEntry *pte;

	TEST_ASSERT(vm->mode == VM_MODE_PXXV48_4K, "Attempt to use "
		"unknown or unsupported guest mode, mode: 0x%x", vm->mode);

	index[0] = (gva >> 12) & 0x1ffu;
	index[1] = (gva >> 21) & 0x1ffu;
	index[2] = (gva >> 30) & 0x1ffu;
	index[3] = (gva >> 39) & 0x1ffu;

	if (!vm->pgd_created)
		goto unmapped_gva;
	pml4e = addr_gpa2hva(vm, vm->pgd);
	if (!pml4e[index[3]].present)
		goto unmapped_gva;

	pdpe = addr_gpa2hva(vm, pml4e[index[3]].address * vm->page_size);
	if (!pdpe[index[2]].present)
		goto unmapped_gva;

	pde = addr_gpa2hva(vm, pdpe[index[2]].address * vm->page_size);
	if (!pde[index[1]].present)
		goto unmapped_gva;

	pte = addr_gpa2hva(vm, pde[index[1]].address * vm->page_size);
	if (!pte[index[0]].present)
		goto unmapped_gva;

	return (pte[index[0]].address * vm->page_size) + (gva & 0xfffu);

unmapped_gva:
	TEST_ASSERT(false, "No mapping for vm virtual address, "
		    "gva: 0x%lx", gva);
	exit(EXIT_FAILURE);
}