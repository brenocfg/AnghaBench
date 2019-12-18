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
struct sta32x_priv {int* coef_shadow; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ STA32X_B1CF1 ; 
 scalar_t__ STA32X_CFADDR2 ; 
 scalar_t__ STA32X_CFUD ; 
 int STA32X_COEF_COUNT ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 struct sta32x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int sta32x_coefficient_put(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	int numcoef = kcontrol->private_value >> 16;
	int index = kcontrol->private_value & 0xffff;
	unsigned int cfud;
	int i;

	/* preserve reserved bits in STA32X_CFUD */
	regmap_read(sta32x->regmap, STA32X_CFUD, &cfud);
	cfud &= 0xf0;
	/*
	 * chip documentation does not say if the bits are self clearing,
	 * so do it explicitly
	 */
	regmap_write(sta32x->regmap, STA32X_CFUD, cfud);

	regmap_write(sta32x->regmap, STA32X_CFADDR2, index);
	for (i = 0; i < numcoef && (index + i < STA32X_COEF_COUNT); i++)
		sta32x->coef_shadow[index + i] =
			  (ucontrol->value.bytes.data[3 * i] << 16)
			| (ucontrol->value.bytes.data[3 * i + 1] << 8)
			| (ucontrol->value.bytes.data[3 * i + 2]);
	for (i = 0; i < 3 * numcoef; i++)
		regmap_write(sta32x->regmap, STA32X_B1CF1 + i,
			     ucontrol->value.bytes.data[i]);
	if (numcoef == 1)
		regmap_write(sta32x->regmap, STA32X_CFUD, cfud | 0x01);
	else if (numcoef == 5)
		regmap_write(sta32x->regmap, STA32X_CFUD, cfud | 0x02);
	else
		return -EINVAL;

	return 0;
}