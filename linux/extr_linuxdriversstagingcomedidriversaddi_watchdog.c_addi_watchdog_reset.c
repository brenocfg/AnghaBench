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
 scalar_t__ ADDI_TCW_CTRL_REG ; 
 scalar_t__ ADDI_TCW_RELOAD_REG ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

void addi_watchdog_reset(unsigned long iobase)
{
	outl(0x0, iobase + ADDI_TCW_CTRL_REG);
	outl(0x0, iobase + ADDI_TCW_RELOAD_REG);
}