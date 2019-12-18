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
struct snd_rme9652 {int control_register; int creg_spdif_stream; scalar_t__ playback_pid; scalar_t__ capture_pid; int period_bytes; int /*<<< orphan*/  lock; } ;
struct snd_pcm_substream {TYPE_1__* pstr; } ;
struct snd_pcm_hw_params {int dummy; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {scalar_t__ stream; } ;

/* Variables and functions */
 int EBUSY ; 
 int RME9652_Dolby ; 
 int RME9652_EMP ; 
 int RME9652_PRO ; 
 int /*<<< orphan*/  RME9652_control_register ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  _snd_pcm_hw_param_setempty (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int params_period_size (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_rate (struct snd_pcm_hw_params*) ; 
 int rme9652_adat_sample_rate (struct snd_rme9652*) ; 
 int rme9652_set_interrupt_interval (struct snd_rme9652*,int) ; 
 int rme9652_set_rate (struct snd_rme9652*,scalar_t__) ; 
 int /*<<< orphan*/  rme9652_write (struct snd_rme9652*,int /*<<< orphan*/ ,int) ; 
 struct snd_rme9652* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_rme9652_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params)
{
	struct snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	int err;
	pid_t this_pid;
	pid_t other_pid;

	spin_lock_irq(&rme9652->lock);

	if (substream->pstr->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		rme9652->control_register &= ~(RME9652_PRO | RME9652_Dolby | RME9652_EMP);
		rme9652_write(rme9652, RME9652_control_register, rme9652->control_register |= rme9652->creg_spdif_stream);
		this_pid = rme9652->playback_pid;
		other_pid = rme9652->capture_pid;
	} else {
		this_pid = rme9652->capture_pid;
		other_pid = rme9652->playback_pid;
	}

	if ((other_pid > 0) && (this_pid != other_pid)) {

		/* The other stream is open, and not by the same
		   task as this one. Make sure that the parameters
		   that matter are the same.
		 */

		if ((int)params_rate(params) !=
		    rme9652_adat_sample_rate(rme9652)) {
			spin_unlock_irq(&rme9652->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
			return -EBUSY;
		}

		if (params_period_size(params) != rme9652->period_bytes / 4) {
			spin_unlock_irq(&rme9652->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
			return -EBUSY;
		}

		/* We're fine. */

		spin_unlock_irq(&rme9652->lock);
 		return 0;

	} else {
		spin_unlock_irq(&rme9652->lock);
	}

	/* how to make sure that the rate matches an externally-set one ?
	 */

	if ((err = rme9652_set_rate(rme9652, params_rate(params))) < 0) {
		_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
		return err;
	}

	if ((err = rme9652_set_interrupt_interval(rme9652, params_period_size(params))) < 0) {
		_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
		return err;
	}

	return 0;
}