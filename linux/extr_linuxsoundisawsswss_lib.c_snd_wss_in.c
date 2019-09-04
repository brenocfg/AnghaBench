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
struct snd_wss {unsigned char mce_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG ; 
 int /*<<< orphan*/  REGSEL ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  snd_wss_wait (struct snd_wss*) ; 
 unsigned char wss_inb (struct snd_wss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wss_outb (struct snd_wss*,int /*<<< orphan*/ ,unsigned char) ; 

unsigned char snd_wss_in(struct snd_wss *chip, unsigned char reg)
{
	snd_wss_wait(chip);
#ifdef CONFIG_SND_DEBUG
	if (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT)
		snd_printk(KERN_DEBUG "in: auto calibration time out "
			   "- reg = 0x%x\n", reg);
#endif
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | reg);
	mb();
	return wss_inb(chip, CS4231P(REG));
}