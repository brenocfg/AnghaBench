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
struct sta32x_priv {int /*<<< orphan*/  coeff_lock; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {unsigned int* data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ STA32X_B1CF1 ; 
 scalar_t__ STA32X_CFADDR2 ; 
 scalar_t__ STA32X_CFUD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 struct sta32x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int sta32x_coefficient_get(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	int numcoef = kcontrol->private_value >> 16;
	int index = kcontrol->private_value & 0xffff;
	unsigned int cfud, val;
	int i, ret = 0;

	mutex_lock(&sta32x->coeff_lock);

	/* preserve reserved bits in STA32X_CFUD */
	regmap_read(sta32x->regmap, STA32X_CFUD, &cfud);
	cfud &= 0xf0;
	/*
	 * chip documentation does not say if the bits are self clearing,
	 * so do it explicitly
	 */
	regmap_write(sta32x->regmap, STA32X_CFUD, cfud);

	regmap_write(sta32x->regmap, STA32X_CFADDR2, index);
	if (numcoef == 1) {
		regmap_write(sta32x->regmap, STA32X_CFUD, cfud | 0x04);
	} else if (numcoef == 5) {
		regmap_write(sta32x->regmap, STA32X_CFUD, cfud | 0x08);
	} else {
		ret = -EINVAL;
		goto exit_unlock;
	}

	for (i = 0; i < 3 * numcoef; i++) {
		regmap_read(sta32x->regmap, STA32X_B1CF1 + i, &val);
		ucontrol->value.bytes.data[i] = val;
	}

exit_unlock:
	mutex_unlock(&sta32x->coeff_lock);

	return ret;
}