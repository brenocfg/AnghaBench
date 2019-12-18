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
 int /*<<< orphan*/  halt_poll_ns_shrink ; 
 int /*<<< orphan*/  trace_kvm_halt_poll_ns_shrink (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void shrink_halt_poll_ns(struct kvm_vcpu *vcpu)
{
	unsigned int old, val, shrink;

	old = val = vcpu->halt_poll_ns;
	shrink = READ_ONCE(halt_poll_ns_shrink);
	if (shrink == 0)
		val = 0;
	else
		val /= shrink;

	vcpu->halt_poll_ns = val;
	trace_kvm_halt_poll_ns_shrink(vcpu->vcpu_id, val, old);
}