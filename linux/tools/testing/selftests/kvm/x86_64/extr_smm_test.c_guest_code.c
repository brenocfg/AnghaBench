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
struct vmx_pages {int dummy; } ;

/* Variables and functions */
 int DONE ; 
 int /*<<< orphan*/  GUEST_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_IA32_APICBASE ; 
 int X2APIC_ENABLE ; 
 int /*<<< orphan*/  prepare_for_vmx_operation (struct vmx_pages*) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  self_smi () ; 
 int /*<<< orphan*/  sync_with_host (int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

void guest_code(struct vmx_pages *vmx_pages)
{
	uint64_t apicbase = rdmsr(MSR_IA32_APICBASE);

	sync_with_host(1);

	wrmsr(MSR_IA32_APICBASE, apicbase | X2APIC_ENABLE);

	sync_with_host(2);

	self_smi();

	sync_with_host(4);

	if (vmx_pages) {
		GUEST_ASSERT(prepare_for_vmx_operation(vmx_pages));

		sync_with_host(5);

		self_smi();

		sync_with_host(7);
	}

	sync_with_host(DONE);
}