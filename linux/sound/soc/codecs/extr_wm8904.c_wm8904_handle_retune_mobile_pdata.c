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
struct TYPE_4__ {size_t items; char const** texts; } ;
struct wm8904_priv {int num_retune_mobile_texts; char const** retune_mobile_texts; TYPE_2__ retune_mobile_enum; struct wm8904_pdata* pdata; } ;
struct wm8904_pdata {int num_retune_mobile_cfgs; TYPE_1__* retune_mobile_cfgs; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol_new {int dummy; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_kcontrol_new SOC_ENUM_EXT (char*,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 char** krealloc (char const**,int,int /*<<< orphan*/ ) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,struct snd_kcontrol_new*,int) ; 
 struct wm8904_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  wm8904_get_retune_mobile_enum ; 
 int /*<<< orphan*/  wm8904_put_retune_mobile_enum ; 

__attribute__((used)) static void wm8904_handle_retune_mobile_pdata(struct snd_soc_component *component)
{
	struct wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);
	struct wm8904_pdata *pdata = wm8904->pdata;
	struct snd_kcontrol_new control =
		SOC_ENUM_EXT("EQ Mode",
			     wm8904->retune_mobile_enum,
			     wm8904_get_retune_mobile_enum,
			     wm8904_put_retune_mobile_enum);
	int ret, i, j;
	const char **t;

	/* We need an array of texts for the enum API but the number
	 * of texts is likely to be less than the number of
	 * configurations due to the sample rate dependency of the
	 * configurations. */
	wm8904->num_retune_mobile_texts = 0;
	wm8904->retune_mobile_texts = NULL;
	for (i = 0; i < pdata->num_retune_mobile_cfgs; i++) {
		for (j = 0; j < wm8904->num_retune_mobile_texts; j++) {
			if (strcmp(pdata->retune_mobile_cfgs[i].name,
				   wm8904->retune_mobile_texts[j]) == 0)
				break;
		}

		if (j != wm8904->num_retune_mobile_texts)
			continue;

		/* Expand the array... */
		t = krealloc(wm8904->retune_mobile_texts,
			     sizeof(char *) * 
			     (wm8904->num_retune_mobile_texts + 1),
			     GFP_KERNEL);
		if (t == NULL)
			continue;

		/* ...store the new entry... */
		t[wm8904->num_retune_mobile_texts] = 
			pdata->retune_mobile_cfgs[i].name;

		/* ...and remember the new version. */
		wm8904->num_retune_mobile_texts++;
		wm8904->retune_mobile_texts = t;
	}

	dev_dbg(component->dev, "Allocated %d unique ReTune Mobile names\n",
		wm8904->num_retune_mobile_texts);

	wm8904->retune_mobile_enum.items = wm8904->num_retune_mobile_texts;
	wm8904->retune_mobile_enum.texts = wm8904->retune_mobile_texts;

	ret = snd_soc_add_component_controls(component, &control, 1);
	if (ret != 0)
		dev_err(component->dev,
			"Failed to add ReTune Mobile control: %d\n", ret);
}