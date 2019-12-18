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
typedef  int /*<<< orphan*/  vm_vaddr_t ;
typedef  scalar_t__ vm_paddr_t ;
struct kvm_vm {int dummy; } ;

/* Variables and functions */
 scalar_t__ kvm_userspace_memory_region_find (struct kvm_vm*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sync_global_to_guest (struct kvm_vm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ucall_exit_mmio_addr ; 
 int /*<<< orphan*/  virt_pg_map (struct kvm_vm*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ucall_mmio_init(struct kvm_vm *vm, vm_paddr_t gpa)
{
	if (kvm_userspace_memory_region_find(vm, gpa, gpa + 1))
		return false;

	virt_pg_map(vm, gpa, gpa, 0);

	ucall_exit_mmio_addr = (vm_vaddr_t *)gpa;
	sync_global_to_guest(vm, ucall_exit_mmio_addr);

	return true;
}