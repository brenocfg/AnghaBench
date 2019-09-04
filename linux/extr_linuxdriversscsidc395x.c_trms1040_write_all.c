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
struct NvRamType {int dummy; } ;

/* Variables and functions */
 int EN_EEPROM ; 
 unsigned long TRM_S1040_GEN_CONTROL ; 
 unsigned long TRM_S1040_GEN_NVRAM ; 
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  trms1040_set_data (unsigned long,int,int) ; 
 int /*<<< orphan*/  trms1040_wait_30us (unsigned long) ; 
 int /*<<< orphan*/  trms1040_write_cmd (unsigned long,int,int) ; 

__attribute__((used)) static void trms1040_write_all(struct NvRamType *eeprom, unsigned long io_port)
{
	u8 *b_eeprom = (u8 *)eeprom;
	u8 addr;

	/* Enable SEEPROM */
	outb((inb(io_port + TRM_S1040_GEN_CONTROL) | EN_EEPROM),
	     io_port + TRM_S1040_GEN_CONTROL);

	/* write enable */
	trms1040_write_cmd(io_port, 0x04, 0xFF);
	outb(0, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_wait_30us(io_port);

	/* write */
	for (addr = 0; addr < 128; addr++, b_eeprom++)
		trms1040_set_data(io_port, addr, *b_eeprom);

	/* write disable */
	trms1040_write_cmd(io_port, 0x04, 0x00);
	outb(0, io_port + TRM_S1040_GEN_NVRAM);
	trms1040_wait_30us(io_port);

	/* Disable SEEPROM */
	outb((inb(io_port + TRM_S1040_GEN_CONTROL) & ~EN_EEPROM),
	     io_port + TRM_S1040_GEN_CONTROL);
}