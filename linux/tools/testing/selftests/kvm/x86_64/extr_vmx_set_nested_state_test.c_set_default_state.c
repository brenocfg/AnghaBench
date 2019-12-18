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
struct kvm_nested_state {int flags; int size; scalar_t__ format; } ;

/* Variables and functions */
 int KVM_STATE_NESTED_GUEST_MODE ; 
 int KVM_STATE_NESTED_RUN_PENDING ; 
 int /*<<< orphan*/  memset (struct kvm_nested_state*,int /*<<< orphan*/ ,int) ; 

void set_default_state(struct kvm_nested_state *state)
{
	memset(state, 0, sizeof(*state));
	state->flags = KVM_STATE_NESTED_RUN_PENDING |
		       KVM_STATE_NESTED_GUEST_MODE;
	state->format = 0;
	state->size = sizeof(*state);
}