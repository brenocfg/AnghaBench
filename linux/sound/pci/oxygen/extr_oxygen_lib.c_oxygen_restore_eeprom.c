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
typedef  int u16 ;
struct pci_device_id {int subdevice; int subvendor; } ;
struct oxygen {TYPE_1__* card; int /*<<< orphan*/  pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int OXYGEN_EEPROM_ID ; 
 int /*<<< orphan*/  OXYGEN_MISC ; 
 int /*<<< orphan*/  OXYGEN_MISC_WRITE_PCI_SUBID ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_ID ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_VENDOR_ID ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  oxygen_clear_bits8 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int oxygen_read_eeprom (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_set_bits8 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write_eeprom (struct oxygen*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void oxygen_restore_eeprom(struct oxygen *chip,
				  const struct pci_device_id *id)
{
	u16 eeprom_id;

	eeprom_id = oxygen_read_eeprom(chip, 0);
	if (eeprom_id != OXYGEN_EEPROM_ID &&
	    (eeprom_id != 0xffff || id->subdevice != 0x8788)) {
		/*
		 * This function gets called only when a known card model has
		 * been detected, i.e., we know there is a valid subsystem
		 * product ID at index 2 in the EEPROM.  Therefore, we have
		 * been able to deduce the correct subsystem vendor ID, and
		 * this is enough information to restore the original EEPROM
		 * contents.
		 */
		oxygen_write_eeprom(chip, 1, id->subvendor);
		oxygen_write_eeprom(chip, 0, OXYGEN_EEPROM_ID);

		oxygen_set_bits8(chip, OXYGEN_MISC,
				 OXYGEN_MISC_WRITE_PCI_SUBID);
		pci_write_config_word(chip->pci, PCI_SUBSYSTEM_VENDOR_ID,
				      id->subvendor);
		pci_write_config_word(chip->pci, PCI_SUBSYSTEM_ID,
				      id->subdevice);
		oxygen_clear_bits8(chip, OXYGEN_MISC,
				   OXYGEN_MISC_WRITE_PCI_SUBID);

		dev_info(chip->card->dev, "EEPROM ID restored\n");
	}
}