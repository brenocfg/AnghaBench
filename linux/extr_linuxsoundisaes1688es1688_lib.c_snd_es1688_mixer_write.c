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
 int /*<<< orphan*/  ES1688P (struct snd_es1688*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIXER_ADDR ; 
 int /*<<< orphan*/  MIXER_DATA ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void snd_es1688_mixer_write(struct snd_es1688 *chip,
			    unsigned char reg, unsigned char data)
{
	outb(reg, ES1688P(chip, MIXER_ADDR));
	udelay(10);
	outb(data, ES1688P(chip, MIXER_DATA));
	udelay(10);
}