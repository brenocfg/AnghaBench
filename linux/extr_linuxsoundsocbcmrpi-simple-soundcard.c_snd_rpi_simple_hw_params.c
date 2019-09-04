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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_rpi_simple_drvdata {scalar_t__ fixed_bclk_ratio; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 unsigned int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 struct snd_rpi_simple_drvdata* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_bclk_ratio (struct snd_soc_dai*,unsigned int) ; 

__attribute__((used)) static int snd_rpi_simple_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_rpi_simple_drvdata *drvdata;
	unsigned int sample_bits;

	drvdata = snd_soc_card_get_drvdata(rtd->card);

	if (drvdata->fixed_bclk_ratio > 0)
		return 0; // BCLK is configured in .init

	/* The simple drivers just set the bclk_ratio to sample_bits * 2 so
	 * hard-code this for now. More complex drivers could just replace
	 * the hw_params routine.
	 */
	sample_bits = snd_pcm_format_physical_width(params_format(params));
	return snd_soc_dai_set_bclk_ratio(cpu_dai, sample_bits * 2);
}