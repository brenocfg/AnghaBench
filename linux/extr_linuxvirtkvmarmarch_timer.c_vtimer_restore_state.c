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
struct arch_timer_cpu {scalar_t__ enabled; } ;
struct TYPE_2__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct arch_timer_context {int loaded; int /*<<< orphan*/  cnt_ctl; int /*<<< orphan*/  cnt_cval; } ;

/* Variables and functions */
 int /*<<< orphan*/  cntv_ctl ; 
 int /*<<< orphan*/  cntv_cval ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  write_sysreg_el0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vtimer_restore_state(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	unsigned long flags;

	local_irq_save(flags);

	if (vtimer->loaded)
		goto out;

	if (timer->enabled) {
		write_sysreg_el0(vtimer->cnt_cval, cntv_cval);
		isb();
		write_sysreg_el0(vtimer->cnt_ctl, cntv_ctl);
	}

	vtimer->loaded = true;
out:
	local_irq_restore(flags);
}