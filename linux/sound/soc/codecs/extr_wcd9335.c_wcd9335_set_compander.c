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
struct wcd9335_codec {int* comp_enabled; } ;
struct soc_mixer_control {int shift; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
#define  COMPANDER_1 131 
#define  COMPANDER_2 130 
#define  COMPANDER_5 129 
#define  COMPANDER_6 128 
 int WCD9335_HPH_GAIN_SRC_SEL_COMPANDER ; 
 int /*<<< orphan*/  WCD9335_HPH_GAIN_SRC_SEL_MASK ; 
 int WCD9335_HPH_GAIN_SRC_SEL_REGISTER ; 
 int /*<<< orphan*/  WCD9335_HPH_L_EN ; 
 int /*<<< orphan*/  WCD9335_HPH_R_EN ; 
 int /*<<< orphan*/  WCD9335_SE_LO_LO3_GAIN ; 
 int /*<<< orphan*/  WCD9335_SE_LO_LO4_GAIN ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int wcd9335_set_compander(struct snd_kcontrol *kc,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kc);
	struct wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	int comp = ((struct soc_mixer_control *) kc->private_value)->shift;
	int value = ucontrol->value.integer.value[0];
	int sel;

	wcd->comp_enabled[comp] = value;
	sel = value ? WCD9335_HPH_GAIN_SRC_SEL_COMPANDER :
		WCD9335_HPH_GAIN_SRC_SEL_REGISTER;

	/* Any specific register configuration for compander */
	switch (comp) {
	case COMPANDER_1:
		/* Set Gain Source Select based on compander enable/disable */
		snd_soc_component_update_bits(component, WCD9335_HPH_L_EN,
				      WCD9335_HPH_GAIN_SRC_SEL_MASK, sel);
		break;
	case COMPANDER_2:
		snd_soc_component_update_bits(component, WCD9335_HPH_R_EN,
				      WCD9335_HPH_GAIN_SRC_SEL_MASK, sel);
		break;
	case COMPANDER_5:
		snd_soc_component_update_bits(component, WCD9335_SE_LO_LO3_GAIN,
				      WCD9335_HPH_GAIN_SRC_SEL_MASK, sel);
		break;
	case COMPANDER_6:
		snd_soc_component_update_bits(component, WCD9335_SE_LO_LO4_GAIN,
				      WCD9335_HPH_GAIN_SRC_SEL_MASK, sel);
		break;
	default:
		break;
	};

	return 0;
}