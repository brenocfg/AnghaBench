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
struct timer_map {int /*<<< orphan*/ * emul_ptimer; int /*<<< orphan*/ * direct_ptimer; void* direct_vtimer; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 scalar_t__ has_vhe () ; 
 int /*<<< orphan*/  trace_kvm_get_timer_map (int /*<<< orphan*/ ,struct timer_map*) ; 
 void* vcpu_ptimer (struct kvm_vcpu*) ; 
 void* vcpu_vtimer (struct kvm_vcpu*) ; 

__attribute__((used)) static void get_timer_map(struct kvm_vcpu *vcpu, struct timer_map *map)
{
	if (has_vhe()) {
		map->direct_vtimer = vcpu_vtimer(vcpu);
		map->direct_ptimer = vcpu_ptimer(vcpu);
		map->emul_ptimer = NULL;
	} else {
		map->direct_vtimer = vcpu_vtimer(vcpu);
		map->direct_ptimer = NULL;
		map->emul_ptimer = vcpu_ptimer(vcpu);
	}

	trace_kvm_get_timer_map(vcpu->vcpu_id, map);
}