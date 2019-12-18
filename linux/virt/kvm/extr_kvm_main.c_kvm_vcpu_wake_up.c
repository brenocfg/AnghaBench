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
struct swait_queue_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  halt_wakeup; } ;
struct kvm_vcpu {TYPE_1__ stat; int /*<<< orphan*/  ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 struct swait_queue_head* kvm_arch_vcpu_wq (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  swake_up_one (struct swait_queue_head*) ; 
 scalar_t__ swq_has_sleeper (struct swait_queue_head*) ; 

bool kvm_vcpu_wake_up(struct kvm_vcpu *vcpu)
{
	struct swait_queue_head *wqp;

	wqp = kvm_arch_vcpu_wq(vcpu);
	if (swq_has_sleeper(wqp)) {
		swake_up_one(wqp);
		WRITE_ONCE(vcpu->ready, true);
		++vcpu->stat.halt_wakeup;
		return true;
	}

	return false;
}