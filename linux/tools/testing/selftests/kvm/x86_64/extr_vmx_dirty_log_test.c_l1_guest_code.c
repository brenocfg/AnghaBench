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
struct vmx_pages {int vmcs_gpa; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_VMCALL ; 
 int /*<<< orphan*/  GUEST_ASSERT (int) ; 
 int /*<<< orphan*/  GUEST_DONE () ; 
 int /*<<< orphan*/  GUEST_SYNC (int) ; 
 int L2_GUEST_STACK_SIZE ; 
 int /*<<< orphan*/  VM_EXIT_REASON ; 
 int /*<<< orphan*/  l2_guest_code ; 
 int load_vmcs (struct vmx_pages*) ; 
 int prepare_for_vmx_operation (struct vmx_pages*) ; 
 int /*<<< orphan*/  prepare_vmcs (struct vmx_pages*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  vmlaunch () ; 
 scalar_t__ vmreadz (int /*<<< orphan*/ ) ; 

void l1_guest_code(struct vmx_pages *vmx)
{
#define L2_GUEST_STACK_SIZE 64
	unsigned long l2_guest_stack[L2_GUEST_STACK_SIZE];

	GUEST_ASSERT(vmx->vmcs_gpa);
	GUEST_ASSERT(prepare_for_vmx_operation(vmx));
	GUEST_ASSERT(load_vmcs(vmx));

	prepare_vmcs(vmx, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	GUEST_SYNC(false);
	GUEST_ASSERT(!vmlaunch());
	GUEST_SYNC(false);
	GUEST_ASSERT(vmreadz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);
	GUEST_DONE();
}