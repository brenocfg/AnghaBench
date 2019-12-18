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
struct timer_map {int /*<<< orphan*/  emul_ptimer; int /*<<< orphan*/  direct_ptimer; int /*<<< orphan*/  direct_vtimer; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_timer_map (struct kvm_vcpu*,struct timer_map*) ; 
 scalar_t__ kvm_timer_should_fire (int /*<<< orphan*/ ) ; 

bool kvm_timer_is_pending(struct kvm_vcpu *vcpu)
{
	struct timer_map map;

	get_timer_map(vcpu, &map);

	return kvm_timer_should_fire(map.direct_vtimer) ||
	       kvm_timer_should_fire(map.direct_ptimer) ||
	       kvm_timer_should_fire(map.emul_ptimer);
}