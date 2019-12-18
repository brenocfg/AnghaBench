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
typedef  int uint64_t ;
struct kvm_vm {size_t page_size; size_t page_shift; int /*<<< orphan*/  vpages_mapped; int /*<<< orphan*/  vpages_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,...) ; 
 int sparsebit_is_clear_num (int /*<<< orphan*/ ,int,int) ; 
 int sparsebit_is_set_num (int /*<<< orphan*/ ,int,int) ; 
 int sparsebit_next_clear_num (int /*<<< orphan*/ ,int,int) ; 
 int sparsebit_next_set_num (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static vm_vaddr_t vm_vaddr_unused_gap(struct kvm_vm *vm, size_t sz,
				      vm_vaddr_t vaddr_min)
{
	uint64_t pages = (sz + vm->page_size - 1) >> vm->page_shift;

	/* Determine lowest permitted virtual page index. */
	uint64_t pgidx_start = (vaddr_min + vm->page_size - 1) >> vm->page_shift;
	if ((pgidx_start * vm->page_size) < vaddr_min)
		goto no_va_found;

	/* Loop over section with enough valid virtual page indexes. */
	if (!sparsebit_is_set_num(vm->vpages_valid,
		pgidx_start, pages))
		pgidx_start = sparsebit_next_set_num(vm->vpages_valid,
			pgidx_start, pages);
	do {
		/*
		 * Are there enough unused virtual pages available at
		 * the currently proposed starting virtual page index.
		 * If not, adjust proposed starting index to next
		 * possible.
		 */
		if (sparsebit_is_clear_num(vm->vpages_mapped,
			pgidx_start, pages))
			goto va_found;
		pgidx_start = sparsebit_next_clear_num(vm->vpages_mapped,
			pgidx_start, pages);
		if (pgidx_start == 0)
			goto no_va_found;

		/*
		 * If needed, adjust proposed starting virtual address,
		 * to next range of valid virtual addresses.
		 */
		if (!sparsebit_is_set_num(vm->vpages_valid,
			pgidx_start, pages)) {
			pgidx_start = sparsebit_next_set_num(
				vm->vpages_valid, pgidx_start, pages);
			if (pgidx_start == 0)
				goto no_va_found;
		}
	} while (pgidx_start != 0);

no_va_found:
	TEST_ASSERT(false, "No vaddr of specified pages available, "
		"pages: 0x%lx", pages);

	/* NOT REACHED */
	return -1;

va_found:
	TEST_ASSERT(sparsebit_is_set_num(vm->vpages_valid,
		pgidx_start, pages),
		"Unexpected, invalid virtual page index range,\n"
		"  pgidx_start: 0x%lx\n"
		"  pages: 0x%lx",
		pgidx_start, pages);
	TEST_ASSERT(sparsebit_is_clear_num(vm->vpages_mapped,
		pgidx_start, pages),
		"Unexpected, pages already mapped,\n"
		"  pgidx_start: 0x%lx\n"
		"  pages: 0x%lx",
		pgidx_start, pages);

	return pgidx_start * vm->page_size;
}