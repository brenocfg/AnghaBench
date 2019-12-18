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
struct kvm_vcpu {unsigned int halt_poll_ns; int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int halt_poll_ns ; 
 int /*<<< orphan*/  halt_poll_ns_grow ; 
 int /*<<< orphan*/  halt_poll_ns_grow_start ; 
 int /*<<< orphan*/  trace_kvm_halt_poll_ns_grow (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void grow_halt_poll_ns(struct kvm_vcpu *vcpu)
{
	unsigned int old, val, grow, grow_start;

	old = val = vcpu->halt_poll_ns;
	grow_start = READ_ONCE(halt_poll_ns_grow_start);
	grow = READ_ONCE(halt_poll_ns_grow);
	if (!grow)
		goto out;

	val *= grow;
	if (val < grow_start)
		val = grow_start;

	if (val > halt_poll_ns)
		val = halt_poll_ns;

	vcpu->halt_poll_ns = val;
out:
	trace_kvm_halt_poll_ns_grow(vcpu->vcpu_id, val, old);
}