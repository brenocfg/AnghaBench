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
struct snd_wm8776 {unsigned short* regs; int /*<<< orphan*/  addr; } ;
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_vt1724_write_i2c (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char,unsigned short) ; 

__attribute__((used)) static void wm8776_write(struct snd_ice1712 *ice, struct snd_wm8776 *wm,
			 unsigned char reg, unsigned short val)
{
	/*
	 * WM8776 registers are up to 9 bits wide, bit 8 is placed in the LSB
	 * of the address field
	 */
	snd_vt1724_write_i2c(ice, wm->addr,
			     (reg << 1) | ((val >> 8) & 1),
			     val & 0xff);
	wm->regs[reg] = val;
}