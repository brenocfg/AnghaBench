#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pdacf {int chip_status; TYPE_1__* ak4117; int /*<<< orphan*/  reg_lock; scalar_t__ pcm_running; int /*<<< orphan*/  pcm_tdone; int /*<<< orphan*/  pcm_hwptr; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int rate; } ;
struct TYPE_2__ {int rcs0; } ;

/* Variables and functions */
 int AK4117_CHECK_NO_RATE ; 
 int AK4117_CHECK_NO_STAT ; 
 int AK4117_UNLCK ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 unsigned short PDAUDIOCF_RECORD ; 
 int /*<<< orphan*/  PDAUDIOCF_REG_SCR ; 
 int PDAUDIOCF_STAT_IS_STALE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned short pdacf_reg_read (struct snd_pdacf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdacf_reg_write (struct snd_pdacf*,int /*<<< orphan*/ ,unsigned short) ; 
 int snd_ak4117_check_rate_and_errors (TYPE_1__*,int) ; 
 struct snd_pdacf* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pdacf_pcm_trigger(struct snd_pcm_substream *subs, int cmd)
{
	struct snd_pdacf *chip = snd_pcm_substream_chip(subs);
	struct snd_pcm_runtime *runtime = subs->runtime;
	int inc, ret = 0, rate;
	unsigned short mask, val, tmp;

	if (chip->chip_status & PDAUDIOCF_STAT_IS_STALE)
		return -EBUSY;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		chip->pcm_hwptr = 0;
		chip->pcm_tdone = 0;
		/* fall thru */
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		mask = 0;
		val = PDAUDIOCF_RECORD;
		inc = 1;
		rate = snd_ak4117_check_rate_and_errors(chip->ak4117, AK4117_CHECK_NO_STAT|AK4117_CHECK_NO_RATE);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		mask = PDAUDIOCF_RECORD;
		val = 0;
		inc = -1;
		rate = 0;
		break;
	default:
		return -EINVAL;
	}
	mutex_lock(&chip->reg_lock);
	chip->pcm_running += inc;
	tmp = pdacf_reg_read(chip, PDAUDIOCF_REG_SCR);
	if (chip->pcm_running) {
		if ((chip->ak4117->rcs0 & AK4117_UNLCK) || runtime->rate != rate) {
			chip->pcm_running -= inc;
			ret = -EIO;
			goto __end;
		}
	}
	tmp &= ~mask;
	tmp |= val;
	pdacf_reg_write(chip, PDAUDIOCF_REG_SCR, tmp);
      __end:
	mutex_unlock(&chip->reg_lock);
	snd_ak4117_check_rate_and_errors(chip->ak4117, AK4117_CHECK_NO_RATE);
	return ret;
}