#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct snd_soc_component* component; } ;
struct TYPE_12__ {int items; int /*<<< orphan*/ * texts; } ;
struct wm8994_priv {int dsp_active; TYPE_5__ hubs; int /*<<< orphan*/ * enh_eq_texts; TYPE_6__ enh_eq_enum; int /*<<< orphan*/ * vss_hpf_texts; TYPE_6__ vss_hpf_enum; int /*<<< orphan*/ * vss_texts; TYPE_6__ vss_enum; int /*<<< orphan*/ * mbc_texts; TYPE_6__ mbc_enum; struct wm8994* wm8994; } ;
struct wm8994_pdata {int num_mbc_cfgs; int num_vss_cfgs; int num_vss_hpf_cfgs; int num_enh_eq_cfgs; TYPE_4__* enh_eq_cfgs; TYPE_3__* vss_hpf_cfgs; TYPE_2__* vss_cfgs; TYPE_1__* mbc_cfgs; } ;
struct wm8994 {struct wm8994_pdata pdata; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol_new {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct snd_kcontrol_new*) ; 
 int /*<<< orphan*/  FW_ACTION_HOTPLUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_kcontrol_new SOC_ENUM_EXT (char*,TYPE_6__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_firmware_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,struct snd_kcontrol_new*,int) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8958_enh_eq_loaded ; 
 struct snd_kcontrol_new* wm8958_enh_eq_snd_controls ; 
 int /*<<< orphan*/  wm8958_get_enh_eq_enum ; 
 int /*<<< orphan*/  wm8958_get_mbc_enum ; 
 int /*<<< orphan*/  wm8958_get_vss_enum ; 
 int /*<<< orphan*/  wm8958_get_vss_hpf_enum ; 
 int /*<<< orphan*/  wm8958_mbc_loaded ; 
 struct snd_kcontrol_new* wm8958_mbc_snd_controls ; 
 int /*<<< orphan*/  wm8958_mbc_vss_loaded ; 
 int /*<<< orphan*/  wm8958_put_enh_eq_enum ; 
 int /*<<< orphan*/  wm8958_put_mbc_enum ; 
 int /*<<< orphan*/  wm8958_put_vss_enum ; 
 int /*<<< orphan*/  wm8958_put_vss_hpf_enum ; 
 struct snd_kcontrol_new* wm8958_vss_snd_controls ; 

void wm8958_dsp2_init(struct snd_soc_component *component)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	struct wm8994_pdata *pdata = &control->pdata;
	int ret, i;

	wm8994->dsp_active = -1;

	snd_soc_add_component_controls(component, wm8958_mbc_snd_controls,
			     ARRAY_SIZE(wm8958_mbc_snd_controls));
	snd_soc_add_component_controls(component, wm8958_vss_snd_controls,
			     ARRAY_SIZE(wm8958_vss_snd_controls));
	snd_soc_add_component_controls(component, wm8958_enh_eq_snd_controls,
			     ARRAY_SIZE(wm8958_enh_eq_snd_controls));


