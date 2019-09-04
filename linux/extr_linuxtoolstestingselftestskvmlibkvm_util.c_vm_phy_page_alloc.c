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
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct userspace_mem_region {int /*<<< orphan*/  unused_phy_pages; } ;
struct kvm_vm {int page_size; int page_shift; } ;
typedef  int sparsebit_idx_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 struct userspace_mem_region* memslot2region (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparsebit_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sparsebit_is_set (int /*<<< orphan*/ ,int) ; 
 int sparsebit_next_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vm_dump (int /*<<< orphan*/ ,struct kvm_vm*,int) ; 

vm_paddr_t vm_phy_page_alloc(struct kvm_vm *vm,
	vm_paddr_t paddr_min, uint32_t memslot)
{
	struct userspace_mem_region *region;
	sparsebit_idx_t pg;

	TEST_ASSERT((paddr_min % vm->page_size) == 0, "Min physical address "
		"not divisible by page size.\n"
		"  paddr_min: 0x%lx page_size: 0x%x",
		paddr_min, vm->page_size);

	/* Locate memory region. */
	region = memslot2region(vm, memslot);

	/* Locate next available physical page at or above paddr_min. */
	pg = paddr_min >> vm->page_shift;

	if (!sparsebit_is_set(region->unused_phy_pages, pg)) {
		pg = sparsebit_next_set(region->unused_phy_pages, pg);
		if (pg == 0) {
			fprintf(stderr, "No guest physical page available, "
				"paddr_min: 0x%lx page_size: 0x%x memslot: %u",
				paddr_min, vm->page_size, memslot);
			fputs("---- vm dump ----\n", stderr);
			vm_dump(stderr, vm, 2);
			abort();
		}
	}

	/* Specify page as in use and return its address. */
	sparsebit_clear(region->unused_phy_pages, pg);

	return pg * vm->page_size;
}