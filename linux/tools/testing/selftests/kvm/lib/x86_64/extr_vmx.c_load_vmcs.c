#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vmx_pages {int /*<<< orphan*/  enlightened_vmcs; int /*<<< orphan*/  enlightened_vmcs_gpa; int /*<<< orphan*/  shadow_vmcs_gpa; scalar_t__ shadow_vmcs; int /*<<< orphan*/  vmcs_gpa; scalar_t__ vmcs; } ;
struct TYPE_2__ {int revision_id; } ;

/* Variables and functions */
 TYPE_1__* current_evmcs ; 
 int /*<<< orphan*/  enable_evmcs ; 
 scalar_t__ evmcs_vmptrld (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vmclear (int /*<<< orphan*/ ) ; 
 int vmcs_revision () ; 
 scalar_t__ vmptrld (int /*<<< orphan*/ ) ; 

bool load_vmcs(struct vmx_pages *vmx)
{
	if (!enable_evmcs) {
		/* Load a VMCS. */
		*(uint32_t *)(vmx->vmcs) = vmcs_revision();
		if (vmclear(vmx->vmcs_gpa))
			return false;

		if (vmptrld(vmx->vmcs_gpa))
			return false;

		/* Setup shadow VMCS, do not load it yet. */
		*(uint32_t *)(vmx->shadow_vmcs) =
			vmcs_revision() | 0x80000000ul;
		if (vmclear(vmx->shadow_vmcs_gpa))
			return false;
	} else {
		if (evmcs_vmptrld(vmx->enlightened_vmcs_gpa,
				  vmx->enlightened_vmcs))
			return false;
		current_evmcs->revision_id = vmcs_revision();
	}

	return true;
}