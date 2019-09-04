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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ DC390_EEPROM_LEN ; 
 scalar_t__ DC390_EEPROM_READ ; 
 int /*<<< orphan*/  dc390_eeprom_get_data (struct pci_dev*) ; 
 int /*<<< orphan*/  dc390_eeprom_prepare_read (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dc390_read_eeprom(struct pci_dev *pdev, u16 *ptr)
{
	u8 cmd = DC390_EEPROM_READ, i;

	for (i = 0; i < DC390_EEPROM_LEN; i++) {
		pci_write_config_byte(pdev, 0xc0, 0);
		udelay(160);

		dc390_eeprom_prepare_read(pdev, cmd++);
		*ptr++ = dc390_eeprom_get_data(pdev);

		pci_write_config_byte(pdev, 0x80, 0);
		pci_write_config_byte(pdev, 0x80, 0);
		udelay(160);
	}
}