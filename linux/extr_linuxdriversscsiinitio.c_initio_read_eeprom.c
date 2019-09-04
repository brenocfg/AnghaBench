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

/* Variables and functions */
 scalar_t__ TUL_GCTRL ; 
 int TUL_GCTRL_EEPROM_BIT ; 
 int /*<<< orphan*/  i91unvram ; 
 int /*<<< orphan*/ * i91unvramp ; 
 int inb (scalar_t__) ; 
 int initio_se2_rd_all (unsigned long) ; 
 int /*<<< orphan*/  initio_se2_update_all (unsigned long) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void initio_read_eeprom(unsigned long base)
{
	u8 gctrl;

	i91unvramp = &i91unvram;
	/* Enable EEProm programming */
	gctrl = inb(base + TUL_GCTRL);
	outb(gctrl | TUL_GCTRL_EEPROM_BIT, base + TUL_GCTRL);
	if (initio_se2_rd_all(base) != 1) {
		initio_se2_update_all(base);	/* setup default pattern */
		initio_se2_rd_all(base);	/* load again  */
	}
	/* Disable EEProm programming */
	gctrl = inb(base + TUL_GCTRL);
	outb(gctrl & ~TUL_GCTRL_EEPROM_BIT, base + TUL_GCTRL);
}