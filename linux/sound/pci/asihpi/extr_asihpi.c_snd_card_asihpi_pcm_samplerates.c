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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct snd_pcm_hardware {unsigned int rates; unsigned int rate_min; unsigned int rate_max; } ;
struct snd_card_asihpi {TYPE_1__* pci; int /*<<< orphan*/  h_mixer; scalar_t__ support_mrx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_CONTROL_SAMPLECLOCK ; 
 int /*<<< orphan*/  HPI_SOURCENODE_CLOCK_SOURCE ; 
 unsigned int SNDRV_PCM_RATE_11025 ; 
 unsigned int SNDRV_PCM_RATE_16000 ; 
 unsigned int SNDRV_PCM_RATE_176400 ; 
 unsigned int SNDRV_PCM_RATE_192000 ; 
 unsigned int SNDRV_PCM_RATE_22050 ; 
 unsigned int SNDRV_PCM_RATE_32000 ; 
 unsigned int SNDRV_PCM_RATE_44100 ; 
 unsigned int SNDRV_PCM_RATE_48000 ; 
 unsigned int SNDRV_PCM_RATE_5512 ; 
 unsigned int SNDRV_PCM_RATE_64000 ; 
 unsigned int SNDRV_PCM_RATE_8000 ; 
 unsigned int SNDRV_PCM_RATE_8000_96000 ; 
 unsigned int SNDRV_PCM_RATE_88200 ; 
 unsigned int SNDRV_PCM_RATE_96000 ; 
 unsigned int SNDRV_PCM_RATE_CONTINUOUS ; 
 unsigned int SNDRV_PCM_RATE_KNOT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ hpi_mixer_get_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ hpi_sample_clock_get_sample_rate (int,int*) ; 
 scalar_t__ hpi_sample_clock_query_local_rate (int,int,int*) ; 
 unsigned int max (unsigned int,int) ; 
 unsigned int min (unsigned int,int) ; 

__attribute__((used)) static void snd_card_asihpi_pcm_samplerates(struct snd_card_asihpi *asihpi,
					 struct snd_pcm_hardware *pcmhw)
{
	u16 err;
	u32 h_control;
	u32 sample_rate;
	int idx;
	unsigned int rate_min = 200000;
	unsigned int rate_max = 0;
	unsigned int rates = 0;

	if (asihpi->support_mrx) {
		rates |= SNDRV_PCM_RATE_CONTINUOUS;
		rates |= SNDRV_PCM_RATE_8000_96000;
		rate_min = 8000;
		rate_max = 100000;
	} else {
		/* on cards without SRC,
		   valid rates are determined by sampleclock */
		err = hpi_mixer_get_control(asihpi->h_mixer,
					  HPI_SOURCENODE_CLOCK_SOURCE, 0, 0, 0,
					  HPI_CONTROL_SAMPLECLOCK, &h_control);
		if (err) {
			dev_err(&asihpi->pci->dev,
				"No local sampleclock, err %d\n", err);
		}

		for (idx = -1; idx < 100; idx++) {
			if (idx == -1) {
				if (hpi_sample_clock_get_sample_rate(h_control,
								&sample_rate))
					continue;
			} else if (hpi_sample_clock_query_local_rate(h_control,
							idx, &sample_rate)) {
				break;
			}

			rate_min = min(rate_min, sample_rate);
			rate_max = max(rate_max, sample_rate);

			switch (sample_rate) {
			case 5512:
				rates |= SNDRV_PCM_RATE_5512;
				break;
			case 8000:
				rates |= SNDRV_PCM_RATE_8000;
				break;
			case 11025:
				rates |= SNDRV_PCM_RATE_11025;
				break;
			case 16000:
				rates |= SNDRV_PCM_RATE_16000;
				break;
			case 22050:
				rates |= SNDRV_PCM_RATE_22050;
				break;
			case 32000:
				rates |= SNDRV_PCM_RATE_32000;
				break;
			case 44100:
				rates |= SNDRV_PCM_RATE_44100;
				break;
			case 48000:
				rates |= SNDRV_PCM_RATE_48000;
				break;
			case 64000:
				rates |= SNDRV_PCM_RATE_64000;
				break;
			case 88200:
				rates |= SNDRV_PCM_RATE_88200;
				break;
			case 96000:
				rates |= SNDRV_PCM_RATE_96000;
				break;
			case 176400:
				rates |= SNDRV_PCM_RATE_176400;
				break;
			case 192000:
				rates |= SNDRV_PCM_RATE_192000;
				break;
			default: /* some other rate */
				rates |= SNDRV_PCM_RATE_KNOT;
			}
		}
	}

	pcmhw->rates = rates;
	pcmhw->rate_min = rate_min;
	pcmhw->rate_max = rate_max;
}