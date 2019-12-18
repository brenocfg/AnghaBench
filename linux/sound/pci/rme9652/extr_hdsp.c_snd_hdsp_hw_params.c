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
struct hdsp {int control_register; int creg_spdif_stream; scalar_t__ playback_pid; scalar_t__ capture_pid; scalar_t__ system_sample_rate; int period_bytes; int /*<<< orphan*/  lock; int /*<<< orphan*/  clock_source_locked; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {scalar_t__ stream; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int HDSP_SPDIFEmphasis ; 
 int HDSP_SPDIFNonAudio ; 
 int HDSP_SPDIFProfessional ; 
 int /*<<< orphan*/  HDSP_controlRegister ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  _snd_pcm_hw_param_setempty (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 scalar_t__ hdsp_check_for_firmware (struct hdsp*,int) ; 
 scalar_t__ hdsp_check_for_iobox (struct hdsp*) ; 
 int hdsp_set_interrupt_interval (struct hdsp*,int) ; 
 int hdsp_set_rate (struct hdsp*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int) ; 
 int params_period_size (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_rate (struct snd_pcm_hw_params*) ; 
 struct hdsp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdsp_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params)
{
	struct hdsp *hdsp = snd_pcm_substream_chip(substream);
	int err;
	pid_t this_pid;
	pid_t other_pid;

	if (hdsp_check_for_iobox (hdsp))
		return -EIO;

	if (hdsp_check_for_firmware(hdsp, 1))
		return -EIO;

	spin_lock_irq(&hdsp->lock);

	if (substream->pstr->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		hdsp->control_register &= ~(HDSP_SPDIFProfessional | HDSP_SPDIFNonAudio | HDSP_SPDIFEmphasis);
		hdsp_write(hdsp, HDSP_controlRegister, hdsp->control_register |= hdsp->creg_spdif_stream);
		this_pid = hdsp->playback_pid;
		other_pid = hdsp->capture_pid;
	} else {
		this_pid = hdsp->capture_pid;
		other_pid = hdsp->playback_pid;
	}

	if ((other_pid > 0) && (this_pid != other_pid)) {

		/* The other stream is open, and not by the same
		   task as this one. Make sure that the parameters
		   that matter are the same.
		 */

		if (params_rate(params) != hdsp->system_sample_rate) {
			spin_unlock_irq(&hdsp->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
			return -EBUSY;
		}

		if (params_period_size(params) != hdsp->period_bytes / 4) {
			spin_unlock_irq(&hdsp->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
			return -EBUSY;
		}

		/* We're fine. */

		spin_unlock_irq(&hdsp->lock);
 		return 0;

	} else {
		spin_unlock_irq(&hdsp->lock);
	}

	/* how to make sure that the rate matches an externally-set one ?
	 */

	spin_lock_irq(&hdsp->lock);
	if (! hdsp->clock_source_locked) {
		if ((err = hdsp_set_rate(hdsp, params_rate(params), 0)) < 0) {
			spin_unlock_irq(&hdsp->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
			return err;
		}
	}
	spin_unlock_irq(&hdsp->lock);

	if ((err = hdsp_set_interrupt_interval(hdsp, params_period_size(params))) < 0) {
		_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
		return err;
	}

	return 0;
}