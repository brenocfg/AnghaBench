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
struct wm8994_priv {int mbc_cfg; struct wm8994* wm8994; } ;
struct TYPE_4__ {int num_mbc_cfgs; } ;
struct wm8994 {TYPE_1__ pdata; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {int* item; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int WM8958_DSP2CLK_ENA ; 
 int /*<<< orphan*/  WM8994_CLOCKING_1 ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int wm8958_put_mbc_enum(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	int value = ucontrol->value.enumerated.item[0];
	int reg;

	/* Don't allow on the fly reconfiguration */
	reg = snd_soc_component_read32(component, WM8994_CLOCKING_1);
	if (reg < 0 || reg & WM8958_DSP2CLK_ENA)
		return -EBUSY;

	if (value >= control->pdata.num_mbc_cfgs)
		return -EINVAL;

	wm8994->mbc_cfg = value;

	return 0;
}