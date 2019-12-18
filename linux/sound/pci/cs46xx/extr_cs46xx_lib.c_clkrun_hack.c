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
typedef  int u16 ;
struct snd_cs46xx {scalar_t__ acpi_port; scalar_t__ amplifier; } ;

/* Variables and functions */
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void clkrun_hack(struct snd_cs46xx *chip, int change)
{
	u16 control, nval;
	
	if (!chip->acpi_port)
		return;

	chip->amplifier += change;
	
	/* Read ACPI port */	
	nval = control = inw(chip->acpi_port + 0x10);

	/* Flip CLKRUN off while running */
	if (! chip->amplifier)
		nval |= 0x2000;
	else
		nval &= ~0x2000;
	if (nval != control)
		outw(nval, chip->acpi_port + 0x10);
}