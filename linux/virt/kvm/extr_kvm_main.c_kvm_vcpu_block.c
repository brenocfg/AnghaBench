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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  halt_poll_invalid; int /*<<< orphan*/  halt_successful_poll; int /*<<< orphan*/  halt_attempted_poll; } ;
struct kvm_vcpu {scalar_t__ halt_poll_ns; int /*<<< orphan*/  wq; TYPE_1__ stat; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_SWAITQUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_swait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grow_halt_poll_ns (struct kvm_vcpu*) ; 
 scalar_t__ halt_poll_ns ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arch_no_poll (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_block_finish (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_blocking (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_unblocking (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_check_block (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  prepare_to_swait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  shrink_halt_poll_ns (struct kvm_vcpu*) ; 
 scalar_t__ single_task_running () ; 
 int /*<<< orphan*/  trace_kvm_vcpu_wakeup (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_valid_wakeup (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  wait ; 

void kvm_vcpu_block(struct kvm_vcpu *vcpu)
{
	ktime_t start, cur;
	DECLARE_SWAITQUEUE(wait);
	bool waited = false;
	u64 block_ns;

	kvm_arch_vcpu_blocking(vcpu);

	start = cur = ktime_get();
	if (vcpu->halt_poll_ns && !kvm_arch_no_poll(vcpu)) {
		ktime_t stop = ktime_add_ns(ktime_get(), vcpu->halt_poll_ns);

		++vcpu->stat.halt_attempted_poll;
		do {
			/*
			 * This sets KVM_REQ_UNHALT if an interrupt
			 * arrives.
			 */
			if (kvm_vcpu_check_block(vcpu) < 0) {
				++vcpu->stat.halt_successful_poll;
				if (!vcpu_valid_wakeup(vcpu))
					++vcpu->stat.halt_poll_invalid;
				goto out;
			}
			cur = ktime_get();
		} while (single_task_running() && ktime_before(cur, stop));
	}

	for (;;) {
		prepare_to_swait_exclusive(&vcpu->wq, &wait, TASK_INTERRUPTIBLE);

		if (kvm_vcpu_check_block(vcpu) < 0)
			break;

		waited = true;
		schedule();
	}

	finish_swait(&vcpu->wq, &wait);
	cur = ktime_get();
out:
	kvm_arch_vcpu_unblocking(vcpu);
	block_ns = ktime_to_ns(cur) - ktime_to_ns(start);

	if (!kvm_arch_no_poll(vcpu)) {
		if (!vcpu_valid_wakeup(vcpu)) {
			shrink_halt_poll_ns(vcpu);
		} else if (halt_poll_ns) {
			if (block_ns <= vcpu->halt_poll_ns)
				;
			/* we had a long block, shrink polling */
			else if (vcpu->halt_poll_ns && block_ns > halt_poll_ns)
				shrink_halt_poll_ns(vcpu);
			/* we had a short halt and our poll time is too small */
			else if (vcpu->halt_poll_ns < halt_poll_ns &&
				block_ns < halt_poll_ns)
				grow_halt_poll_ns(vcpu);
		} else {
			vcpu->halt_poll_ns = 0;
		}
	}

	trace_kvm_vcpu_wakeup(block_ns, waited, vcpu_valid_wakeup(vcpu));
	kvm_arch_vcpu_block_finish(vcpu);
}