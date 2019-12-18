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
struct TYPE_4__ {int items; int /*<<< orphan*/ * texts; } ;
struct wm8904_priv {int /*<<< orphan*/ * drc_texts; TYPE_2__ drc_enum; struct wm8904_pdata* pdata; } ;
struct wm8904_pdata {int num_drc_cfgs; int num_retune_mobile_cfgs; TYPE_1__* drc_cfgs; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol_new {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct snd_kcontrol_new*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_kcontrol_new SOC_ENUM_EXT (char*,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,struct snd_kcontrol_new*,int) ; 
 struct wm8904_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_kcontrol_new* wm8904_eq_controls ; 
 int /*<<< orphan*/  wm8904_get_drc_enum ; 
 int /*<<< orphan*/  wm8904_handle_retune_mobile_pdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8904_put_drc_enum ; 
 int /*<<< orphan*/  wm8904_set_drc (struct snd_soc_component*) ; 

__attribute__((used)) static void wm8904_handle_pdata(struct snd_soc_component *component)
{
	struct wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	struct wm8904_pdata *pdata = wm8904->pdata;
	int ret, i;

	if (!pdata) {
		snd_soc_add_component_controls(component, wm8904_eq_controls,
				     ARRAY_SIZE(wm8904_eq_controls));
		return;
	}

	dev_dbg(component->dev, "%d DRC configurations\n", pdata->num_drc_cfgs);

	if (pdata->num_drc_cfgs) {
		struct snd_kcontrol_new control =
			SOC_ENUM_EXT("DRC Mode", wm8904->drc_enum,
				     wm8904_get_drc_enum, wm8904_put_drc_enum);

		/* We need an array of texts for the enum API */
		wm8904->drc_texts = kmalloc_array(pdata->num_drc_cfgs,
						  sizeof(char *),
						  GFP_KERNEL);
		if (!wm8904->drc_texts)
			return;

		for (i = 0; i < pdata->num_drc_cfgs; i++)
			wm8904->drc_texts[i] = pdata->drc_cfgs[i].name;

		wm8904->drc_enum.items = pdata->num_drc_cfgs;
		wm8904->drc_enum.texts = wm8904->drc_texts;

		ret = snd_soc_add_component_controls(component, &control, 1);
		if (ret != 0)
			dev_err(component->dev,
				"Failed to add DRC mode control: %d\n", ret);

		wm8904_set_drc(component);
	}

	dev_dbg(component->dev, "%d ReTune Mobile configurations\n",
		pdata->num_retune_mobile_cfgs);

	if (pdata->num_retune_mobile_cfgs)
		wm8904_handle_retune_mobile_pdata(component);
	else
		snd_soc_add_component_controls(component, wm8904_eq_controls,
				     ARRAY_SIZE(wm8904_eq_controls));
}