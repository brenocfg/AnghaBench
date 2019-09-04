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
struct kvm_msi {int flags; int /*<<< orphan*/  devid; int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  devid; int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ msi; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int KVM_MSI_VALID_DEVID ; 
 int /*<<< orphan*/  KVM_USERSPACE_IRQ_SOURCE_ID ; 
 int /*<<< orphan*/  irqchip_in_kernel (struct kvm*) ; 
 int kvm_set_msi (struct kvm_kernel_irq_routing_entry*,struct kvm*,int /*<<< orphan*/ ,int,int) ; 

int kvm_send_userspace_msi(struct kvm *kvm, struct kvm_msi *msi)
{
	struct kvm_kernel_irq_routing_entry route;

	if (!irqchip_in_kernel(kvm) || (msi->flags & ~KVM_MSI_VALID_DEVID))
		return -EINVAL;

	route.msi.address_lo = msi->address_lo;
	route.msi.address_hi = msi->address_hi;
	route.msi.data = msi->data;
	route.msi.flags = msi->flags;
	route.msi.devid = msi->devid;

	return kvm_set_msi(&route, kvm, KVM_USERSPACE_IRQ_SOURCE_ID, 1, false);
}