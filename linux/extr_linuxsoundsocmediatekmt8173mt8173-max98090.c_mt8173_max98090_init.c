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
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int max98090_mic_detect (struct snd_soc_component*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt8173_max98090_jack ; 
 int /*<<< orphan*/  mt8173_max98090_jack_pins ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt8173_max98090_init(struct snd_soc_pcm_runtime *runtime)
{
	int ret;
	struct snd_soc_card *card = runtime->card;
	struct snd_soc_component *component = runtime->codec_dai->component;

	/* enable jack detection */
	ret = snd_soc_card_jack_new(card, "Headphone", SND_JACK_HEADPHONE,
				    &mt8173_max98090_jack,
				    mt8173_max98090_jack_pins,
				    ARRAY_SIZE(mt8173_max98090_jack_pins));
	if (ret) {
		dev_err(card->dev, "Can't create a new Jack %d\n", ret);
		return ret;
	}

	return max98090_mic_detect(component, &mt8173_max98090_jack);
}