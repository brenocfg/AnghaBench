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
struct snd_soc_component {TYPE_1__* card; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {unsigned int* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct rt1011_priv {unsigned int r0_reg; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  instantiated; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned int,unsigned int,unsigned int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt1011_r0_load (struct rt1011_priv*) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 scalar_t__ snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct rt1011_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt1011_r0_load_mode_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct rt1011_priv *rt1011 = snd_soc_component_get_drvdata(component);
	struct device *dev;
	unsigned int r0_integer, r0_factor, format;

	if (ucontrol->value.integer.value[0] == rt1011->r0_reg)
		return 0;

	if (!component->card->instantiated)
		return 0;

	if (ucontrol->value.integer.value[0] == 0)
		return -EINVAL;

	dev = regmap_get_device(rt1011->regmap);
	if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
		rt1011->r0_reg = ucontrol->value.integer.value[0];

		format = 2147483648U; /* 2^24 * 128 */
		r0_integer = format / rt1011->r0_reg / 128;
		r0_factor = ((format / rt1011->r0_reg * 100) / 128)
						- (r0_integer * 100);
		dev_info(dev,	"New r0 resistance about %d.%02d ohm, reg=0x%X\n",
			r0_integer, r0_factor, rt1011->r0_reg);

		if (rt1011->r0_reg)
			rt1011_r0_load(rt1011);
	}

	return 0;
}