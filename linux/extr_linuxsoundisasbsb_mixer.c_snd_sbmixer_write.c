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
struct snd_sb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXER_ADDR ; 
 int /*<<< orphan*/  MIXER_DATA ; 
 int /*<<< orphan*/  SBP (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void snd_sbmixer_write(struct snd_sb *chip, unsigned char reg, unsigned char data)
{
	outb(reg, SBP(chip, MIXER_ADDR));
	udelay(10);
	outb(data, SBP(chip, MIXER_DATA));
	udelay(10);
#ifdef IO_DEBUG
	snd_printk(KERN_DEBUG "mixer_write 0x%x 0x%x\n", reg, data);
#endif
}