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
struct kvm_msi {int /*<<< orphan*/  devid; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct TYPE_2__ {int /*<<< orphan*/  devid; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ msi; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  vgic_has_its (struct kvm*) ; 
 int vgic_its_inject_msi (struct kvm*,struct kvm_msi*) ; 

int kvm_set_msi(struct kvm_kernel_irq_routing_entry *e,
		struct kvm *kvm, int irq_source_id,
		int level, bool line_status)
{
	struct kvm_msi msi;

	msi.address_lo = e->msi.address_lo;
	msi.address_hi = e->msi.address_hi;
	msi.data = e->msi.data;
	msi.flags = e->msi.flags;
	msi.devid = e->msi.devid;

	if (!vgic_has_its(kvm))
		return -ENODEV;

	if (!level)
		return -1;

	return vgic_its_inject_msi(kvm, &msi);
}