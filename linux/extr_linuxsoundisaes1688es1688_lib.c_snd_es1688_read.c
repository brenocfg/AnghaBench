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
 int /*<<< orphan*/  snd_es1688_dsp_command (struct snd_es1688*,unsigned char) ; 
 int snd_es1688_dsp_get_byte (struct snd_es1688*) ; 

__attribute__((used)) static int snd_es1688_read(struct snd_es1688 *chip, unsigned char reg)
{
	/* Read a byte from an extended mode register of ES1688 */
	if (!snd_es1688_dsp_command(chip, 0xc0))
		return -1;
	if (!snd_es1688_dsp_command(chip, reg))
		return -1;
	return snd_es1688_dsp_get_byte(chip);
}