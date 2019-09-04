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
struct vgic_dist {scalar_t__ vgic_model; int has_its; } ;
struct TYPE_2__ {struct vgic_dist vgic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ KVM_DEV_TYPE_ARM_VGIC_V3 ; 

bool vgic_has_its(struct kvm *kvm)
{
	struct vgic_dist *dist = &kvm->arch.vgic;

	if (dist->vgic_model != KVM_DEV_TYPE_ARM_VGIC_V3)
		return false;

	return dist->has_its;
}