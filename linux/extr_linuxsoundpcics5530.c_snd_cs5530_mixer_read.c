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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 snd_cs5530_mixer_read(unsigned long io, u8 reg)
{
	outb(reg, io + 4);
	udelay(20);
	reg = inb(io + 5);
	udelay(20);
	return reg;
}