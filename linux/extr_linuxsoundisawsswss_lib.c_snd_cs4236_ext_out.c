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
struct snd_wss {int mce_bit; int* image; unsigned char* eimage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231P (int /*<<< orphan*/ ) ; 
 size_t CS4236_EXT_REG ; 
 size_t CS4236_REG (unsigned char) ; 
 int /*<<< orphan*/  REG ; 
 int /*<<< orphan*/  REGSEL ; 
 int /*<<< orphan*/  wss_outb (struct snd_wss*,int /*<<< orphan*/ ,unsigned char) ; 

void snd_cs4236_ext_out(struct snd_wss *chip, unsigned char reg,
			unsigned char val)
{
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | 0x17);
	wss_outb(chip, CS4231P(REG),
		 reg | (chip->image[CS4236_EXT_REG] & 0x01));
	wss_outb(chip, CS4231P(REG), val);
	chip->eimage[CS4236_REG(reg)] = val;
#if 0
	printk(KERN_DEBUG "ext out : reg = 0x%x, val = 0x%x\n", reg, val);
#endif
}