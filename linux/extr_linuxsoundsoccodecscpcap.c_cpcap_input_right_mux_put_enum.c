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
struct cpcap_audio {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPCAP_BIT_EMU_MIC_MUX ; 
 int /*<<< orphan*/  CPCAP_BIT_HS_MIC_MUX ; 
 int /*<<< orphan*/  CPCAP_BIT_MIC1_MUX ; 
 int /*<<< orphan*/  CPCAP_BIT_RX_R_ENCODE ; 
 int /*<<< orphan*/  CPCAP_REG_TXI ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct cpcap_audio* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_kcontrol_component (struct snd_kcontrol*) ; 
 struct snd_soc_dapm_context* snd_soc_dapm_kcontrol_dapm (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mux_update_power (struct snd_soc_dapm_context*,struct snd_kcontrol*,unsigned int,struct soc_enum*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpcap_input_right_mux_put_enum(struct snd_kcontrol *kcontrol,
					  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	struct cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int muxval = ucontrol->value.enumerated.item[0];
	int regval = 0, mask;
	int err;

	mask = 0;
	mask |= BIT(CPCAP_BIT_MIC1_MUX);
	mask |= BIT(CPCAP_BIT_HS_MIC_MUX);
	mask |= BIT(CPCAP_BIT_EMU_MIC_MUX);
	mask |= BIT(CPCAP_BIT_RX_R_ENCODE);

	switch (muxval) {
	case 1:
		regval = BIT(CPCAP_BIT_MIC1_MUX);
		break;
	case 2:
		regval = BIT(CPCAP_BIT_HS_MIC_MUX);
		break;
	case 3:
		regval = BIT(CPCAP_BIT_EMU_MIC_MUX);
		break;
	case 4:
		regval = BIT(CPCAP_BIT_RX_R_ENCODE);
		break;
	default:
		break;
	}

	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_TXI,
				 mask, regval);
	if (err)
		return err;

	snd_soc_dapm_mux_update_power(dapm, kcontrol, muxval, e, NULL);

	return 0;
}