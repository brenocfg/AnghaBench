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
struct soc_enum {unsigned int shift_l; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct cpcap_audio {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_REG_RXCOA ; 
 int /*<<< orphan*/  CPCAP_REG_RXEPOA ; 
 int /*<<< orphan*/  CPCAP_REG_RXSDOA ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct cpcap_audio* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int cpcap_output_mux_get_enum(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	struct cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int shift = e->shift_l;
	int reg_voice, reg_hifi, reg_ext, status;
	int err;

	err = regmap_read(cpcap->regmap, CPCAP_REG_RXCOA, &reg_voice);
	if (err)
		return err;
	err = regmap_read(cpcap->regmap, CPCAP_REG_RXSDOA, &reg_hifi);
	if (err)
		return err;
	err = regmap_read(cpcap->regmap, CPCAP_REG_RXEPOA, &reg_ext);
	if (err)
		return err;

	reg_voice = (reg_voice >> shift) & 1;
	reg_hifi = (reg_hifi >> shift) & 1;
	reg_ext = (reg_ext >> shift) & 1;
	status = reg_ext << 2 | reg_hifi << 1 | reg_voice;

	switch (status) {
	case 0x04:
		ucontrol->value.enumerated.item[0] = 3;
		break;
	case 0x02:
		ucontrol->value.enumerated.item[0] = 2;
		break;
	case 0x01:
		ucontrol->value.enumerated.item[0] = 1;
		break;
	default:
		ucontrol->value.enumerated.item[0] = 0;
		break;
	}

	return 0;
}