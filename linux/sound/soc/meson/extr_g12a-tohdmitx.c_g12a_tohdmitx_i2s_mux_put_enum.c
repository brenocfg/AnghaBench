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
struct soc_enum {int dummy; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int CTRL0_I2S_BCLK_SEL ; 
 int CTRL0_I2S_DAT_SEL ; 
 int CTRL0_I2S_LRCLK_SEL ; 
 int FIELD_PREP (int,unsigned int) ; 
 int /*<<< orphan*/  TOHDMITX_CTRL0 ; 
 unsigned int g12a_tohdmitx_get_input_val (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_kcontrol_component (struct snd_kcontrol*) ; 
 struct snd_soc_dapm_context* snd_soc_dapm_kcontrol_dapm (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mux_update_power (struct snd_soc_dapm_context*,struct snd_kcontrol*,unsigned int,struct soc_enum*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int g12a_tohdmitx_i2s_mux_put_enum(struct snd_kcontrol *kcontrol,
					  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	struct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int mux = ucontrol->value.enumerated.item[0];
	unsigned int val = g12a_tohdmitx_get_input_val(component,
						       CTRL0_I2S_DAT_SEL);

	/* Force disconnect of the mux while updating */
	if (val != mux)
		snd_soc_dapm_mux_update_power(dapm, kcontrol, 0, NULL, NULL);

	snd_soc_component_update_bits(component, TOHDMITX_CTRL0,
				      CTRL0_I2S_DAT_SEL |
				      CTRL0_I2S_LRCLK_SEL |
				      CTRL0_I2S_BCLK_SEL,
				      FIELD_PREP(CTRL0_I2S_DAT_SEL, mux) |
				      FIELD_PREP(CTRL0_I2S_LRCLK_SEL, mux) |
				      FIELD_PREP(CTRL0_I2S_BCLK_SEL, mux));

	snd_soc_dapm_mux_update_power(dapm, kcontrol, mux, e, NULL);

	return 0;
}