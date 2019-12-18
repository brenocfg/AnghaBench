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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmx_pages {int /*<<< orphan*/  vmxon_gpa; scalar_t__ vmxon; } ;

/* Variables and functions */
 int FEATURE_CONTROL_LOCKED ; 
 int FEATURE_CONTROL_VMXON_ENABLED_OUTSIDE_SMX ; 
 int /*<<< orphan*/  MSR_IA32_FEATURE_CONTROL ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR0_FIXED0 ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR0_FIXED1 ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR4_FIXED0 ; 
 int /*<<< orphan*/  MSR_IA32_VMX_CR4_FIXED1 ; 
 unsigned long X86_CR4_VMXE ; 
 unsigned long rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_revision () ; 
 scalar_t__ vmxon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

bool prepare_for_vmx_operation(struct vmx_pages *vmx)
{
	uint64_t feature_control;
	uint64_t required;
	unsigned long cr0;
	unsigned long cr4;

	/*
	 * Ensure bits in CR0 and CR4 are valid in VMX operation:
	 * - Bit X is 1 in _FIXED0: bit X is fixed to 1 in CRx.
	 * - Bit X is 0 in _FIXED1: bit X is fixed to 0 in CRx.
	 */
	__asm__ __volatile__("mov %%cr0, %0" : "=r"(cr0) : : "memory");
	cr0 &= rdmsr(MSR_IA32_VMX_CR0_FIXED1);
	cr0 |= rdmsr(MSR_IA32_VMX_CR0_FIXED0);
	__asm__ __volatile__("mov %0, %%cr0" : : "r"(cr0) : "memory");

	__asm__ __volatile__("mov %%cr4, %0" : "=r"(cr4) : : "memory");
	cr4 &= rdmsr(MSR_IA32_VMX_CR4_FIXED1);
	cr4 |= rdmsr(MSR_IA32_VMX_CR4_FIXED0);
	/* Enable VMX operation */
	cr4 |= X86_CR4_VMXE;
	__asm__ __volatile__("mov %0, %%cr4" : : "r"(cr4) : "memory");

	/*
	 * Configure IA32_FEATURE_CONTROL MSR to allow VMXON:
	 *  Bit 0: Lock bit. If clear, VMXON causes a #GP.
	 *  Bit 2: Enables VMXON outside of SMX operation. If clear, VMXON
	 *    outside of SMX causes a #GP.
	 */
	required = FEATURE_CONTROL_VMXON_ENABLED_OUTSIDE_SMX;
	required |= FEATURE_CONTROL_LOCKED;
	feature_control = rdmsr(MSR_IA32_FEATURE_CONTROL);
	if ((feature_control & required) != required)
		wrmsr(MSR_IA32_FEATURE_CONTROL, feature_control | required);

	/* Enter VMX root operation. */
	*(uint32_t *)(vmx->vmxon) = vmcs_revision();
	if (vmxon(vmx->vmxon_gpa))
		return false;

	return true;
}