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
struct kvm_vcpu {int dummy; } ;
struct kvm_device_attr {int attr; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_ARM_VCPU_TIMER_IRQ_PTIMER 129 
#define  KVM_ARM_VCPU_TIMER_IRQ_VTIMER 128 

int kvm_arm_timer_has_attr(struct kvm_vcpu *vcpu, struct kvm_device_attr *attr)
{
	switch (attr->attr) {
	case KVM_ARM_VCPU_TIMER_IRQ_VTIMER:
	case KVM_ARM_VCPU_TIMER_IRQ_PTIMER:
		return 0;
	}

	return -ENXIO;
}