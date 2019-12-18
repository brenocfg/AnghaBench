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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmx_pages {int dummy; } ;
struct TYPE_2__ {int guest_phys_addr; int memory_size; } ;
struct userspace_mem_region {int /*<<< orphan*/  unused_phy_pages; TYPE_1__ region; } ;
struct kvm_vm {int page_shift; } ;
typedef  int sparsebit_idx_t ;

/* Variables and functions */
 struct userspace_mem_region* memslot2region (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_map (struct vmx_pages*,struct kvm_vm*,int,int,int,int /*<<< orphan*/ ) ; 
 int sparsebit_next_clear (int /*<<< orphan*/ ,int) ; 

void nested_map_memslot(struct vmx_pages *vmx, struct kvm_vm *vm,
			uint32_t memslot, uint32_t eptp_memslot)
{
	sparsebit_idx_t i, last;
	struct userspace_mem_region *region =
		memslot2region(vm, memslot);

	i = (region->region.guest_phys_addr >> vm->page_shift) - 1;
	last = i + (region->region.memory_size >> vm->page_shift);
	for (;;) {
		i = sparsebit_next_clear(region->unused_phy_pages, i);
		if (i > last)
			break;

		nested_map(vmx, vm,
			   (uint64_t)i << vm->page_shift,
			   (uint64_t)i << vm->page_shift,
			   1 << vm->page_shift,
			   eptp_memslot);
	}
}