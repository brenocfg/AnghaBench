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
typedef  int u8 ;
struct TYPE_2__ {int* _8; } ;
struct oxygen {TYPE_1__ saved_registers; scalar_t__ addr; } ;

/* Variables and functions */
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

void oxygen_write8_masked(struct oxygen *chip, unsigned int reg,
			  u8 value, u8 mask)
{
	u8 tmp = inb(chip->addr + reg);
	tmp &= ~mask;
	tmp |= value & mask;
	outb(tmp, chip->addr + reg);
	chip->saved_registers._8[reg] = tmp;
}