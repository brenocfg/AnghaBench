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
struct vmx_pages {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_ASSERT (int) ; 
 int L2_GUEST_STACK_SIZE ; 
 int /*<<< orphan*/  l2_guest_code ; 
 int load_vmcs (struct vmx_pages*) ; 
 int prepare_for_vmx_operation (struct vmx_pages*) ; 
 int /*<<< orphan*/  prepare_vmcs (struct vmx_pages*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  vmlaunch () ; 

__attribute__((used)) static void l1_guest_code(struct vmx_pages *vmx_pages)
{
#define L2_GUEST_STACK_SIZE 64
	unsigned long l2_guest_stack[L2_GUEST_STACK_SIZE];

	GUEST_ASSERT(prepare_for_vmx_operation(vmx_pages));
	GUEST_ASSERT(load_vmcs(vmx_pages));

	/* Prepare the VMCS for L2 execution. */
	prepare_vmcs(vmx_pages, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(0);
}