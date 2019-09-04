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
struct snd_soc_dapm_widget_list {unsigned int num_widgets; struct snd_soc_dapm_widget** widgets; } ;
struct snd_soc_dapm_widget {int (* event ) (struct snd_soc_dapm_widget*,int /*<<< orphan*/ ,int) ;int event_flags; int /*<<< orphan*/  name; TYPE_1__* dapm; } ;
struct snd_soc_dapm_update {int /*<<< orphan*/  kcontrol; int /*<<< orphan*/  val2; int /*<<< orphan*/  mask2; int /*<<< orphan*/  reg2; scalar_t__ has_second_set; int /*<<< orphan*/  val; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct snd_soc_card {struct snd_soc_dapm_update* update; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SND_SOC_DAPM_POST_REG ; 
 int SND_SOC_DAPM_PRE_REG ; 
 struct snd_soc_dapm_widget_list* dapm_kcontrol_get_wlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dapm_kcontrol_is_powered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int soc_dapm_update_bits (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct snd_soc_dapm_widget*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct snd_soc_dapm_widget*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dapm_widget_update(struct snd_soc_card *card)
{
	struct snd_soc_dapm_update *update = card->update;
	struct snd_soc_dapm_widget_list *wlist;
	struct snd_soc_dapm_widget *w = NULL;
	unsigned int wi;
	int ret;

	if (!update || !dapm_kcontrol_is_powered(update->kcontrol))
		return;

	wlist = dapm_kcontrol_get_wlist(update->kcontrol);

	for (wi = 0; wi < wlist->num_widgets; wi++) {
		w = wlist->widgets[wi];

		if (w->event && (w->event_flags & SND_SOC_DAPM_PRE_REG)) {
			ret = w->event(w, update->kcontrol, SND_SOC_DAPM_PRE_REG);
			if (ret != 0)
				dev_err(w->dapm->dev, "ASoC: %s DAPM pre-event failed: %d\n",
					   w->name, ret);
		}
	}

	if (!w)
		return;

	ret = soc_dapm_update_bits(w->dapm, update->reg, update->mask,
		update->val);
	if (ret < 0)
		dev_err(w->dapm->dev, "ASoC: %s DAPM update failed: %d\n",
			w->name, ret);

	if (update->has_second_set) {
		ret = soc_dapm_update_bits(w->dapm, update->reg2,
					   update->mask2, update->val2);
		if (ret < 0)
			dev_err(w->dapm->dev,
				"ASoC: %s DAPM update failed: %d\n",
				w->name, ret);
	}

	for (wi = 0; wi < wlist->num_widgets; wi++) {
		w = wlist->widgets[wi];

		if (w->event && (w->event_flags & SND_SOC_DAPM_POST_REG)) {
			ret = w->event(w, update->kcontrol, SND_SOC_DAPM_POST_REG);
			if (ret != 0)
				dev_err(w->dapm->dev, "ASoC: %s DAPM post-event failed: %d\n",
					   w->name, ret);
		}
	}
}