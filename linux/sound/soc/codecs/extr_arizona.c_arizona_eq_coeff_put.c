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
struct soc_bytes {int num_regs; int /*<<< orphan*/  base; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_2__ bytes; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct arizona {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 unsigned int ARIZONA_EQ1_B1_MODE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ arizona_eq_filter_unstable (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int,int) ; 
 int regmap_get_val_bytes (int /*<<< orphan*/ ) ; 
 int regmap_raw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

int arizona_eq_coeff_put(struct snd_kcontrol *kcontrol,
			 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct arizona *arizona = dev_get_drvdata(component->dev->parent);
	struct soc_bytes *params = (void *)kcontrol->private_value;
	unsigned int val;
	__be16 *data;
	int len;
	int ret;

	len = params->num_regs * regmap_get_val_bytes(arizona->regmap);

	data = kmemdup(ucontrol->value.bytes.data, len, GFP_KERNEL | GFP_DMA);
	if (!data)
		return -ENOMEM;

	data[0] &= cpu_to_be16(ARIZONA_EQ1_B1_MODE);

	if (arizona_eq_filter_unstable(!!data[0], data[1], data[2]) ||
	    arizona_eq_filter_unstable(true, data[4], data[5]) ||
	    arizona_eq_filter_unstable(true, data[8], data[9]) ||
	    arizona_eq_filter_unstable(true, data[12], data[13]) ||
	    arizona_eq_filter_unstable(false, data[16], data[17])) {
		dev_err(arizona->dev, "Rejecting unstable EQ coefficients\n");
		ret = -EINVAL;
		goto out;
	}

	ret = regmap_read(arizona->regmap, params->base, &val);
	if (ret != 0)
		goto out;

	val &= ~ARIZONA_EQ1_B1_MODE;
	data[0] |= cpu_to_be16(val);

	ret = regmap_raw_write(arizona->regmap, params->base, data, len);

out:
	kfree(data);
	return ret;
}