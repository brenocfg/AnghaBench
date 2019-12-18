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
typedef  uintptr_t vm_vaddr_t ;
struct vmx_pages {void* enlightened_vmcs; void* enlightened_vmcs_gpa; void* enlightened_vmcs_hva; void* vp_assist; void* vp_assist_gpa; void* vp_assist_hva; void* vmwrite_hva; void* vmwrite; void* vmwrite_gpa; void* vmread_hva; void* vmread; void* vmread_gpa; void* shadow_vmcs; void* shadow_vmcs_gpa; void* shadow_vmcs_hva; void* msr_hva; void* msr; void* msr_gpa; void* vmcs; void* vmcs_gpa; void* vmcs_hva; void* vmxon; void* vmxon_gpa; void* vmxon_hva; } ;
struct kvm_vm {int dummy; } ;

/* Variables and functions */
 void* addr_gva2gpa (struct kvm_vm*,uintptr_t) ; 
 void* addr_gva2hva (struct kvm_vm*,uintptr_t) ; 
 int /*<<< orphan*/  getpagesize () ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 uintptr_t vm_vaddr_alloc (struct kvm_vm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct vmx_pages *
vcpu_alloc_vmx(struct kvm_vm *vm, vm_vaddr_t *p_vmx_gva)
{
	vm_vaddr_t vmx_gva = vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	struct vmx_pages *vmx = addr_gva2hva(vm, vmx_gva);

	/* Setup of a region of guest memory for the vmxon region. */
	vmx->vmxon = (void *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->vmxon_hva = addr_gva2hva(vm, (uintptr_t)vmx->vmxon);
	vmx->vmxon_gpa = addr_gva2gpa(vm, (uintptr_t)vmx->vmxon);

	/* Setup of a region of guest memory for a vmcs. */
	vmx->vmcs = (void *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->vmcs_hva = addr_gva2hva(vm, (uintptr_t)vmx->vmcs);
	vmx->vmcs_gpa = addr_gva2gpa(vm, (uintptr_t)vmx->vmcs);

	/* Setup of a region of guest memory for the MSR bitmap. */
	vmx->msr = (void *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->msr_hva = addr_gva2hva(vm, (uintptr_t)vmx->msr);
	vmx->msr_gpa = addr_gva2gpa(vm, (uintptr_t)vmx->msr);
	memset(vmx->msr_hva, 0, getpagesize());

	/* Setup of a region of guest memory for the shadow VMCS. */
	vmx->shadow_vmcs = (void *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->shadow_vmcs_hva = addr_gva2hva(vm, (uintptr_t)vmx->shadow_vmcs);
	vmx->shadow_vmcs_gpa = addr_gva2gpa(vm, (uintptr_t)vmx->shadow_vmcs);

	/* Setup of a region of guest memory for the VMREAD and VMWRITE bitmaps. */
	vmx->vmread = (void *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->vmread_hva = addr_gva2hva(vm, (uintptr_t)vmx->vmread);
	vmx->vmread_gpa = addr_gva2gpa(vm, (uintptr_t)vmx->vmread);
	memset(vmx->vmread_hva, 0, getpagesize());

	vmx->vmwrite = (void *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->vmwrite_hva = addr_gva2hva(vm, (uintptr_t)vmx->vmwrite);
	vmx->vmwrite_gpa = addr_gva2gpa(vm, (uintptr_t)vmx->vmwrite);
	memset(vmx->vmwrite_hva, 0, getpagesize());

	/* Setup of a region of guest memory for the VP Assist page. */
	vmx->vp_assist = (void *)vm_vaddr_alloc(vm, getpagesize(),
						0x10000, 0, 0);
	vmx->vp_assist_hva = addr_gva2hva(vm, (uintptr_t)vmx->vp_assist);
	vmx->vp_assist_gpa = addr_gva2gpa(vm, (uintptr_t)vmx->vp_assist);

	/* Setup of a region of guest memory for the enlightened VMCS. */
	vmx->enlightened_vmcs = (void *)vm_vaddr_alloc(vm, getpagesize(),
						       0x10000, 0, 0);
	vmx->enlightened_vmcs_hva =
		addr_gva2hva(vm, (uintptr_t)vmx->enlightened_vmcs);
	vmx->enlightened_vmcs_gpa =
		addr_gva2gpa(vm, (uintptr_t)vmx->enlightened_vmcs);

	*p_vmx_gva = vmx_gva;
	return vmx;
}