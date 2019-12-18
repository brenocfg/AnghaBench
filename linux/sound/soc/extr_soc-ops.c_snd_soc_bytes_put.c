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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct soc_bytes {int num_regs; int mask; int /*<<< orphan*/  base; } ;
struct snd_soc_component {int val_bytes; int /*<<< orphan*/  regmap; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int /*<<< orphan*/ ,int,int) ; 
 int regmap_parse_val (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int regmap_raw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 

int snd_soc_bytes_put(struct snd_kcontrol *kcontrol,
		      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct soc_bytes *params = (void *)kcontrol->private_value;
	int ret, len;
	unsigned int val, mask;
	void *data;

	if (!component->regmap || !params->num_regs)
		return -EINVAL;

	len = params->num_regs * component->val_bytes;

	data = kmemdup(ucontrol->value.bytes.data, len, GFP_KERNEL | GFP_DMA);
	if (!data)
		return -ENOMEM;

	/*
	 * If we've got a mask then we need to preserve the register
	 * bits.  We shouldn't modify the incoming data so take a
	 * copy.
	 */
	if (params->mask) {
		ret = regmap_read(component->regmap, params->base, &val);
		if (ret != 0)
			goto out;

		val &= params->mask;

		switch (component->val_bytes) {
		case 1:
			((u8 *)data)[0] &= ~params->mask;
			((u8 *)data)[0] |= val;
			break;
		case 2:
			mask = ~params->mask;
			ret = regmap_parse_val(component->regmap,
							&mask, &mask);
			if (ret != 0)
				goto out;

			((u16 *)data)[0] &= mask;

			ret = regmap_parse_val(component->regmap,
							&val, &val);
			if (ret != 0)
				goto out;

			((u16 *)data)[0] |= val;
			break;
		case 4:
			mask = ~params->mask;
			ret = regmap_parse_val(component->regmap,
							&mask, &mask);
			if (ret != 0)
				goto out;

			((u32 *)data)[0] &= mask;

			ret = regmap_parse_val(component->regmap,
							&val, &val);
			if (ret != 0)
				goto out;

			((u32 *)data)[0] |= val;
			break;
		default:
			ret = -EINVAL;
			goto out;
		}
	}

	ret = regmap_raw_write(component->regmap, params->base,
			       data, len);

out:
	kfree(data);

	return ret;
}