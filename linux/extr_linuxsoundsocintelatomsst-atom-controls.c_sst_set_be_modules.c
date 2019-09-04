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
struct sst_data {int dummy; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct sst_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int sst_send_pipe_module_params (struct snd_soc_dapm_widget*,struct snd_kcontrol*) ; 
 int sst_send_slot_map (struct sst_data*) ; 

__attribute__((used)) static int sst_set_be_modules(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *k, int event)
{
	int ret = 0;
	struct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	struct sst_data *drv = snd_soc_component_get_drvdata(c);

	dev_dbg(c->dev, "Enter: widget=%s\n", w->name);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		ret = sst_send_slot_map(drv);
		if (ret)
			return ret;
		ret = sst_send_pipe_module_params(w, k);
	}
	return ret;
}