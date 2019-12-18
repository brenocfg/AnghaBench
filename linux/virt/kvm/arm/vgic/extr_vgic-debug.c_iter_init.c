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
struct vgic_state_iter {int nr_cpus; scalar_t__ nr_lpis; int /*<<< orphan*/  lpi_array; int /*<<< orphan*/  nr_spis; } ;
struct TYPE_3__ {scalar_t__ vgic_model; int /*<<< orphan*/  nr_spis; } ;
struct TYPE_4__ {TYPE_1__ vgic; } ;
struct kvm {TYPE_2__ arch; int /*<<< orphan*/  online_vcpus; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ KVM_DEV_TYPE_ARM_VGIC_V3 ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iter_next (struct vgic_state_iter*) ; 
 int /*<<< orphan*/  memset (struct vgic_state_iter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vgic_copy_lpi_list (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iter_init(struct kvm *kvm, struct vgic_state_iter *iter,
		      loff_t pos)
{
	int nr_cpus = atomic_read(&kvm->online_vcpus);

	memset(iter, 0, sizeof(*iter));

	iter->nr_cpus = nr_cpus;
	iter->nr_spis = kvm->arch.vgic.nr_spis;
	if (kvm->arch.vgic.vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3) {
		iter->nr_lpis = vgic_copy_lpi_list(kvm, NULL, &iter->lpi_array);
		if (iter->nr_lpis < 0)
			iter->nr_lpis = 0;
	}

	/* Fast forward to the right position if needed */
	while (pos--)
		iter_next(iter);
}