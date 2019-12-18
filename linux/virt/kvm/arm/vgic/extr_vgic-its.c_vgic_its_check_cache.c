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
typedef  int /*<<< orphan*/  u32 ;
struct vgic_irq {int dummy; } ;
struct vgic_dist {int /*<<< orphan*/  lpi_list_lock; } ;
struct TYPE_2__ {struct vgic_dist vgic; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 struct vgic_irq* __vgic_its_check_cache (struct vgic_dist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct vgic_irq *vgic_its_check_cache(struct kvm *kvm, phys_addr_t db,
					     u32 devid, u32 eventid)
{
	struct vgic_dist *dist = &kvm->arch.vgic;
	struct vgic_irq *irq;
	unsigned long flags;

	raw_spin_lock_irqsave(&dist->lpi_list_lock, flags);
	irq = __vgic_its_check_cache(dist, db, devid, eventid);
	raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);

	return irq;
}