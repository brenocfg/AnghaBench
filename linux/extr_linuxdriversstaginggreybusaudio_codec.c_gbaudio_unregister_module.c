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
struct gbaudio_module_info {int /*<<< orphan*/  name; int /*<<< orphan*/  num_dapm_widgets; scalar_t__ dapm_widgets; int /*<<< orphan*/  num_controls; scalar_t__ controls; int /*<<< orphan*/  num_dapm_routes; scalar_t__ dapm_routes; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; struct snd_soc_codec* codec; } ;
struct TYPE_3__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gbaudio_codec_cleanup (struct gbaudio_module_info*) ; 
 TYPE_2__* gbcodec ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dapm_del_routes (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_free_controls (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_remove_codec_controls (struct snd_soc_codec*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void gbaudio_unregister_module(struct gbaudio_module_info *module)
{
	struct snd_soc_codec *codec = gbcodec->codec;
	struct snd_card *card = codec->card->snd_card;
	struct snd_soc_jack *jack, *next_j;
	int mask;

	dev_dbg(codec->dev, "Unregister %s module\n", module->name);

	down_write(&card->controls_rwsem);
	mutex_lock(&gbcodec->lock);
	gbaudio_codec_cleanup(module);
	list_del(&module->list);
	dev_dbg(codec->dev, "Process Unregister %s module\n", module->name);
	mutex_unlock(&gbcodec->lock);

#ifdef CONFIG_SND_JACK
	/* free jack devices for this module from codec->jack_list */
	list_for_each_entry_safe(jack, next_j, &codec->jack_list, list) {
		if (jack == &module->headset_jack)
			mask = GBCODEC_JACK_MASK;
		else if (jack == &module->button_jack)
			mask = GBCODEC_JACK_BUTTON_MASK;
		else
			mask = 0;
		if (mask) {
			dev_dbg(module->dev, "Report %s removal\n",
				jack->jack->id);
			snd_soc_jack_report(jack, 0, mask);
			snd_device_free(codec->card->snd_card, jack->jack);
			list_del(&jack->list);
		}
	}
#endif

	if (module->dapm_routes) {
		dev_dbg(codec->dev, "Removing %d routes\n",
			module->num_dapm_routes);
		snd_soc_dapm_del_routes(&codec->dapm, module->dapm_routes,
					module->num_dapm_routes);
	}
	if (module->controls) {
		dev_dbg(codec->dev, "Removing %d controls\n",
			module->num_controls);
		snd_soc_remove_codec_controls(codec, module->controls,
					      module->num_controls);
	}
	if (module->dapm_widgets) {
		dev_dbg(codec->dev, "Removing %d widgets\n",
			module->num_dapm_widgets);
		snd_soc_dapm_free_controls(&codec->dapm, module->dapm_widgets,
					   module->num_dapm_widgets);
	}

	dev_dbg(codec->dev, "Unregistered %s module\n", module->name);

	up_write(&card->controls_rwsem);
}