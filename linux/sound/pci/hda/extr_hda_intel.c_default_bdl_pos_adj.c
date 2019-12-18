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
struct azx {int driver_type; TYPE_1__* pci; } ;
struct TYPE_2__ {scalar_t__ vendor; int device; } ;

/* Variables and functions */
#define  AZX_DRIVER_ICH 129 
#define  AZX_DRIVER_PCH 128 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 

__attribute__((used)) static int default_bdl_pos_adj(struct azx *chip)
{
	/* some exceptions: Atoms seem problematic with value 1 */
	if (chip->pci->vendor == PCI_VENDOR_ID_INTEL) {
		switch (chip->pci->device) {
		case 0x0f04: /* Baytrail */
		case 0x2284: /* Braswell */
			return 32;
		}
	}

	switch (chip->driver_type) {
	case AZX_DRIVER_ICH:
	case AZX_DRIVER_PCH:
		return 1;
	default:
		return 32;
	}
}