#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_soc_card* card; int /*<<< orphan*/  codec_dai; } ;
struct snd_soc_jack {int dummy; } ;
struct TYPE_3__ {int idle_bias_off; } ;
struct snd_soc_card {TYPE_2__* dev; TYPE_1__ dapm; } ;
struct byt_max98090_private {struct snd_soc_jack jack; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M98090_REG_SYSTEM_CLOCK ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_LINEOUT ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  hs_jack_gpios ; 
 int /*<<< orphan*/  hs_jack_pins ; 
 struct byt_max98090_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int,struct snd_soc_jack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_sysclk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_add_gpiods (int /*<<< orphan*/ ,struct snd_soc_jack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int byt_max98090_init(struct snd_soc_pcm_runtime *runtime)
{
	int ret;
	struct snd_soc_card *card = runtime->card;
	struct byt_max98090_private *drv = snd_soc_card_get_drvdata(card);
	struct snd_soc_jack *jack = &drv->jack;

	card->dapm.idle_bias_off = true;

	ret = snd_soc_dai_set_sysclk(runtime->codec_dai,
				     M98090_REG_SYSTEM_CLOCK,
				     25000000, SND_SOC_CLOCK_IN);
	if (ret < 0) {
		dev_err(card->dev, "Can't set codec clock %d\n", ret);
		return ret;
	}

	/* Enable jack detection */
	ret = snd_soc_card_jack_new(runtime->card, "Headset",
				    SND_JACK_LINEOUT | SND_JACK_HEADSET, jack,
				    hs_jack_pins, ARRAY_SIZE(hs_jack_pins));
	if (ret)
		return ret;

	return snd_soc_jack_add_gpiods(card->dev->parent, jack,
				       ARRAY_SIZE(hs_jack_gpios),
				       hs_jack_gpios);
}