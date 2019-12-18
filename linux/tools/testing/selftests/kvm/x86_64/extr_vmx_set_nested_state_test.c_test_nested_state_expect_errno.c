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
struct kvm_vm {int dummy; } ;
struct kvm_nested_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VCPU_ID ; 
 int errno ; 
 int /*<<< orphan*/  strerror (int) ; 
 int vcpu_nested_state_set (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_nested_state*,int) ; 

void test_nested_state_expect_errno(struct kvm_vm *vm,
				    struct kvm_nested_state *state,
				    int expected_errno)
{
	int rv;

	rv = vcpu_nested_state_set(vm, VCPU_ID, state, true);
	TEST_ASSERT(rv == -1 && errno == expected_errno,
		"Expected %s (%d) from vcpu_nested_state_set but got rv: %i errno: %s (%d)",
		strerror(expected_errno), expected_errno, rv, strerror(errno),
		errno);
}