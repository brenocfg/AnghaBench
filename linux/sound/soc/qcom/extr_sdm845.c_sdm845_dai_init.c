#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; struct snd_soc_dai* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_dai {int id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct snd_jack {int /*<<< orphan*/  private_free; struct snd_soc_component* private_data; } ;
struct TYPE_3__ {struct snd_jack* jack; } ;
struct sdm845_snd_data {int jack_setup; TYPE_1__ jack; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  KEY_PLAYPAUSE ; 
 int /*<<< orphan*/  KEY_VOICECOMMAND ; 
 int /*<<< orphan*/  KEY_VOLUMEDOWN ; 
 int /*<<< orphan*/  KEY_VOLUMEUP ; 
#define  PRIMARY_MI2S_RX 128 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_BTN_3 ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_HEADSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdm845_jack_free ; 
 int /*<<< orphan*/  snd_jack_set_key (struct snd_jack*,int,int /*<<< orphan*/ ) ; 
 struct sdm845_snd_data* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_card_jack_new (struct snd_soc_card*,char*,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_soc_component_set_jack (struct snd_soc_component*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdm845_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component;
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct sdm845_snd_data *pdata = snd_soc_card_get_drvdata(card);
	struct snd_jack *jack;
	int rval;

	if (!pdata->jack_setup) {
		rval = snd_soc_card_jack_new(card, "Headset Jack",
				SND_JACK_HEADSET |
				SND_JACK_HEADPHONE |
				SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				SND_JACK_BTN_2 | SND_JACK_BTN_3,
				&pdata->jack, NULL, 0);

		if (rval < 0) {
			dev_err(card->dev, "Unable to add Headphone Jack\n");
			return rval;
		}

		jack = pdata->jack.jack;

		snd_jack_set_key(jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
		snd_jack_set_key(jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
		snd_jack_set_key(jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
		snd_jack_set_key(jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);
		pdata->jack_setup = true;
	}

	switch (cpu_dai->id) {
	case PRIMARY_MI2S_RX:
		jack  = pdata->jack.jack;
		component = codec_dai->component;

		jack->private_data = component;
		jack->private_free = sdm845_jack_free;
		rval = snd_soc_component_set_jack(component,
						  &pdata->jack, NULL);
		if (rval != 0 && rval != -ENOTSUPP) {
			dev_warn(card->dev, "Failed to set jack: %d\n", rval);
			return rval;
		}
		break;
	default:
		break;
	}

	return 0;
}