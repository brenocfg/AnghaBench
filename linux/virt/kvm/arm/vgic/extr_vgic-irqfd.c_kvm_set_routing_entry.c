#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  devid; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct TYPE_7__ {int /*<<< orphan*/  irqchip; int /*<<< orphan*/  pin; } ;
struct kvm_kernel_irq_routing_entry {TYPE_3__ msi; int /*<<< orphan*/  set; TYPE_2__ irqchip; } ;
struct TYPE_9__ {int /*<<< orphan*/  devid; int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct TYPE_6__ {int /*<<< orphan*/  pin; int /*<<< orphan*/  irqchip; } ;
struct TYPE_10__ {TYPE_4__ msi; TYPE_1__ irqchip; } ;
struct kvm_irq_routing_entry {int type; TYPE_5__ u; int /*<<< orphan*/  flags; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVM_IRQCHIP_NUM_PINS ; 
#define  KVM_IRQ_ROUTING_IRQCHIP 129 
#define  KVM_IRQ_ROUTING_MSI 128 
 int /*<<< orphan*/  KVM_NR_IRQCHIPS ; 
 int /*<<< orphan*/  kvm_set_msi ; 
 int /*<<< orphan*/  vgic_irqfd_set_irq ; 

int kvm_set_routing_entry(struct kvm *kvm,
			  struct kvm_kernel_irq_routing_entry *e,
			  const struct kvm_irq_routing_entry *ue)
{
	int r = -EINVAL;

	switch (ue->type) {
	case KVM_IRQ_ROUTING_IRQCHIP:
		e->set = vgic_irqfd_set_irq;
		e->irqchip.irqchip = ue->u.irqchip.irqchip;
		e->irqchip.pin = ue->u.irqchip.pin;
		if ((e->irqchip.pin >= KVM_IRQCHIP_NUM_PINS) ||
		    (e->irqchip.irqchip >= KVM_NR_IRQCHIPS))
			goto out;
		break;
	case KVM_IRQ_ROUTING_MSI:
		e->set = kvm_set_msi;
		e->msi.address_lo = ue->u.msi.address_lo;
		e->msi.address_hi = ue->u.msi.address_hi;
		e->msi.data = ue->u.msi.data;
		e->msi.flags = ue->flags;
		e->msi.devid = ue->u.msi.devid;
		break;
	default:
		goto out;
	}
	r = 0;
out:
	return r;
}