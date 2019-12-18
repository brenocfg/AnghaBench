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
struct soc_enum {unsigned int shift_l; unsigned int mask; int reg; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {unsigned int* item; } ;
struct TYPE_6__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct regmap {int dummy; } ;
struct madera_priv {struct madera* madera; } ;
struct TYPE_7__ {unsigned int** inmode; } ;
struct TYPE_8__ {TYPE_3__ codec; } ;
struct madera {int /*<<< orphan*/  dev; TYPE_4__ pdata; struct regmap* regmap; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MADERA_ADC_DIGITAL_VOLUME_1L 131 
#define  MADERA_ADC_DIGITAL_VOLUME_1R 130 
#define  MADERA_ADC_DIGITAL_VOLUME_2L 129 
#define  MADERA_ADC_DIGITAL_VOLUME_2R 128 
 unsigned int MADERA_IN1L_SRC_SE_MASK ; 
 int MADERA_IN1L_SRC_SE_SHIFT ; 
 unsigned int MADERA_INMODE_SE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int,unsigned int,unsigned int,unsigned int) ; 
 int regmap_update_bits_check (struct regmap*,int,unsigned int,unsigned int,int*) ; 
 struct madera_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_kcontrol_component (struct snd_kcontrol*) ; 
 struct snd_soc_dapm_context* snd_soc_dapm_kcontrol_dapm (struct snd_kcontrol*) ; 
 int snd_soc_dapm_mux_update_power (struct snd_soc_dapm_context*,struct snd_kcontrol*,unsigned int,struct soc_enum*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int madera_inmux_put(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	struct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	struct madera_priv *priv = snd_soc_component_get_drvdata(component);
	struct madera *madera = priv->madera;
	struct regmap *regmap = madera->regmap;
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int mux, val, mask;
	unsigned int inmode;
	bool changed;
	int ret;

	mux = ucontrol->value.enumerated.item[0];
	if (mux > 1)
		return -EINVAL;

	val = mux << e->shift_l;
	mask = (e->mask << e->shift_l) | MADERA_IN1L_SRC_SE_MASK;

	switch (e->reg) {
	case MADERA_ADC_DIGITAL_VOLUME_1L:
		inmode = madera->pdata.codec.inmode[0][2 * mux];
		break;
	case MADERA_ADC_DIGITAL_VOLUME_1R:
		inmode = madera->pdata.codec.inmode[0][1 + (2 * mux)];
		break;
	case MADERA_ADC_DIGITAL_VOLUME_2L:
		inmode = madera->pdata.codec.inmode[1][2 * mux];
		break;
	case MADERA_ADC_DIGITAL_VOLUME_2R:
		inmode = madera->pdata.codec.inmode[1][1 + (2 * mux)];
		break;
	default:
		return -EINVAL;
	}

	if (inmode & MADERA_INMODE_SE)
		val |= 1 << MADERA_IN1L_SRC_SE_SHIFT;

	dev_dbg(madera->dev, "mux=%u reg=0x%x inmode=0x%x mask=0x%x val=0x%x\n",
		mux, e->reg, inmode, mask, val);

	ret = regmap_update_bits_check(regmap, e->reg, mask, val, &changed);
	if (ret < 0)
		return ret;

	if (changed)
		return snd_soc_dapm_mux_update_power(dapm, kcontrol,
						     mux, e, NULL);
	else
		return 0;
}