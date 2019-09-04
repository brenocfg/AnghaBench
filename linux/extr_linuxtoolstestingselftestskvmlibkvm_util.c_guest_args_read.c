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
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm_vm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;
struct kvm_run {TYPE_1__ io; } ;
struct kvm_regs {int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; } ;
struct guest_args {int /*<<< orphan*/  arg1; int /*<<< orphan*/  arg0; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct kvm_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcpu_regs_get (struct kvm_vm*,int /*<<< orphan*/ ,struct kvm_regs*) ; 
 struct kvm_run* vcpu_state (struct kvm_vm*,int /*<<< orphan*/ ) ; 

void guest_args_read(struct kvm_vm *vm, uint32_t vcpu_id,
		     struct guest_args *args)
{
	struct kvm_run *run = vcpu_state(vm, vcpu_id);
	struct kvm_regs regs;

	memset(&regs, 0, sizeof(regs));
	vcpu_regs_get(vm, vcpu_id, &regs);

	args->port = run->io.port;
	args->arg0 = regs.rdi;
	args->arg1 = regs.rsi;
}