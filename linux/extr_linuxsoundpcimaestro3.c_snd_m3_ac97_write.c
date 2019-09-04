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
struct snd_ac97 {int id; struct snd_m3* private_data; } ;

/* Variables and functions */
 unsigned short AC97_MASTER ; 
 int /*<<< orphan*/  CODEC_COMMAND ; 
 int /*<<< orphan*/  CODEC_DATA ; 
 scalar_t__ snd_m3_ac97_wait (struct snd_m3*) ; 
 int /*<<< orphan*/  snd_m3_outb (struct snd_m3*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_m3_outw (struct snd_m3*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snd_m3_ac97_write(struct snd_ac97 *ac97, unsigned short reg, unsigned short val)
{
	struct snd_m3 *chip = ac97->private_data;

	if (snd_m3_ac97_wait(chip))
		return;
	snd_m3_outw(chip, val, CODEC_DATA);
	snd_m3_outb(chip, reg & 0x7f, CODEC_COMMAND);
	/*
	 * Workaround for buggy ES1988 integrated AC'97 codec. It remains silent
	 * until the MASTER volume or mute is touched (alsactl restore does not
	 * work).
	 */
	if (ac97->id == 0x45838308 && reg == AC97_MASTER) {
		snd_m3_ac97_wait(chip);
		snd_m3_outw(chip, val, CODEC_DATA);
		snd_m3_outb(chip, reg & 0x7f, CODEC_COMMAND);
	}
}