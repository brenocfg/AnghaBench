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
struct kvm {int dummy; } ;
struct TYPE_2__ {scalar_t__ has_gicv4; } ;

/* Variables and functions */
 TYPE_1__ kvm_vgic_global_state ; 
 scalar_t__ vgic_has_its (struct kvm*) ; 

bool vgic_supports_direct_msis(struct kvm *kvm)
{
	return kvm_vgic_global_state.has_gicv4 && vgic_has_its(kvm);
}