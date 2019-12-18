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
struct snd_pcm_hardware {int info; int periods_min; int period_bytes_min; int channels_max; int period_bytes_max; int buffer_bytes_max; int /*<<< orphan*/  periods_max; } ;
struct snd_pcm_runtime {struct snd_pcm_hardware hw; } ;
struct amdtp_stream {int flags; } ;

/* Variables and functions */
 int CIP_BLOCKING ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_TIME ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int SNDRV_PCM_INFO_BATCH ; 
 int SNDRV_PCM_INFO_BLOCK_TRANSFER ; 
 int SNDRV_PCM_INFO_INTERLEAVED ; 
 int SNDRV_PCM_INFO_JOINT_DUPLEX ; 
 int SNDRV_PCM_INFO_MMAP ; 
 int SNDRV_PCM_INFO_MMAP_VALID ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  apply_constraint_to_size ; 
 int snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int amdtp_stream_add_pcm_hw_constraints(struct amdtp_stream *s,
					struct snd_pcm_runtime *runtime)
{
	struct snd_pcm_hardware *hw = &runtime->hw;
	int err;

	hw->info = SNDRV_PCM_INFO_BATCH |
		   SNDRV_PCM_INFO_BLOCK_TRANSFER |
		   SNDRV_PCM_INFO_INTERLEAVED |
		   SNDRV_PCM_INFO_JOINT_DUPLEX |
		   SNDRV_PCM_INFO_MMAP |
		   SNDRV_PCM_INFO_MMAP_VALID;

	/* SNDRV_PCM_INFO_BATCH */
	hw->periods_min = 2;
	hw->periods_max = UINT_MAX;

	/* bytes for a frame */
	hw->period_bytes_min = 4 * hw->channels_max;

	/* Just to prevent from allocating much pages. */
	hw->period_bytes_max = hw->period_bytes_min * 2048;
	hw->buffer_bytes_max = hw->period_bytes_max * hw->periods_min;

	/*
	 * Currently firewire-lib processes 16 packets in one software
	 * interrupt callback. This equals to 2msec but actually the
	 * interval of the interrupts has a jitter.
	 * Additionally, even if adding a constraint to fit period size to
	 * 2msec, actual calculated frames per period doesn't equal to 2msec,
	 * depending on sampling rate.
	 * Anyway, the interval to call snd_pcm_period_elapsed() cannot 2msec.
	 * Here let us use 5msec for safe period interrupt.
	 */
	err = snd_pcm_hw_constraint_minmax(runtime,
					   SNDRV_PCM_HW_PARAM_PERIOD_TIME,
					   5000, UINT_MAX);
	if (err < 0)
		goto end;

	/* Non-Blocking stream has no more constraints */
	if (!(s->flags & CIP_BLOCKING))
		goto end;

	/*
	 * One AMDTP packet can include some frames. In blocking mode, the
	 * number equals to SYT_INTERVAL. So the number is 8, 16 or 32,
	 * depending on its sampling rate. For accurate period interrupt, it's
	 * preferrable to align period/buffer sizes to current SYT_INTERVAL.
	 */
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				  apply_constraint_to_size, NULL,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		goto end;
	err = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
				  apply_constraint_to_size, NULL,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (err < 0)
		goto end;
end:
	return err;
}