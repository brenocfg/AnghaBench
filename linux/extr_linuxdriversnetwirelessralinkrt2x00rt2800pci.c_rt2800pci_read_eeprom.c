#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ rt2800pci_efuse_detect (struct rt2x00_dev*) ; 
 int rt2800pci_read_eeprom_efuse (struct rt2x00_dev*) ; 
 int rt2800pci_read_eeprom_pci (struct rt2x00_dev*) ; 

__attribute__((used)) static int rt2800pci_read_eeprom(struct rt2x00_dev *rt2x00dev)
{
	int retval;

	if (rt2800pci_efuse_detect(rt2x00dev))
		retval = rt2800pci_read_eeprom_efuse(rt2x00dev);
	else
		retval = rt2800pci_read_eeprom_pci(rt2x00dev);

	return retval;
}