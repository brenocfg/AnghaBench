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
struct TYPE_2__ {int guest_phys_addr; int memory_size; } ;
struct userspace_mem_region {TYPE_1__ region; scalar_t__ host_mem; struct userspace_mem_region* next; } ;
struct kvm_vm {struct userspace_mem_region* userspace_mem_region_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int) ; 

void *addr_gpa2hva(struct kvm_vm *vm, vm_paddr_t gpa)
{
	struct userspace_mem_region *region;
	for (region = vm->userspace_mem_region_head; region;
	     region = region->next) {
		if ((gpa >= region->region.guest_phys_addr)
			&& (gpa <= (region->region.guest_phys_addr
				+ region->region.memory_size - 1)))
			return (void *) ((uintptr_t) region->host_mem
				+ (gpa - region->region.guest_phys_addr));
	}

	TEST_ASSERT(false, "No vm physical memory at 0x%lx", gpa);
	return NULL;
}