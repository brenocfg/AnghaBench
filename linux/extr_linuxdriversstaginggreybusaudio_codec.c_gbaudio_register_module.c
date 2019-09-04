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
struct snd_soc_jack {int dummy; } ;
struct snd_soc_codec {int /*<<< orphan*/  dev; int /*<<< orphan*/  dapm; TYPE_1__* card; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; } ;
struct gbaudio_module_info {int /*<<< orphan*/  name; int /*<<< orphan*/  list; int /*<<< orphan*/  num_dapm_routes; int /*<<< orphan*/  dapm_routes; int /*<<< orphan*/  num_controls; int /*<<< orphan*/  controls; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; scalar_t__ num_dais; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  module_list; int /*<<< orphan*/  dev; struct snd_soc_codec* codec; } ;
struct TYPE_3__ {scalar_t__ instantiated; struct snd_card* snd_card; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int gbaudio_init_jack (struct gbaudio_module_info*,struct snd_soc_codec*) ; 
 TYPE_2__* gbcodec ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_add_codec_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_link_component_dai_widgets (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_new_widgets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int gbaudio_register_module(struct gbaudio_module_info *module)
{
	int ret;
	struct snd_soc_codec *codec;
	struct snd_card *card;
	struct snd_soc_jack *jack = NULL;

	if (!gbcodec) {
		dev_err(module->dev, "GB Codec not yet probed\n");
		return -EAGAIN;
	}

	codec = gbcodec->codec;
	card = codec->card->snd_card;

	down_write(&card->controls_rwsem);

	if (module->num_dais) {
		dev_err(gbcodec->dev,
			"%d:DAIs not supported via gbcodec driver\n",
			module->num_dais);
		up_write(&card->controls_rwsem);
		return -EINVAL;
	}

	ret = gbaudio_init_jack(module, codec);
	if (ret) {
		up_write(&card->controls_rwsem);
		return ret;
	}

	if (module->dapm_widgets)
		snd_soc_dapm_new_controls(&codec->dapm, module->dapm_widgets,
					  module->num_dapm_widgets);
	if (module->controls)
		snd_soc_add_codec_controls(codec, module->controls,
					   module->num_controls);
	if (module->dapm_routes)
		snd_soc_dapm_add_routes(&codec->dapm, module->dapm_routes,
					module->num_dapm_routes);

	/* card already instantiated, create widgets here only */
	if (codec->card->instantiated) {
		snd_soc_dapm_link_component_dai_widgets(codec->card,
							&codec->dapm);
#ifdef CONFIG_SND_JACK
		/*
		 * register jack devices for this module
		 * from codec->jack_list
		 */
		list_for_each_entry(jack, &codec->jack_list, list) {
			if ((jack == &module->headset_jack) ||
			    (jack == &module->button_jack))
				snd_device_register(codec->card->snd_card,
						    jack->jack);
		}
#endif
	}

	mutex_lock(&gbcodec->lock);
	list_add(&module->list, &gbcodec->module_list);
	mutex_unlock(&gbcodec->lock);

	if (codec->card->instantiated)
		ret = snd_soc_dapm_new_widgets(&codec->dapm);
	dev_dbg(codec->dev, "Registered %s module\n", module->name);

	up_write(&card->controls_rwsem);
	return ret;
}