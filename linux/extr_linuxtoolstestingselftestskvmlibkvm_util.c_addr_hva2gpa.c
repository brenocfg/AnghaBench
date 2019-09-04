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
typedef  int vm_paddr_t ;
struct TYPE_2__ {int memory_size; scalar_t__ guest_phys_addr; } ;
struct userspace_mem_region {void* host_mem; TYPE_1__ region; struct userspace_mem_region* next; } ;
struct kvm_vm {struct userspace_mem_region* userspace_mem_region_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,void*) ; 

vm_paddr_t addr_hva2gpa(struct kvm_vm *vm, void *hva)
{
	struct userspace_mem_region *region;
	for (region = vm->userspace_mem_region_head; region;
	     region = region->next) {
		if ((hva >= region->host_mem)
			&& (hva <= (region->host_mem
				+ region->region.memory_size - 1)))
			return (vm_paddr_t) ((uintptr_t)
				region->region.guest_phys_addr
				+ (hva - (uintptr_t) region->host_mem));
	}

	TEST_ASSERT(false, "No mapping to a guest physical address, "
		"hva: %p", hva);
	return -1;
}