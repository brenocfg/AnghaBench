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
struct snd_soc_dapm_widget {int connected; scalar_t__ force; } ;
struct snd_soc_dapm_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dapm_assert_locked (struct snd_soc_dapm_context*) ; 
 struct snd_soc_dapm_widget* dapm_find_widget (struct snd_soc_dapm_context*,char const*,int) ; 
 int /*<<< orphan*/  dapm_mark_dirty (struct snd_soc_dapm_widget*,char*) ; 
 int /*<<< orphan*/  dapm_widget_invalidate_input_paths (struct snd_soc_dapm_widget*) ; 
 int /*<<< orphan*/  dapm_widget_invalidate_output_paths (struct snd_soc_dapm_widget*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int snd_soc_dapm_set_pin(struct snd_soc_dapm_context *dapm,
				const char *pin, int status)
{
	struct snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, true);

	dapm_assert_locked(dapm);

	if (!w) {
		dev_err(dapm->dev, "ASoC: DAPM unknown pin %s\n", pin);
		return -EINVAL;
	}

	if (w->connected != status) {
		dapm_mark_dirty(w, "pin configuration");
		dapm_widget_invalidate_input_paths(w);
		dapm_widget_invalidate_output_paths(w);
	}

	w->connected = status;
	if (status == 0)
		w->force = 0;

	return 0;
}