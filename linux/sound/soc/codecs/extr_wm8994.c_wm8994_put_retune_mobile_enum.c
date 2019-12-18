#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wm8994_priv {int* retune_mobile_cfg; struct wm8994* wm8994; } ;
struct wm8994_pdata {int num_retune_mobile_cfgs; } ;
struct wm8994 {struct wm8994_pdata pdata; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct TYPE_5__ {int* item; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int wm8994_get_retune_mobile_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8994_set_retune_mobile (struct snd_soc_component*,int) ; 

__attribute__((used)) static int wm8994_put_retune_mobile_enum(struct snd_kcontrol *kcontrol,
					 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	struct wm8994_pdata *pdata = &control->pdata;
	int block = wm8994_get_retune_mobile_block(kcontrol->id.name);
	int value = ucontrol->value.enumerated.item[0];

	if (block < 0)
		return block;

	if (value >= pdata->num_retune_mobile_cfgs)
		return -EINVAL;

	wm8994->retune_mobile_cfg[block] = value;

	wm8994_set_retune_mobile(component, block);

	return 0;
}