#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct arizona* arizona; } ;
struct wm8998_priv {TYPE_1__ core; } ;
struct soc_enum {int reg; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_7__ {unsigned int* item; } ;
struct TYPE_8__ {TYPE_3__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;
struct TYPE_6__ {unsigned int* inmode; } ;
struct arizona {TYPE_2__ pdata; } ;

/* Variables and functions */
#define  ARIZONA_ADC_DIGITAL_VOLUME_2L 128 
 unsigned int ARIZONA_IN1L_CONTROL ; 
 int ARIZONA_IN1L_SRC_MASK ; 
 int ARIZONA_IN1L_SRC_SE_MASK ; 
 int ARIZONA_IN1L_SRC_SE_SHIFT ; 
 unsigned int ARIZONA_IN1L_SRC_SHIFT ; 
 int ARIZONA_IN1_MODE_MASK ; 
 int ARIZONA_IN1_MODE_SHIFT ; 
 unsigned int ARIZONA_IN2L_CONTROL ; 
 unsigned int ARIZONA_INMODE_DMIC ; 
 unsigned int ARIZONA_INMODE_SE ; 
 int EINVAL ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8998_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int,unsigned int) ; 
 struct snd_soc_component* snd_soc_dapm_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_dapm_mux_update_power (struct snd_soc_dapm_context*,struct snd_kcontrol*,unsigned int,struct soc_enum*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wm8998_inmux_put(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct wm8998_priv *wm8998 = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = wm8998->core.arizona;
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int mode_reg, mode_index;
	unsigned int mux, inmode, src_val, mode_val;

	mux = ucontrol->value.enumerated.item[0];
	if (mux > 1)
		return -EINVAL;

	switch (e->reg) {
	case ARIZONA_ADC_DIGITAL_VOLUME_2L:
		mode_reg = ARIZONA_IN2L_CONTROL;
		mode_index = 1 + (2 * mux);
		break;
	default:
		mode_reg = ARIZONA_IN1L_CONTROL;
		mode_index = (2 * mux);
		break;
	}

	inmode = arizona->pdata.inmode[mode_index];
	if (inmode & ARIZONA_INMODE_DMIC)
		mode_val = 1 << ARIZONA_IN1_MODE_SHIFT;
	else
		mode_val = 0;

	src_val = mux << ARIZONA_IN1L_SRC_SHIFT;
	if (inmode & ARIZONA_INMODE_SE)
		src_val |= 1 << ARIZONA_IN1L_SRC_SE_SHIFT;

	snd_soc_component_update_bits(component, mode_reg,
				      ARIZONA_IN1_MODE_MASK, mode_val);

	snd_soc_component_update_bits(component, e->reg,
				      ARIZONA_IN1L_SRC_MASK |
				      ARIZONA_IN1L_SRC_SE_MASK,
				      src_val);

	return snd_soc_dapm_mux_update_power(dapm, kcontrol,
					     ucontrol->value.enumerated.item[0],
					     e, NULL);
}