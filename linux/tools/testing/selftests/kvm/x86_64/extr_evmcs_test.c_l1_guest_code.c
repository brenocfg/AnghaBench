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
struct vmx_pages {int vmcs_gpa; scalar_t__ enlightened_vmcs_gpa; int /*<<< orphan*/  vp_assist; int /*<<< orphan*/  vp_assist_gpa; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_VMCALL ; 
 int /*<<< orphan*/  GUEST_ASSERT (int) ; 
 int /*<<< orphan*/  GUEST_SYNC (int) ; 
 int L2_GUEST_STACK_SIZE ; 
 int /*<<< orphan*/  VM_EXIT_REASON ; 
 int /*<<< orphan*/  enable_vp_assist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2_guest_code ; 
 int load_vmcs (struct vmx_pages*) ; 
 int prepare_for_vmx_operation (struct vmx_pages*) ; 
 int /*<<< orphan*/  prepare_vmcs (struct vmx_pages*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  vmlaunch () ; 
 scalar_t__ vmptrstz () ; 
 scalar_t__ vmreadz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmresume () ; 

void l1_guest_code(struct vmx_pages *vmx_pages)
{
#define L2_GUEST_STACK_SIZE 64
	unsigned long l2_guest_stack[L2_GUEST_STACK_SIZE];

	enable_vp_assist(vmx_pages->vp_assist_gpa, vmx_pages->vp_assist);

	GUEST_ASSERT(vmx_pages->vmcs_gpa);
	GUEST_ASSERT(prepare_for_vmx_operation(vmx_pages));
	GUEST_SYNC(3);
	GUEST_ASSERT(load_vmcs(vmx_pages));
	GUEST_ASSERT(vmptrstz() == vmx_pages->enlightened_vmcs_gpa);

	GUEST_SYNC(4);
	GUEST_ASSERT(vmptrstz() == vmx_pages->enlightened_vmcs_gpa);

	prepare_vmcs(vmx_pages, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	GUEST_SYNC(5);
	GUEST_ASSERT(vmptrstz() == vmx_pages->enlightened_vmcs_gpa);
	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(vmptrstz() == vmx_pages->enlightened_vmcs_gpa);
	GUEST_SYNC(8);
	GUEST_ASSERT(!vmresume());
	GUEST_ASSERT(vmreadz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);
	GUEST_SYNC(9);
}