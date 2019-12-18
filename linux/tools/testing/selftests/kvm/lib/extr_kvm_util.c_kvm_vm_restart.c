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
struct TYPE_2__ {int /*<<< orphan*/  memory_size; int /*<<< orphan*/  guest_phys_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  slot; } ;
struct userspace_mem_region {TYPE_1__ region; struct userspace_mem_region* next; } ;
struct kvm_vm {int /*<<< orphan*/  fd; struct userspace_mem_region* userspace_mem_region_head; scalar_t__ has_irqchip; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_SET_USER_MEMORY_REGION ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_create_irqchip (struct kvm_vm*) ; 
 int /*<<< orphan*/  vm_open (struct kvm_vm*,int) ; 

void kvm_vm_restart(struct kvm_vm *vmp, int perm)
{
	struct userspace_mem_region *region;

	vm_open(vmp, perm);
	if (vmp->has_irqchip)
		vm_create_irqchip(vmp);

	for (region = vmp->userspace_mem_region_head; region;
		region = region->next) {
		int ret = ioctl(vmp->fd, KVM_SET_USER_MEMORY_REGION, &region->region);
		TEST_ASSERT(ret == 0, "KVM_SET_USER_MEMORY_REGION IOCTL failed,\n"
			    "  rc: %i errno: %i\n"
			    "  slot: %u flags: 0x%x\n"
			    "  guest_phys_addr: 0x%lx size: 0x%lx",
			    ret, errno, region->region.slot,
			    region->region.flags,
			    region->region.guest_phys_addr,
			    region->region.memory_size);
	}
}