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
struct tlv320dac33_priv {int fifo_mode; unsigned long long t_stamp1; unsigned long long t_stamp2; int alarm_threshold; unsigned long long mode1_us_burst; int nsample; int fifo_size; unsigned int uthr; unsigned int mode7_us_to_lthr; int /*<<< orphan*/  burst_rate; int /*<<< orphan*/  lock; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
typedef  unsigned int snd_pcm_sframes_t ;
struct TYPE_2__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
#define  DAC33_FIFO_BYPASS 130 
#define  DAC33_FIFO_MODE1 129 
#define  DAC33_FIFO_MODE7 128 
 int /*<<< orphan*/  DAC33_MODE7_MARGIN ; 
 int US_TO_SAMPLES (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 unsigned long long ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  likely (int) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static snd_pcm_sframes_t dac33_dai_delay(
			struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	unsigned long long t0, t1, t_now;
	unsigned int time_delta, uthr;
	int samples_out, samples_in, samples;
	snd_pcm_sframes_t delay = 0;
	unsigned long flags;

	switch (dac33->fifo_mode) {
	case DAC33_FIFO_BYPASS:
		break;
	case DAC33_FIFO_MODE1:
		spin_lock_irqsave(&dac33->lock, flags);
		t0 = dac33->t_stamp1;
		t1 = dac33->t_stamp2;
		spin_unlock_irqrestore(&dac33->lock, flags);
		t_now = ktime_to_us(ktime_get());

		/* We have not started to fill the FIFO yet, delay is 0 */
		if (!t1)
			goto out;

		if (t0 > t1) {
			/*
			 * Phase 1:
			 * After Alarm threshold, and before nSample write
			 */
			time_delta = t_now - t0;
			samples_out = time_delta ? US_TO_SAMPLES(
						substream->runtime->rate,
						time_delta) : 0;

			if (likely(dac33->alarm_threshold > samples_out))
				delay = dac33->alarm_threshold - samples_out;
			else
				delay = 0;
		} else if ((t_now - t1) <= dac33->mode1_us_burst) {
			/*
			 * Phase 2:
			 * After nSample write (during burst operation)
			 */
			time_delta = t_now - t0;
			samples_out = time_delta ? US_TO_SAMPLES(
						substream->runtime->rate,
						time_delta) : 0;

			time_delta = t_now - t1;
			samples_in = time_delta ? US_TO_SAMPLES(
						dac33->burst_rate,
						time_delta) : 0;

			samples = dac33->alarm_threshold;
			samples += (samples_in - samples_out);

			if (likely(samples > 0))
				delay = samples;
			else
				delay = 0;
		} else {
			/*
			 * Phase 3:
			 * After burst operation, before next alarm threshold
			 */
			time_delta = t_now - t0;
			samples_out = time_delta ? US_TO_SAMPLES(
						substream->runtime->rate,
						time_delta) : 0;

			samples_in = dac33->nsample;
			samples = dac33->alarm_threshold;
			samples += (samples_in - samples_out);

			if (likely(samples > 0))
				delay = samples > dac33->fifo_size ?
					dac33->fifo_size : samples;
			else
				delay = 0;
		}
		break;
	case DAC33_FIFO_MODE7:
		spin_lock_irqsave(&dac33->lock, flags);
		t0 = dac33->t_stamp1;
		uthr = dac33->uthr;
		spin_unlock_irqrestore(&dac33->lock, flags);
		t_now = ktime_to_us(ktime_get());

		/* We have not started to fill the FIFO yet, delay is 0 */
		if (!t0)
			goto out;

		if (t_now <= t0) {
			/*
			 * Either the timestamps are messed or equal. Report
			 * maximum delay
			 */
			delay = uthr;
			goto out;
		}

		time_delta = t_now - t0;
		if (time_delta <= dac33->mode7_us_to_lthr) {
			/*
			* Phase 1:
			* After burst (draining phase)
			*/
			samples_out = US_TO_SAMPLES(
					substream->runtime->rate,
					time_delta);

			if (likely(uthr > samples_out))
				delay = uthr - samples_out;
			else
				delay = 0;
		} else {
			/*
			* Phase 2:
			* During burst operation
			*/
			time_delta = time_delta - dac33->mode7_us_to_lthr;

			samples_out = US_TO_SAMPLES(
					substream->runtime->rate,
					time_delta);
			samples_in = US_TO_SAMPLES(
					dac33->burst_rate,
					time_delta);
			delay = DAC33_MODE7_MARGIN + samples_in - samples_out;

			if (unlikely(delay > uthr))
				delay = uthr;
		}
		break;
	default:
		dev_warn(component->dev, "Unhandled FIFO mode: %d\n",
							dac33->fifo_mode);
		break;
	}
out:
	return delay;
}