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
struct snd_soc_pcm_runtime {struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1977_SYSCLK ; 
 int /*<<< orphan*/  ADAU1977_SYSCLK_SRC_MCLK ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int snd_soc_component_set_sysclk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_tdm_slot (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1977_init(struct snd_soc_pcm_runtime *rtd)
{
	int ret;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;

	ret = snd_soc_dai_set_tdm_slot(codec_dai, 0, 0, 0, 0);
	if (ret < 0)
		return ret;

	return snd_soc_component_set_sysclk(codec_dai->component,
			ADAU1977_SYSCLK, ADAU1977_SYSCLK_SRC_MCLK,
			11289600, SND_SOC_CLOCK_IN);
}