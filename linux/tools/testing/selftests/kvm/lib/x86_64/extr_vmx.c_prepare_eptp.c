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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmx_pages {void* eptp; int /*<<< orphan*/  eptp_gpa; int /*<<< orphan*/  eptp_hva; } ;
struct kvm_vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_gva2gpa (struct kvm_vm*,uintptr_t) ; 
 int /*<<< orphan*/  addr_gva2hva (struct kvm_vm*,uintptr_t) ; 
 int /*<<< orphan*/  getpagesize () ; 
 scalar_t__ vm_vaddr_alloc (struct kvm_vm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void prepare_eptp(struct vmx_pages *vmx, struct kvm_vm *vm,
		  uint32_t eptp_memslot)
{
	vmx->eptp = (void *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->eptp_hva = addr_gva2hva(vm, (uintptr_t)vmx->eptp);
	vmx->eptp_gpa = addr_gva2gpa(vm, (uintptr_t)vmx->eptp);
}