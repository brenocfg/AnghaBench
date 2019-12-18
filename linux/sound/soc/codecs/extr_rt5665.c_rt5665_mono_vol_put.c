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
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5665_MONO_NG2_CTRL_1 ; 
 int RT5665_NG2_DIS ; 
 int RT5665_NG2_EN ; 
 int /*<<< orphan*/  RT5665_NG2_EN_MASK ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_put_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int rt5665_mono_vol_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	int ret = snd_soc_put_volsw(kcontrol, ucontrol);

	if (snd_soc_component_read32(component, RT5665_MONO_NG2_CTRL_1) & RT5665_NG2_EN) {
		snd_soc_component_update_bits(component, RT5665_MONO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_DIS);
		snd_soc_component_update_bits(component, RT5665_MONO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_EN);
	}

	return ret;
}