#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  function; } ;
struct arch_timer_cpu {TYPE_3__ phys_timer; TYPE_3__ bg_timer; int /*<<< orphan*/  expired; } ;
struct TYPE_6__ {struct arch_timer_cpu timer_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;
struct arch_timer_context {TYPE_2__ irq; scalar_t__ cntvoff; } ;
struct TYPE_10__ {int /*<<< orphan*/  irq; } ;
struct TYPE_9__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ default_ptimer_irq ; 
 TYPE_4__ default_vtimer_irq ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_bg_timer_expire ; 
 int /*<<< orphan*/  kvm_phys_timer_expire ; 
 int /*<<< orphan*/  kvm_phys_timer_read () ; 
 int /*<<< orphan*/  kvm_timer_inject_irq_work ; 
 int /*<<< orphan*/  update_vtimer_cntvoff (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 struct arch_timer_context* vcpu_ptimer (struct kvm_vcpu*) ; 
 struct arch_timer_context* vcpu_vtimer (struct kvm_vcpu*) ; 

void kvm_timer_vcpu_init(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = &vcpu->arch.timer_cpu;
	struct arch_timer_context *vtimer = vcpu_vtimer(vcpu);
	struct arch_timer_context *ptimer = vcpu_ptimer(vcpu);

	/* Synchronize cntvoff across all vtimers of a VM. */
	update_vtimer_cntvoff(vcpu, kvm_phys_timer_read());
	vcpu_ptimer(vcpu)->cntvoff = 0;

	INIT_WORK(&timer->expired, kvm_timer_inject_irq_work);
	hrtimer_init(&timer->bg_timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	timer->bg_timer.function = kvm_bg_timer_expire;

	hrtimer_init(&timer->phys_timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	timer->phys_timer.function = kvm_phys_timer_expire;

	vtimer->irq.irq = default_vtimer_irq.irq;
	ptimer->irq.irq = default_ptimer_irq.irq;
}