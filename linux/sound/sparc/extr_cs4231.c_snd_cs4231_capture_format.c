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
struct snd_pcm_hw_params {int dummy; } ;
struct snd_cs4231 {int* image; int /*<<< orphan*/  mce_mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t CS4231_IFACE_CTRL ; 
 int CS4231_PLAYBACK_ENABLE ; 
 size_t CS4231_PLAYBK_FORMAT ; 
 size_t CS4231_REC_FORMAT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_cs4231_calibrate_mute (struct snd_cs4231*,int) ; 
 int /*<<< orphan*/  snd_cs4231_mce_down (struct snd_cs4231*) ; 
 int /*<<< orphan*/  snd_cs4231_mce_up (struct snd_cs4231*) ; 
 int /*<<< orphan*/  snd_cs4231_out (struct snd_cs4231*,size_t,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_cs4231_capture_format(struct snd_cs4231 *chip,
				      struct snd_pcm_hw_params *params,
				      unsigned char cdfr)
{
	unsigned long flags;

	mutex_lock(&chip->mce_mutex);
	snd_cs4231_calibrate_mute(chip, 1);

	snd_cs4231_mce_up(chip);

	spin_lock_irqsave(&chip->lock, flags);
	if (!(chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE)) {
		snd_cs4231_out(chip, CS4231_PLAYBK_FORMAT,
			       ((chip->image[CS4231_PLAYBK_FORMAT]) & 0xf0) |
			       (cdfr & 0x0f));
		spin_unlock_irqrestore(&chip->lock, flags);
		snd_cs4231_mce_down(chip);
		snd_cs4231_mce_up(chip);
		spin_lock_irqsave(&chip->lock, flags);
	}
	snd_cs4231_out(chip, CS4231_REC_FORMAT, cdfr);
	spin_unlock_irqrestore(&chip->lock, flags);

	snd_cs4231_mce_down(chip);

	snd_cs4231_calibrate_mute(chip, 0);
	mutex_unlock(&chip->mce_mutex);
}