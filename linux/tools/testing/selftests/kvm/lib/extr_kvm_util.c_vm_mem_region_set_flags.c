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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct userspace_mem_region {TYPE_1__ region; } ;
struct kvm_vm {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_SET_USER_MEMORY_REGION ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct userspace_mem_region* memslot2region (struct kvm_vm*,int /*<<< orphan*/ ) ; 

void vm_mem_region_set_flags(struct kvm_vm *vm, uint32_t slot, uint32_t flags)
{
	int ret;
	struct userspace_mem_region *region;

	region = memslot2region(vm, slot);

	region->region.flags = flags;

	ret = ioctl(vm->fd, KVM_SET_USER_MEMORY_REGION, &region->region);

	TEST_ASSERT(ret == 0, "KVM_SET_USER_MEMORY_REGION IOCTL failed,\n"
		"  rc: %i errno: %i slot: %u flags: 0x%x",
		ret, errno, slot, flags);
}