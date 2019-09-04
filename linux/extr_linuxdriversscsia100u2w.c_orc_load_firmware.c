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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct orc_host {scalar_t__ base; } ;

/* Variables and functions */
 int DOWNLOAD ; 
 int EEPRG ; 
 scalar_t__ ORC_EBIOSADR0 ; 
 scalar_t__ ORC_EBIOSADR2 ; 
 scalar_t__ ORC_EBIOSDATA ; 
 scalar_t__ ORC_FWBASEADR ; 
 scalar_t__ ORC_GCFG ; 
 scalar_t__ ORC_RISCCTL ; 
 scalar_t__ ORC_RISCRAM ; 
 int PRGMRST ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 scalar_t__ inl (scalar_t__) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 orc_load_firmware(struct orc_host * host)
{
	u32 data32;
	u16 bios_addr;
	u16 i;
	u8 *data32_ptr, data;


	/* Set up the EEPROM for access */

	data = inb(host->base + ORC_GCFG);
	outb(data | EEPRG, host->base + ORC_GCFG);	/* Enable EEPROM programming */
	outb(0x00, host->base + ORC_EBIOSADR2);
	outw(0x0000, host->base + ORC_EBIOSADR0);
	if (inb(host->base + ORC_EBIOSDATA) != 0x55) {
		outb(data, host->base + ORC_GCFG);	/* Disable EEPROM programming */
		return 0;
	}
	outw(0x0001, host->base + ORC_EBIOSADR0);
	if (inb(host->base + ORC_EBIOSDATA) != 0xAA) {
		outb(data, host->base + ORC_GCFG);	/* Disable EEPROM programming */
		return 0;
	}

	outb(PRGMRST | DOWNLOAD, host->base + ORC_RISCCTL);	/* Enable SRAM programming */
	data32_ptr = (u8 *) & data32;
	data32 = cpu_to_le32(0);		/* Initial FW address to 0 */
	outw(0x0010, host->base + ORC_EBIOSADR0);
	*data32_ptr = inb(host->base + ORC_EBIOSDATA);		/* Read from BIOS */
	outw(0x0011, host->base + ORC_EBIOSADR0);
	*(data32_ptr + 1) = inb(host->base + ORC_EBIOSDATA);	/* Read from BIOS */
	outw(0x0012, host->base + ORC_EBIOSADR0);
	*(data32_ptr + 2) = inb(host->base + ORC_EBIOSDATA);	/* Read from BIOS */
	outw(*(data32_ptr + 2), host->base + ORC_EBIOSADR2);
	outl(le32_to_cpu(data32), host->base + ORC_FWBASEADR);		/* Write FW address */

	/* Copy the code from the BIOS to the SRAM */

	udelay(500);	/* Required on Sun Ultra 5 ... 350 -> failures */
	bios_addr = (u16) le32_to_cpu(data32);	/* FW code locate at BIOS address + ? */
	for (i = 0, data32_ptr = (u8 *) & data32;	/* Download the code    */
	     i < 0x1000;	/* Firmware code size = 4K      */
	     i++, bios_addr++) {
		outw(bios_addr, host->base + ORC_EBIOSADR0);
		*data32_ptr++ = inb(host->base + ORC_EBIOSDATA);	/* Read from BIOS */
		if ((i % 4) == 3) {
			outl(le32_to_cpu(data32), host->base + ORC_RISCRAM);	/* Write every 4 bytes */
			data32_ptr = (u8 *) & data32;
		}
	}

	/* Go back and check they match */

	outb(PRGMRST | DOWNLOAD, host->base + ORC_RISCCTL);	/* Reset program count 0 */
	bios_addr -= 0x1000;	/* Reset the BIOS address */
	for (i = 0, data32_ptr = (u8 *) & data32;	/* Check the code       */
	     i < 0x1000;	/* Firmware code size = 4K      */
	     i++, bios_addr++) {
		outw(bios_addr, host->base + ORC_EBIOSADR0);
		*data32_ptr++ = inb(host->base + ORC_EBIOSDATA);	/* Read from BIOS */
		if ((i % 4) == 3) {
			if (inl(host->base + ORC_RISCRAM) != le32_to_cpu(data32)) {
				outb(PRGMRST, host->base + ORC_RISCCTL);	/* Reset program to 0 */
				outb(data, host->base + ORC_GCFG);	/*Disable EEPROM programming */
				return 0;
			}
			data32_ptr = (u8 *) & data32;
		}
	}

	/* Success */
	outb(PRGMRST, host->base + ORC_RISCCTL);	/* Reset program to 0   */
	outb(data, host->base + ORC_GCFG);	/* Disable EEPROM programming */
	return 1;
}