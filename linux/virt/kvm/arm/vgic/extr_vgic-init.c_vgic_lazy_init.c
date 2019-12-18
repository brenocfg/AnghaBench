#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ vgic_model; } ;
struct TYPE_4__ {TYPE_1__ vgic; } ;
struct kvm {int /*<<< orphan*/  lock; TYPE_2__ arch; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ KVM_DEV_TYPE_ARM_VGIC_V2 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int vgic_init (struct kvm*) ; 
 int /*<<< orphan*/  vgic_initialized (struct kvm*) ; 

int vgic_lazy_init(struct kvm *kvm)
{
	int ret = 0;

	if (unlikely(!vgic_initialized(kvm))) {
		/*
		 * We only provide the automatic initialization of the VGIC
		 * for the legacy case of a GICv2. Any other type must
		 * be explicitly initialized once setup with the respective
		 * KVM device call.
		 */
		if (kvm->arch.vgic.vgic_model != KVM_DEV_TYPE_ARM_VGIC_V2)
			return -EBUSY;

		mutex_lock(&kvm->lock);
		ret = vgic_init(kvm);
		mutex_unlock(&kvm->lock);
	}

	return ret;
}