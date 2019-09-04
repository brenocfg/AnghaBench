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
typedef  int /*<<< orphan*/  uint64_t ;
struct kvm_userspace_memory_region {int dummy; } ;
struct userspace_mem_region {struct kvm_userspace_memory_region region; } ;
struct kvm_vm {int dummy; } ;

/* Variables and functions */
 struct userspace_mem_region* userspace_mem_region_find (struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct kvm_userspace_memory_region *
kvm_userspace_memory_region_find(struct kvm_vm *vm, uint64_t start,
				 uint64_t end)
{
	struct userspace_mem_region *region;

	region = userspace_mem_region_find(vm, start, end);
	if (!region)
		return NULL;

	return &region->region;
}