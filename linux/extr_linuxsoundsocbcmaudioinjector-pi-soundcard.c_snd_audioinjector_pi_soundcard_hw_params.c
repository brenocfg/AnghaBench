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
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_dai_set_bclk_ratio (struct snd_soc_dai*,int) ; 

__attribute__((used)) static int snd_audioinjector_pi_soundcard_hw_params(struct snd_pcm_substream *substream,
				       struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;

	switch (params_rate(params)){
		case 8000:
			return snd_soc_dai_set_bclk_ratio(cpu_dai, 1);
		case 16000:
			return snd_soc_dai_set_bclk_ratio(cpu_dai, 750);
		case 32000:
			return snd_soc_dai_set_bclk_ratio(cpu_dai, 375);
		case 44100:
			return snd_soc_dai_set_bclk_ratio(cpu_dai, 272);
		case 48000:
			return snd_soc_dai_set_bclk_ratio(cpu_dai, 250);
		case 88200:
			return snd_soc_dai_set_bclk_ratio(cpu_dai, 136);
		case 96000:
			return snd_soc_dai_set_bclk_ratio(cpu_dai, 125);
		default:
			return snd_soc_dai_set_bclk_ratio(cpu_dai, 125);
	}
}