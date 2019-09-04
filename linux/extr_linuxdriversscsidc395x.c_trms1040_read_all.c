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
 scalar_t__ TRM_S1040_GEN_CONTROL ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int trms1040_get_data (unsigned long,int) ; 

__attribute__((used)) static void trms1040_read_all(struct NvRamType *eeprom, unsigned long io_port)
{
	u8 *b_eeprom = (u8 *)eeprom;
	u8 addr;

	/* Enable SEEPROM */
	outb((inb(io_port + TRM_S1040_GEN_CONTROL) | EN_EEPROM),
	     io_port + TRM_S1040_GEN_CONTROL);

	/* read details */
	for (addr = 0; addr < 128; addr++, b_eeprom++)
		*b_eeprom = trms1040_get_data(io_port, addr);

	/* Disable SEEPROM */
	outb((inb(io_port + TRM_S1040_GEN_CONTROL) & ~EN_EEPROM),
	     io_port + TRM_S1040_GEN_CONTROL);
}