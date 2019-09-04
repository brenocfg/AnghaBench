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
struct TYPE_2__ {scalar_t__ subvendor; } ;
struct snd_ice1712 {TYPE_1__ eeprom; } ;

/* Variables and functions */
 scalar_t__ VT1724_SUBDEVICE_SE200PCI ; 
 int se200pci_add_controls (struct snd_ice1712*) ; 

__attribute__((used)) static int se_add_controls(struct snd_ice1712 *ice)
{
	int err;

	err = 0;
	/* nothing to do for VT1724_SUBDEVICE_SE90PCI */
	if (ice->eeprom.subvendor == VT1724_SUBDEVICE_SE200PCI)
		err = se200pci_add_controls(ice);

	return err;
}