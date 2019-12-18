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
struct snd_pcm_substream {TYPE_1__* pstr; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_korg1212 {size_t cardState; scalar_t__ playback_pid; scalar_t__ capture_pid; int clkRate; int /*<<< orphan*/  lock; int /*<<< orphan*/  periodsize; int /*<<< orphan*/  channels; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {scalar_t__ stream; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  K1212_PERIOD_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  _snd_pcm_hw_param_setempty (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_rate (struct snd_pcm_hw_params*) ; 
 int snd_korg1212_SetRate (struct snd_korg1212*,scalar_t__) ; 
 struct snd_korg1212* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * stateName ; 

__attribute__((used)) static int snd_korg1212_hw_params(struct snd_pcm_substream *substream,
                             struct snd_pcm_hw_params *params)
{
        unsigned long flags;
        struct snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
        int err;
	pid_t this_pid;
	pid_t other_pid;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_hw_params [%s]\n",
			   stateName[korg1212->cardState]);

        spin_lock_irqsave(&korg1212->lock, flags);

	if (substream->pstr->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		this_pid = korg1212->playback_pid;
		other_pid = korg1212->capture_pid;
	} else {
		this_pid = korg1212->capture_pid;
		other_pid = korg1212->playback_pid;
	}

	if ((other_pid > 0) && (this_pid != other_pid)) {

		/* The other stream is open, and not by the same
		   task as this one. Make sure that the parameters
		   that matter are the same.
		 */

		if ((int)params_rate(params) != korg1212->clkRate) {
			spin_unlock_irqrestore(&korg1212->lock, flags);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
			return -EBUSY;
		}

        	spin_unlock_irqrestore(&korg1212->lock, flags);
	        return 0;
	}

        if ((err = snd_korg1212_SetRate(korg1212, params_rate(params))) < 0) {
                spin_unlock_irqrestore(&korg1212->lock, flags);
                return err;
        }

	korg1212->channels = params_channels(params);
        korg1212->periodsize = K1212_PERIOD_BYTES;

        spin_unlock_irqrestore(&korg1212->lock, flags);

        return 0;
}