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
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; } ;
struct snd_soc_dapm_context {TYPE_1__* card; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dapm_mutex; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct snd_soc_dapm_widget*) ; 
 int PTR_ERR (struct snd_soc_dapm_widget*) ; 
 int /*<<< orphan*/  SND_SOC_DAPM_CLASS_INIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_soc_dapm_widget* snd_soc_dapm_new_control_unlocked (struct snd_soc_dapm_context*,struct snd_soc_dapm_widget const*) ; 

int snd_soc_dapm_new_controls(struct snd_soc_dapm_context *dapm,
	const struct snd_soc_dapm_widget *widget,
	int num)
{
	struct snd_soc_dapm_widget *w;
	int i;
	int ret = 0;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_INIT);
	for (i = 0; i < num; i++) {
		w = snd_soc_dapm_new_control_unlocked(dapm, widget);
		if (IS_ERR(w)) {
			ret = PTR_ERR(w);
			/* Do not nag about probe deferrals */
			if (ret == -EPROBE_DEFER)
				break;
			dev_err(dapm->dev,
				"ASoC: Failed to create DAPM control %s (%d)\n",
				widget->name, ret);
			break;
		}
		if (!w) {
			dev_err(dapm->dev,
				"ASoC: Failed to create DAPM control %s\n",
				widget->name);
			ret = -ENOMEM;
			break;
		}
		widget++;
	}
	mutex_unlock(&dapm->card->dapm_mutex);
	return ret;
}