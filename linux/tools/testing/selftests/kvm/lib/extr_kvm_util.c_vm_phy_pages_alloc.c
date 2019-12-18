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
typedef  size_t vm_paddr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct userspace_mem_region {int /*<<< orphan*/  unused_phy_pages; } ;
struct kvm_vm {size_t page_size; size_t page_shift; } ;
typedef  size_t sparsebit_idx_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,...) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 struct userspace_mem_region* memslot2region (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparsebit_clear (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sparsebit_is_set (int /*<<< orphan*/ ,size_t) ; 
 size_t sparsebit_next_set (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vm_dump (int /*<<< orphan*/ ,struct kvm_vm*,int) ; 

vm_paddr_t vm_phy_pages_alloc(struct kvm_vm *vm, size_t num,
			      vm_paddr_t paddr_min, uint32_t memslot)
{
	struct userspace_mem_region *region;
	sparsebit_idx_t pg, base;

	TEST_ASSERT(num > 0, "Must allocate at least one page");

	TEST_ASSERT((paddr_min % vm->page_size) == 0, "Min physical address "
		"not divisible by page size.\n"
		"  paddr_min: 0x%lx page_size: 0x%x",
		paddr_min, vm->page_size);

	region = memslot2region(vm, memslot);
	base = pg = paddr_min >> vm->page_shift;

	do {
		for (; pg < base + num; ++pg) {
			if (!sparsebit_is_set(region->unused_phy_pages, pg)) {
				base = pg = sparsebit_next_set(region->unused_phy_pages, pg);
				break;
			}
		}
	} while (pg && pg != base + num);

	if (pg == 0) {
		fprintf(stderr, "No guest physical page available, "
			"paddr_min: 0x%lx page_size: 0x%x memslot: %u\n",
			paddr_min, vm->page_size, memslot);
		fputs("---- vm dump ----\n", stderr);
		vm_dump(stderr, vm, 2);
		abort();
	}

	for (pg = base; pg < base + num; ++pg)
		sparsebit_clear(region->unused_phy_pages, pg);

	return base * vm->page_size;
}