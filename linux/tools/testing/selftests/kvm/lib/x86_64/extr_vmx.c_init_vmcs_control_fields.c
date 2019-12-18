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
typedef  int uint32_t ;
struct vmx_pages {int eptp_gpa; int msr_gpa; int vmread_gpa; int vmwrite_gpa; } ;
struct eptPageTablePointer {int page_walk_length; int ad_enabled; int address; int /*<<< orphan*/  memory_type; } ;
typedef  int /*<<< orphan*/  ept_paddr ;

/* Variables and functions */
 int CPU_BASED_ACTIVATE_SECONDARY_CONTROLS ; 
 int /*<<< orphan*/  CPU_BASED_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  CR0_GUEST_HOST_MASK ; 
 int /*<<< orphan*/  CR0_READ_SHADOW ; 
 int /*<<< orphan*/  CR3_TARGET_COUNT ; 
 int /*<<< orphan*/  CR4_GUEST_HOST_MASK ; 
 int /*<<< orphan*/  CR4_READ_SHADOW ; 
 int /*<<< orphan*/  EPT_POINTER ; 
 int /*<<< orphan*/  EXCEPTION_BITMAP ; 
 int /*<<< orphan*/  GUEST_ASSERT (int) ; 
 int /*<<< orphan*/  MSR_BITMAP ; 
 int /*<<< orphan*/  MSR_IA32_VMX_ENTRY_CTLS ; 
 int /*<<< orphan*/  MSR_IA32_VMX_EPT_VPID_CAP ; 
 int /*<<< orphan*/  MSR_IA32_VMX_EXIT_CTLS ; 
 int /*<<< orphan*/  MSR_IA32_VMX_TRUE_PINBASED_CTLS ; 
 int /*<<< orphan*/  MSR_IA32_VMX_TRUE_PROCBASED_CTLS ; 
 int /*<<< orphan*/  PAGE_FAULT_ERROR_CODE_MASK ; 
 int /*<<< orphan*/  PAGE_FAULT_ERROR_CODE_MATCH ; 
 int PAGE_SHIFT_4K ; 
 int /*<<< orphan*/  PIN_BASED_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  POSTED_INTR_NV ; 
 int SECONDARY_EXEC_ENABLE_EPT ; 
 int /*<<< orphan*/  SECONDARY_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  TPR_THRESHOLD ; 
 int /*<<< orphan*/  VIRTUAL_PROCESSOR_ID ; 
 int /*<<< orphan*/  VMREAD_BITMAP ; 
 int /*<<< orphan*/  VMWRITE_BITMAP ; 
 int /*<<< orphan*/  VMX_BASIC_MEM_TYPE_WB ; 
 int VMX_EPT_VPID_CAP_AD_BITS ; 
 int /*<<< orphan*/  VM_ENTRY_CONTROLS ; 
 int VM_ENTRY_IA32E_MODE ; 
 int /*<<< orphan*/  VM_ENTRY_INTR_INFO_FIELD ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_CONTROLS ; 
 int VM_EXIT_HOST_ADDR_SPACE_SIZE ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_MSR_STORE_COUNT ; 
 int get_cr0 () ; 
 int get_cr4 () ; 
 int /*<<< orphan*/  memcpy (int*,struct eptPageTablePointer*,int) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmwrite (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void init_vmcs_control_fields(struct vmx_pages *vmx)
{
	uint32_t sec_exec_ctl = 0;

	vmwrite(VIRTUAL_PROCESSOR_ID, 0);
	vmwrite(POSTED_INTR_NV, 0);

	vmwrite(PIN_BASED_VM_EXEC_CONTROL, rdmsr(MSR_IA32_VMX_TRUE_PINBASED_CTLS));

	if (vmx->eptp_gpa) {
		uint64_t ept_paddr;
		struct eptPageTablePointer eptp = {
			.memory_type = VMX_BASIC_MEM_TYPE_WB,
			.page_walk_length = 3, /* + 1 */
			.ad_enabled = !!(rdmsr(MSR_IA32_VMX_EPT_VPID_CAP) & VMX_EPT_VPID_CAP_AD_BITS),
			.address = vmx->eptp_gpa >> PAGE_SHIFT_4K,
		};

		memcpy(&ept_paddr, &eptp, sizeof(ept_paddr));
		vmwrite(EPT_POINTER, ept_paddr);
		sec_exec_ctl |= SECONDARY_EXEC_ENABLE_EPT;
	}

	if (!vmwrite(SECONDARY_VM_EXEC_CONTROL, sec_exec_ctl))
		vmwrite(CPU_BASED_VM_EXEC_CONTROL,
			rdmsr(MSR_IA32_VMX_TRUE_PROCBASED_CTLS) | CPU_BASED_ACTIVATE_SECONDARY_CONTROLS);
	else {
		vmwrite(CPU_BASED_VM_EXEC_CONTROL, rdmsr(MSR_IA32_VMX_TRUE_PROCBASED_CTLS));
		GUEST_ASSERT(!sec_exec_ctl);
	}

	vmwrite(EXCEPTION_BITMAP, 0);
	vmwrite(PAGE_FAULT_ERROR_CODE_MASK, 0);
	vmwrite(PAGE_FAULT_ERROR_CODE_MATCH, -1); /* Never match */
	vmwrite(CR3_TARGET_COUNT, 0);
	vmwrite(VM_EXIT_CONTROLS, rdmsr(MSR_IA32_VMX_EXIT_CTLS) |
		VM_EXIT_HOST_ADDR_SPACE_SIZE);	  /* 64-bit host */
	vmwrite(VM_EXIT_MSR_STORE_COUNT, 0);
	vmwrite(VM_EXIT_MSR_LOAD_COUNT, 0);
	vmwrite(VM_ENTRY_CONTROLS, rdmsr(MSR_IA32_VMX_ENTRY_CTLS) |
		VM_ENTRY_IA32E_MODE);		  /* 64-bit guest */
	vmwrite(VM_ENTRY_MSR_LOAD_COUNT, 0);
	vmwrite(VM_ENTRY_INTR_INFO_FIELD, 0);
	vmwrite(TPR_THRESHOLD, 0);

	vmwrite(CR0_GUEST_HOST_MASK, 0);
	vmwrite(CR4_GUEST_HOST_MASK, 0);
	vmwrite(CR0_READ_SHADOW, get_cr0());
	vmwrite(CR4_READ_SHADOW, get_cr4());

	vmwrite(MSR_BITMAP, vmx->msr_gpa);
	vmwrite(VMREAD_BITMAP, vmx->vmread_gpa);
	vmwrite(VMWRITE_BITMAP, vmx->vmwrite_gpa);
}