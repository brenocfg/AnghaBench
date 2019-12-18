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
struct vmx_pages {int vmcs_gpa; int shadow_vmcs_gpa; } ;

/* Variables and functions */
 int EXIT_REASON_VMCALL ; 
 int /*<<< orphan*/  GUEST_ASSERT (int) ; 
 int /*<<< orphan*/  GUEST_RIP ; 
 int /*<<< orphan*/  GUEST_SYNC (int) ; 
 int L2_GUEST_STACK_SIZE ; 
 int SECONDARY_EXEC_SHADOW_VMCS ; 
 int /*<<< orphan*/  SECONDARY_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  VMCS_LINK_POINTER ; 
 int /*<<< orphan*/  VM_EXIT_REASON ; 
 int /*<<< orphan*/  l2_guest_code ; 
 int load_vmcs (struct vmx_pages*) ; 
 int prepare_for_vmx_operation (struct vmx_pages*) ; 
 int /*<<< orphan*/  prepare_vmcs (struct vmx_pages*,int /*<<< orphan*/ ,unsigned long*) ; 
 int vmlaunch () ; 
 int /*<<< orphan*/  vmptrld (int) ; 
 scalar_t__ vmptrstz () ; 
 int vmreadz (int /*<<< orphan*/ ) ; 
 int vmresume () ; 
 int /*<<< orphan*/  vmwrite (int /*<<< orphan*/ ,int) ; 

void l1_guest_code(struct vmx_pages *vmx_pages)
{
#define L2_GUEST_STACK_SIZE 64
        unsigned long l2_guest_stack[L2_GUEST_STACK_SIZE];

	GUEST_ASSERT(vmx_pages->vmcs_gpa);
	GUEST_ASSERT(prepare_for_vmx_operation(vmx_pages));
	GUEST_SYNC(3);
	GUEST_ASSERT(load_vmcs(vmx_pages));
	GUEST_ASSERT(vmptrstz() == vmx_pages->vmcs_gpa);

	GUEST_SYNC(4);
	GUEST_ASSERT(vmptrstz() == vmx_pages->vmcs_gpa);

	prepare_vmcs(vmx_pages, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	GUEST_SYNC(5);
	GUEST_ASSERT(vmptrstz() == vmx_pages->vmcs_gpa);
	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(vmptrstz() == vmx_pages->vmcs_gpa);
	GUEST_ASSERT(vmreadz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	/* Check that the launched state is preserved.  */
	GUEST_ASSERT(vmlaunch());

	GUEST_ASSERT(!vmresume());
	GUEST_ASSERT(vmreadz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	GUEST_SYNC(7);
	GUEST_ASSERT(vmreadz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	GUEST_ASSERT(!vmresume());
	GUEST_ASSERT(vmreadz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	vmwrite(GUEST_RIP, vmreadz(GUEST_RIP) + 3);

	vmwrite(SECONDARY_VM_EXEC_CONTROL, SECONDARY_EXEC_SHADOW_VMCS);
	vmwrite(VMCS_LINK_POINTER, vmx_pages->shadow_vmcs_gpa);

	GUEST_ASSERT(!vmptrld(vmx_pages->shadow_vmcs_gpa));
	GUEST_ASSERT(vmlaunch());
	GUEST_SYNC(8);
	GUEST_ASSERT(vmlaunch());
	GUEST_ASSERT(vmresume());

	vmwrite(GUEST_RIP, 0xc0ffee);
	GUEST_SYNC(9);
	GUEST_ASSERT(vmreadz(GUEST_RIP) == 0xc0ffee);

	GUEST_ASSERT(!vmptrld(vmx_pages->vmcs_gpa));
	GUEST_ASSERT(!vmresume());
	GUEST_ASSERT(vmreadz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	GUEST_ASSERT(!vmptrld(vmx_pages->shadow_vmcs_gpa));
	GUEST_ASSERT(vmreadz(GUEST_RIP) == 0xc0ffffee);
	GUEST_ASSERT(vmlaunch());
	GUEST_ASSERT(vmresume());
	GUEST_SYNC(13);
	GUEST_ASSERT(vmreadz(GUEST_RIP) == 0xc0ffffee);
	GUEST_ASSERT(vmlaunch());
	GUEST_ASSERT(vmresume());
}