	/* We don't *require* firmware and don't want to delay boot */
	request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
				"wm8958_mbc.wfw", component->dev, GFP_KERNEL,
				component, wm8958_mbc_loaded);
	request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
				"wm8958_mbc_vss.wfw", component->dev, GFP_KERNEL,
				component, wm8958_mbc_vss_loaded);
	request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
				"wm8958_enh_eq.wfw", component->dev, GFP_KERNEL,
				component, wm8958_enh_eq_loaded);

	if (pdata->num_mbc_cfgs) {
		struct snd_kcontrol_new control[] = {
			SOC_ENUM_EXT("MBC Mode", wm8994->mbc_enum,
				     wm8958_get_mbc_enum, wm8958_put_mbc_enum),
		};

		/* We need an array of texts for the enum API */
		wm8994->mbc_texts = kmalloc_array(pdata->num_mbc_cfgs,
						  sizeof(char *),
						  GFP_KERNEL);
		if (!wm8994->mbc_texts)
			return;

		for (i = 0; i < pdata->num_mbc_cfgs; i++)
			wm8994->mbc_texts[i] = pdata->mbc_cfgs[i].name;

		wm8994->mbc_enum.items = pdata->num_mbc_cfgs;
		wm8994->mbc_enum.texts = wm8994->mbc_texts;

		ret = snd_soc_add_component_controls(wm8994->hubs.component,
						 control, 1);
		if (ret != 0)
			dev_err(wm8994->hubs.component->dev,
				"Failed to add MBC mode controls: %d\n", ret);
	}

	if (pdata->num_vss_cfgs) {
		struct snd_kcontrol_new control[] = {
			SOC_ENUM_EXT("VSS Mode", wm8994->vss_enum,
				     wm8958_get_vss_enum, wm8958_put_vss_enum),
		};

		/* We need an array of texts for the enum API */
		wm8994->vss_texts = kmalloc_array(pdata->num_vss_cfgs,
						  sizeof(char *),
						  GFP_KERNEL);
		if (!wm8994->vss_texts)
			return;

		for (i = 0; i < pdata->num_vss_cfgs; i++)
			wm8994->vss_texts[i] = pdata->vss_cfgs[i].name;

		wm8994->vss_enum.items = pdata->num_vss_cfgs;
		wm8994->vss_enum.texts = wm8994->vss_texts;

		ret = snd_soc_add_component_controls(wm8994->hubs.component,
						 control, 1);
		if (ret != 0)
			dev_err(wm8994->hubs.component->dev,
				"Failed to add VSS mode controls: %d\n", ret);
	}

	if (pdata->num_vss_hpf_cfgs) {
		struct snd_kcontrol_new control[] = {
			SOC_ENUM_EXT("VSS HPF Mode", wm8994->vss_hpf_enum,
				     wm8958_get_vss_hpf_enum,
				     wm8958_put_vss_hpf_enum),
		};

		/* We need an array of texts for the enum API */
		wm8994->vss_hpf_texts = kmalloc_array(pdata->num_vss_hpf_cfgs,
						      sizeof(char *),
						      GFP_KERNEL);
		if (!wm8994->vss_hpf_texts)
			return;

		for (i = 0; i < pdata->num_vss_hpf_cfgs; i++)
			wm8994->vss_hpf_texts[i] = pdata->vss_hpf_cfgs[i].name;

		wm8994->vss_hpf_enum.items = pdata->num_vss_hpf_cfgs;
		wm8994->vss_hpf_enum.texts = wm8994->vss_hpf_texts;

		ret = snd_soc_add_component_controls(wm8994->hubs.component,
						 control, 1);
		if (ret != 0)
			dev_err(wm8994->hubs.component->dev,
				"Failed to add VSS HPFmode controls: %d\n",
				ret);
	}

	if (pdata->num_enh_eq_cfgs) {
		struct snd_kcontrol_new control[] = {
			SOC_ENUM_EXT("Enhanced EQ Mode", wm8994->enh_eq_enum,
				     wm8958_get_enh_eq_enum,
				     wm8958_put_enh_eq_enum),
		};

		/* We need an array of texts for the enum API */
		wm8994->enh_eq_texts = kmalloc_array(pdata->num_enh_eq_cfgs,
						     sizeof(char *),
						     GFP_KERNEL);
		if (!wm8994->enh_eq_texts)
			return;

		for (i = 0; i < pdata->num_enh_eq_cfgs; i++)
			wm8994->enh_eq_texts[i] = pdata->enh_eq_cfgs[i].name;

		wm8994->enh_eq_enum.items = pdata->num_enh_eq_cfgs;
		wm8994->enh_eq_enum.texts = wm8994->enh_eq_texts;

		ret = snd_soc_add_component_controls(wm8994->hubs.component,
						 control, 1);
		if (ret != 0)
			dev_err(wm8994->hubs.component->dev,
				"Failed to add enhanced EQ controls: %d\n",
				ret);
	}
}