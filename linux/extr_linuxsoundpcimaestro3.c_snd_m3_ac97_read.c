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
struct snd_m3 {int dummy; } ;
struct snd_ac97 {struct snd_m3* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_COMMAND ; 
 int /*<<< orphan*/  CODEC_DATA ; 
 scalar_t__ snd_m3_ac97_wait (struct snd_m3*) ; 
 unsigned short snd_m3_inw (struct snd_m3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_m3_outb (struct snd_m3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short
snd_m3_ac97_read(struct snd_ac97 *ac97, unsigned short reg)
{
	struct snd_m3 *chip = ac97->private_data;
	unsigned short data = 0xffff;

	if (snd_m3_ac97_wait(chip))
		goto fail;
	snd_m3_outb(chip, 0x80 | (reg & 0x7f), CODEC_COMMAND);
	if (snd_m3_ac97_wait(chip))
		goto fail;
	data = snd_m3_inw(chip, CODEC_DATA);
fail:
	return data;
}