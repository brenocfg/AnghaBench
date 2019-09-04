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
struct snd_sb {int /*<<< orphan*/  mixer_lock; int /*<<< orphan*/  mode; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALS4K_CR1E_FIFO2_CONTROL ; 
 int EINVAL ; 
 int /*<<< orphan*/  SB_RATE_LOCK_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  capture_cmd (struct snd_sb*) ; 
 int /*<<< orphan*/  snd_als4_cr_write (struct snd_sb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_als4000_capture_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	int result = 0;
	
	/* FIXME race condition in here!!!
	   chip->mode non-atomic update gets consistently protected
	   by reg_lock always, _except_ for this place!!
	   Probably need to take reg_lock as outer (or inner??) lock, too.
	   (or serialize both lock operations? probably not, though... - racy?)
	*/
	spin_lock(&chip->mixer_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		chip->mode |= SB_RATE_LOCK_CAPTURE;
		snd_als4_cr_write(chip, ALS4K_CR1E_FIFO2_CONTROL,
							 capture_cmd(chip));
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		chip->mode &= ~SB_RATE_LOCK_CAPTURE;
		snd_als4_cr_write(chip, ALS4K_CR1E_FIFO2_CONTROL,
							 capture_cmd(chip));
		break;
	default:
		result = -EINVAL;
		break;
	}
	spin_unlock(&chip->mixer_lock);
	return result;
}