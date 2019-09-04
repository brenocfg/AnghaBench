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

/* Variables and functions */
 scalar_t__ PLX9052_INTCSR ; 
 int PLX9052_INTCSR_LI1ENAB ; 
 int PLX9052_INTCSR_LI1POL ; 
 int PLX9052_INTCSR_LI2ENAB ; 
 int PLX9052_INTCSR_LI2POL ; 
 int PLX9052_INTCSR_PCIENAB ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void plx9050_interrupt_control(unsigned long io_base,
				      bool int1_enable,
				      bool int1_active_high,
				      bool int2_enable,
				      bool int2_active_high,
				      bool interrupt_enable)
{
	int flags = 0;

	if (int1_enable)
		flags |= PLX9052_INTCSR_LI1ENAB;
	if (int1_active_high)
		flags |= PLX9052_INTCSR_LI1POL;
	if (int2_enable)
		flags |= PLX9052_INTCSR_LI2ENAB;
	if (int2_active_high)
		flags |= PLX9052_INTCSR_LI2POL;

	if (interrupt_enable)
		flags |= PLX9052_INTCSR_PCIENAB;

	outb(flags, io_base + PLX9052_INTCSR);
}