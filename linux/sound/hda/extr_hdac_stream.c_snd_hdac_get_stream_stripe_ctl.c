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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned int channels; unsigned int rate; unsigned int sample_bits; } ;
struct hdac_bus {int dummy; } ;

/* Variables and functions */
 unsigned int AZX_GCAP_NSDO ; 
 int /*<<< orphan*/  GCAP ; 
 unsigned int snd_hdac_chip_readl (struct hdac_bus*,int /*<<< orphan*/ ) ; 

int snd_hdac_get_stream_stripe_ctl(struct hdac_bus *bus,
				   struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int channels = runtime->channels,
		     rate = runtime->rate,
		     bits_per_sample = runtime->sample_bits,
		     max_sdo_lines, value, sdo_line;

	/* T_AZA_GCAP_NSDO is 1:2 bitfields in GCAP */
	max_sdo_lines = snd_hdac_chip_readl(bus, GCAP) & AZX_GCAP_NSDO;

	/* following is from HD audio spec */
	for (sdo_line = max_sdo_lines; sdo_line > 0; sdo_line >>= 1) {
		if (rate > 48000)
			value = (channels * bits_per_sample *
					(rate / 48000)) / sdo_line;
		else
			value = (channels * bits_per_sample) / sdo_line;

		if (value >= 8)
			break;
	}

	/* stripe value: 0 for 1SDO, 1 for 2SDO, 2 for 4SDO lines */
	return sdo_line >> 1;
}