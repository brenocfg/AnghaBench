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
struct snd_soc_dapm_widget {int connected; int force; TYPE_1__* dapm; } ;
struct snd_soc_dapm_context {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct snd_soc_dapm_widget* dapm_find_widget (struct snd_soc_dapm_context*,char const*,int) ; 
 int /*<<< orphan*/  dapm_mark_dirty (struct snd_soc_dapm_widget*,char*) ; 
 int /*<<< orphan*/  dapm_widget_invalidate_input_paths (struct snd_soc_dapm_widget*) ; 
 int /*<<< orphan*/  dapm_widget_invalidate_output_paths (struct snd_soc_dapm_widget*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 

int snd_soc_dapm_force_enable_pin_unlocked(struct snd_soc_dapm_context *dapm,
					 const char *pin)
{
	struct snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, true);

	if (!w) {
		dev_err(dapm->dev, "ASoC: unknown pin %s\n", pin);
		return -EINVAL;
	}

	dev_dbg(w->dapm->dev, "ASoC: force enable pin %s\n", pin);
	if (!w->connected) {
		/*
		 * w->force does not affect the number of input or output paths,
		 * so we only have to recheck if w->connected is changed
		 */
		dapm_widget_invalidate_input_paths(w);
		dapm_widget_invalidate_output_paths(w);
		w->connected = 1;
	}
	w->force = 1;
	dapm_mark_dirty(w, "force enable");

	return 0;
}