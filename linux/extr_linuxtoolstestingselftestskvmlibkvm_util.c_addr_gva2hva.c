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
struct kvm_vm {int dummy; } ;

/* Variables and functions */
 void* addr_gpa2hva (struct kvm_vm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addr_gva2gpa (struct kvm_vm*,int /*<<< orphan*/ ) ; 

void *addr_gva2hva(struct kvm_vm *vm, vm_vaddr_t gva)
{
	return addr_gpa2hva(vm, addr_gva2gpa(vm, gva));
}