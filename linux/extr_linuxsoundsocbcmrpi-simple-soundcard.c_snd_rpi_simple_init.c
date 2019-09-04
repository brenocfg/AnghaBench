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
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; int /*<<< orphan*/  card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_rpi_simple_drvdata {scalar_t__ fixed_bclk_ratio; } ;

/* Variables and functions */
 struct snd_rpi_simple_drvdata* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_bclk_ratio (struct snd_soc_dai*,scalar_t__) ; 

__attribute__((used)) static int snd_rpi_simple_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_rpi_simple_drvdata *drvdata =
		snd_soc_card_get_drvdata(rtd->card);
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;

	if (drvdata->fixed_bclk_ratio > 0)
		return snd_soc_dai_set_bclk_ratio(cpu_dai,
				drvdata->fixed_bclk_ratio);

	return 0;
}