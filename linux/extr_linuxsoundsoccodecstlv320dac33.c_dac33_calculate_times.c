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
struct tlv320dac33_priv {int fifo_mode; unsigned int alarm_threshold; unsigned int fifo_size; unsigned int nsample; unsigned int burst_rate; unsigned int uthr; int /*<<< orphan*/  t_stamp1; void* mode7_us_to_lthr; int /*<<< orphan*/  t_stamp2; void* mode1_us_burst; int /*<<< orphan*/  mode1_latency; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {unsigned int period_size; unsigned int rate; } ;

/* Variables and functions */
#define  DAC33_FIFO_MODE1 129 
#define  DAC33_FIFO_MODE7 128 
 unsigned int DAC33_MODE7_MARGIN ; 
 void* SAMPLES_TO_US (unsigned int,unsigned int) ; 
 unsigned int US_TO_SAMPLES (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTHR_FROM_PERIOD_SIZE (unsigned int,unsigned int,unsigned int) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void dac33_calculate_times(struct snd_pcm_substream *substream,
				  struct snd_soc_component *component)
{
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	unsigned int period_size = substream->runtime->period_size;
	unsigned int rate = substream->runtime->rate;
	unsigned int nsample_limit;

	/* In bypass mode we don't need to calculate */
	if (!dac33->fifo_mode)
		return;

	switch (dac33->fifo_mode) {
	case DAC33_FIFO_MODE1:
		/* Number of samples under i2c latency */
		dac33->alarm_threshold = US_TO_SAMPLES(rate,
						dac33->mode1_latency);
		nsample_limit = dac33->fifo_size - dac33->alarm_threshold;

		if (period_size <= dac33->alarm_threshold)
			/*
			 * Configure nSamaple to number of periods,
			 * which covers the latency requironment.
			 */
			dac33->nsample = period_size *
				((dac33->alarm_threshold / period_size) +
				(dac33->alarm_threshold % period_size ?
				1 : 0));
		else if (period_size > nsample_limit)
			dac33->nsample = nsample_limit;
		else
			dac33->nsample = period_size;

		dac33->mode1_us_burst = SAMPLES_TO_US(dac33->burst_rate,
						      dac33->nsample);
		dac33->t_stamp1 = 0;
		dac33->t_stamp2 = 0;
		break;
	case DAC33_FIFO_MODE7:
		dac33->uthr = UTHR_FROM_PERIOD_SIZE(period_size, rate,
						    dac33->burst_rate) + 9;
		if (dac33->uthr > (dac33->fifo_size - DAC33_MODE7_MARGIN))
			dac33->uthr = dac33->fifo_size - DAC33_MODE7_MARGIN;
		if (dac33->uthr < (DAC33_MODE7_MARGIN + 10))
			dac33->uthr = (DAC33_MODE7_MARGIN + 10);

		dac33->mode7_us_to_lthr =
				SAMPLES_TO_US(substream->runtime->rate,
					dac33->uthr - DAC33_MODE7_MARGIN + 1);
		dac33->t_stamp1 = 0;
		break;
	default:
		break;
	}

}