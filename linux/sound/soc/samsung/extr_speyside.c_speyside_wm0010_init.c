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
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLK_AUDIO_RATE ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int speyside_wm0010_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dai *dai = rtd->codec_dai;
	int ret;

	ret = snd_soc_dai_set_sysclk(dai, 0, MCLK_AUDIO_RATE, 0);
	if (ret < 0)
		return ret;

	return 0;
}