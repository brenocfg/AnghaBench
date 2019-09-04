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
struct snd_wss {int mce_bit; int* image; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231P (int /*<<< orphan*/ ) ; 
 size_t CS4236_EXT_REG ; 
 int /*<<< orphan*/  REG ; 
 int /*<<< orphan*/  REGSEL ; 
 unsigned char wss_inb (struct snd_wss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wss_outb (struct snd_wss*,int /*<<< orphan*/ ,unsigned char) ; 

unsigned char snd_cs4236_ext_in(struct snd_wss *chip, unsigned char reg)
{
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | 0x17);
	wss_outb(chip, CS4231P(REG),
		 reg | (chip->image[CS4236_EXT_REG] & 0x01));
#if 1
	return wss_inb(chip, CS4231P(REG));
#else
	{
		unsigned char res;
		res = wss_inb(chip, CS4231P(REG));
		printk(KERN_DEBUG "ext in : reg = 0x%x, val = 0x%x\n",
		       reg, res);
		return res;
	}
#endif
}