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
struct TYPE_2__ {int sversion; } ;
struct parisc_device {int /*<<< orphan*/  aux_irq; TYPE_1__ id; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  gsc_asic_assign_irq (void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wax_choose_irq(struct parisc_device *dev, void *ctrl)
{
	int irq;

	switch (dev->id.sversion) {
		case 0x73:	irq =  1; break; /* i8042 General */
		case 0x8c:	irq =  6; break; /* Serial */
		case 0x90:	irq = 10; break; /* EISA */
		default:	return;		 /* Unknown */
	}

	gsc_asic_assign_irq(ctrl, irq, &dev->irq);

	switch (dev->id.sversion) {
		case 0x73:	irq =  2; break; /* i8042 High-priority */
		case 0x90:	irq =  0; break; /* EISA NMI */
		default:	return;		 /* No secondary IRQ */
	}

	gsc_asic_assign_irq(ctrl, irq, &dev->aux_irq);
}