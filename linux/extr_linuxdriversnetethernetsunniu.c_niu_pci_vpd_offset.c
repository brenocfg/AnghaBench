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
typedef  scalar_t__ u32 ;
struct niu {int dummy; } ;

/* Variables and functions */
 scalar_t__ ESPC_EEPROM_SIZE ; 
 int niu_pci_eeprom_read (struct niu*,scalar_t__) ; 
 int niu_pci_eeprom_read16 (struct niu*,scalar_t__) ; 
 int niu_pci_eeprom_read16_swp (struct niu*,scalar_t__) ; 

__attribute__((used)) static u32 niu_pci_vpd_offset(struct niu *np)
{
	u32 start = 0, end = ESPC_EEPROM_SIZE, ret;
	int err;

	while (start < end) {
		ret = start;

		/* ROM header signature?  */
		err = niu_pci_eeprom_read16(np, start +  0);
		if (err != 0x55aa)
			return 0;

		/* Apply offset to PCI data structure.  */
		err = niu_pci_eeprom_read16(np, start + 23);
		if (err < 0)
			return 0;
		start += err;

		/* Check for "PCIR" signature.  */
		err = niu_pci_eeprom_read16(np, start +  0);
		if (err != 0x5043)
			return 0;
		err = niu_pci_eeprom_read16(np, start +  2);
		if (err != 0x4952)
			return 0;

		/* Check for OBP image type.  */
		err = niu_pci_eeprom_read(np, start + 20);
		if (err < 0)
			return 0;
		if (err != 0x01) {
			err = niu_pci_eeprom_read(np, ret + 2);
			if (err < 0)
				return 0;

			start = ret + (err * 512);
			continue;
		}

		err = niu_pci_eeprom_read16_swp(np, start + 8);
		if (err < 0)
			return err;
		ret += err;

		err = niu_pci_eeprom_read(np, ret + 0);
		if (err != 0x82)
			return 0;

		return ret;
	}

	return 0;
}