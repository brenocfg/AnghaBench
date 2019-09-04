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
typedef  int /*<<< orphan*/  u16 ;
struct soc_mixer_control {unsigned int reg; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct da7218_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int regmap_raw_read (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int) ; 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int da7218_tonegen_freq_get(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	struct soc_mixer_control *mixer_ctrl =
		(struct soc_mixer_control *) kcontrol->private_value;
	unsigned int reg = mixer_ctrl->reg;
	u16 val;
	int ret;

	/*
	 * Frequency value spans two 8-bit registers, lower then upper byte.
	 * Therefore we need to convert to host endianness here.
	 */
	ret = regmap_raw_read(da7218->regmap, reg, &val, 2);
	if (ret)
		return ret;

	ucontrol->value.integer.value[0] = le16_to_cpu(val);

	return 0;
}