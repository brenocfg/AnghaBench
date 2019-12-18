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
struct snd_pcm_runtime {struct q6asm_dai_rtd* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct q6asm_dai_rtd {int bits_per_sample; int /*<<< orphan*/  periods; int /*<<< orphan*/  pcm_size; } ;

/* Variables and functions */
#define  SNDRV_PCM_FORMAT_S16_LE 129 
#define  SNDRV_PCM_FORMAT_S24_LE 128 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_periods (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int q6asm_dai_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct q6asm_dai_rtd *prtd = runtime->private_data;

	prtd->pcm_size = params_buffer_bytes(params);
	prtd->periods = params_periods(params);

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		prtd->bits_per_sample = 16;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		prtd->bits_per_sample = 24;
		break;
	}

	return 0;
}