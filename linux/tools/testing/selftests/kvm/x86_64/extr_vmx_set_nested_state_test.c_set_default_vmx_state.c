#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ flags; } ;
struct TYPE_5__ {int vmxon_pa; int vmcs12_pa; TYPE_1__ smm; } ;
struct TYPE_6__ {TYPE_2__ vmx; } ;
struct kvm_nested_state {int flags; int size; TYPE_3__ hdr; scalar_t__ format; } ;

/* Variables and functions */
 int KVM_STATE_NESTED_EVMCS ; 
 int KVM_STATE_NESTED_GUEST_MODE ; 
 int KVM_STATE_NESTED_RUN_PENDING ; 
 int /*<<< orphan*/  VMCS12_REVISION ; 
 scalar_t__ have_evmcs ; 
 int /*<<< orphan*/  memset (struct kvm_nested_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_revision_id_for_vmcs12 (struct kvm_nested_state*,int /*<<< orphan*/ ) ; 

void set_default_vmx_state(struct kvm_nested_state *state, int size)
{
	memset(state, 0, size);
	state->flags = KVM_STATE_NESTED_GUEST_MODE  |
			KVM_STATE_NESTED_RUN_PENDING;
	if (have_evmcs)
		state->flags |= KVM_STATE_NESTED_EVMCS;
	state->format = 0;
	state->size = size;
	state->hdr.vmx.vmxon_pa = 0x1000;
	state->hdr.vmx.vmcs12_pa = 0x2000;
	state->hdr.vmx.smm.flags = 0;
	set_revision_id_for_vmcs12(state, VMCS12_REVISION);
}