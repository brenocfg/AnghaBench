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
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 unsigned int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_bclk_ratio (struct snd_soc_dai*,unsigned int) ; 

__attribute__((used)) static int snd_rpi_dionaudio_loco_hw_params(
	struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;

	unsigned int sample_bits =
		snd_pcm_format_physical_width(params_format(params));

	return snd_soc_dai_set_bclk_ratio(cpu_dai, sample_bits * 2);
}