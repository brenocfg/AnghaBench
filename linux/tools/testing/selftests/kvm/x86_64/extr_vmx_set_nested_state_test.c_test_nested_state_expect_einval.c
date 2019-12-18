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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  test_nested_state_expect_errno (struct kvm_vm*,struct kvm_nested_state*,int /*<<< orphan*/ ) ; 

void test_nested_state_expect_einval(struct kvm_vm *vm,
				     struct kvm_nested_state *state)
{
	test_nested_state_expect_errno(vm, state, EINVAL);
}