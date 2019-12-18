#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_map {scalar_t__ emul_ptimer; TYPE_1__* direct_ptimer; TYPE_1__* direct_vtimer; } ;
struct kvm_vcpu {int dummy; } ;
struct arch_timer_cpu {int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  cntvoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_timer_map (struct kvm_vcpu*,struct timer_map*) ; 
 int /*<<< orphan*/  has_gic_active_state ; 
 int /*<<< orphan*/  kvm_timer_unblocking (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_timer_vcpu_load_gic (TYPE_1__*) ; 
 int /*<<< orphan*/  kvm_timer_vcpu_load_nogic (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_cntvoff (int /*<<< orphan*/ ) ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_emulate (scalar_t__) ; 
 int /*<<< orphan*/  timer_restore_state (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 struct arch_timer_cpu* vcpu_timer (struct kvm_vcpu*) ; 

void kvm_timer_vcpu_load(struct kvm_vcpu *vcpu)
{
	struct arch_timer_cpu *timer = vcpu_timer(vcpu);
	struct timer_map map;

	if (unlikely(!timer->enabled))
		return;

	get_timer_map(vcpu, &map);

	if (static_branch_likely(&has_gic_active_state)) {
		kvm_timer_vcpu_load_gic(map.direct_vtimer);
		if (map.direct_ptimer)
			kvm_timer_vcpu_load_gic(map.direct_ptimer);
	} else {
		kvm_timer_vcpu_load_nogic(vcpu);
	}

	set_cntvoff(map.direct_vtimer->cntvoff);

	kvm_timer_unblocking(vcpu);

	timer_restore_state(map.direct_vtimer);
	if (map.direct_ptimer)
		timer_restore_state(map.direct_ptimer);

	if (map.emul_ptimer)
		timer_emulate(map.emul_ptimer);
}