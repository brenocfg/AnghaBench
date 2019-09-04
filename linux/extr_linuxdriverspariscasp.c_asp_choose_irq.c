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
struct parisc_device {int hw_path; int /*<<< orphan*/  aux_irq; TYPE_1__ id; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  gsc_asic_assign_irq (void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asp_choose_irq(struct parisc_device *dev, void *ctrl)
{
	int irq;

	switch (dev->id.sversion) {
	case 0x71:	irq =  9; break; /* SCSI */
	case 0x72:	irq =  8; break; /* LAN */
	case 0x73:	irq =  1; break; /* HIL */
	case 0x74:	irq =  7; break; /* Centronics */
	case 0x75:	irq = (dev->hw_path == 4) ? 5 : 6; break; /* RS232 */
	case 0x76:	irq = 10; break; /* EISA BA */
	case 0x77:	irq = 11; break; /* Graphics1 */
	case 0x7a:	irq = 13; break; /* Audio (Bushmaster) */
	case 0x7b:	irq = 13; break; /* Audio (Scorpio) */
	case 0x7c:	irq =  3; break; /* FW SCSI */
	case 0x7d:	irq =  4; break; /* FDDI */
	case 0x7f:	irq = 13; break; /* Audio (Outfield) */
	default:	return;		 /* Unknown */
	}

	gsc_asic_assign_irq(ctrl, irq, &dev->irq);

	switch (dev->id.sversion) {
	case 0x73:	irq =  2; break; /* i8042 High-priority */
	case 0x76:	irq =  0; break; /* EISA BA */
	default:	return;		 /* Other */
	}

	gsc_asic_assign_irq(ctrl, irq, &dev->aux_irq);
}