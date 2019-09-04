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
struct snd_es1688 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  ES1688P (struct snd_es1688*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_es1688_dsp_command(struct snd_es1688 *chip, unsigned char val)
{
	int i;

	for (i = 10000; i; i--)
		if ((inb(ES1688P(chip, STATUS)) & 0x80) == 0) {
			outb(val, ES1688P(chip, COMMAND));
			return 1;
		}
#ifdef CONFIG_SND_DEBUG
	printk(KERN_DEBUG "snd_es1688_dsp_command: timeout (0x%x)\n", val);
#endif
	return 0;
}