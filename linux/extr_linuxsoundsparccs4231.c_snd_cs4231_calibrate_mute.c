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
struct snd_cs4231 {int calibrate_mute; int* image; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t CS4231_AUX1_LEFT_INPUT ; 
 size_t CS4231_AUX1_RIGHT_INPUT ; 
 size_t CS4231_AUX2_LEFT_INPUT ; 
 size_t CS4231_AUX2_RIGHT_INPUT ; 
 size_t CS4231_LEFT_INPUT ; 
 size_t CS4231_LEFT_LINE_IN ; 
 size_t CS4231_LEFT_OUTPUT ; 
 size_t CS4231_LOOPBACK ; 
 size_t CS4231_MONO_CTRL ; 
 size_t CS4231_RIGHT_INPUT ; 
 size_t CS4231_RIGHT_LINE_IN ; 
 size_t CS4231_RIGHT_OUTPUT ; 
 int /*<<< orphan*/  snd_cs4231_dout (struct snd_cs4231*,size_t,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_cs4231_calibrate_mute(struct snd_cs4231 *chip, int mute)
{
	unsigned long flags;

	mute = mute ? 1 : 0;
	spin_lock_irqsave(&chip->lock, flags);
	if (chip->calibrate_mute == mute) {
		spin_unlock_irqrestore(&chip->lock, flags);
		return;
	}
	if (!mute) {
		snd_cs4231_dout(chip, CS4231_LEFT_INPUT,
				chip->image[CS4231_LEFT_INPUT]);
		snd_cs4231_dout(chip, CS4231_RIGHT_INPUT,
				chip->image[CS4231_RIGHT_INPUT]);
		snd_cs4231_dout(chip, CS4231_LOOPBACK,
				chip->image[CS4231_LOOPBACK]);
	}
	snd_cs4231_dout(chip, CS4231_AUX1_LEFT_INPUT,
			mute ? 0x80 : chip->image[CS4231_AUX1_LEFT_INPUT]);
	snd_cs4231_dout(chip, CS4231_AUX1_RIGHT_INPUT,
			mute ? 0x80 : chip->image[CS4231_AUX1_RIGHT_INPUT]);
	snd_cs4231_dout(chip, CS4231_AUX2_LEFT_INPUT,
			mute ? 0x80 : chip->image[CS4231_AUX2_LEFT_INPUT]);
	snd_cs4231_dout(chip, CS4231_AUX2_RIGHT_INPUT,
			mute ? 0x80 : chip->image[CS4231_AUX2_RIGHT_INPUT]);
	snd_cs4231_dout(chip, CS4231_LEFT_OUTPUT,
			mute ? 0x80 : chip->image[CS4231_LEFT_OUTPUT]);
	snd_cs4231_dout(chip, CS4231_RIGHT_OUTPUT,
			mute ? 0x80 : chip->image[CS4231_RIGHT_OUTPUT]);
	snd_cs4231_dout(chip, CS4231_LEFT_LINE_IN,
			mute ? 0x80 : chip->image[CS4231_LEFT_LINE_IN]);
	snd_cs4231_dout(chip, CS4231_RIGHT_LINE_IN,
			mute ? 0x80 : chip->image[CS4231_RIGHT_LINE_IN]);
	snd_cs4231_dout(chip, CS4231_MONO_CTRL,
			mute ? 0xc0 : chip->image[CS4231_MONO_CTRL]);
	chip->calibrate_mute = mute;
	spin_unlock_irqrestore(&chip->lock, flags);
}