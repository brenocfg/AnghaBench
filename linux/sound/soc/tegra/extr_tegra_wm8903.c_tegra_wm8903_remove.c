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
struct snd_soc_pcm_runtime {struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {TYPE_1__* dai_link; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8903_mic_detect (struct snd_soc_component*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_wm8903_remove(struct snd_soc_card *card)
{
	struct snd_soc_pcm_runtime *rtd =
		snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_component *component = codec_dai->component;

	wm8903_mic_detect(component, NULL, 0, 0);

	return 0;
}