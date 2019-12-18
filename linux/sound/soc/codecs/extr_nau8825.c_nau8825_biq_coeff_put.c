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
struct soc_bytes_ext {int /*<<< orphan*/  max; } ;
struct snd_soc_component {int /*<<< orphan*/  regmap; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  NAU8825_BIQ_WRT_EN ; 
 int /*<<< orphan*/  NAU8825_REG_BIQ_COF1 ; 
 int /*<<< orphan*/  NAU8825_REG_BIQ_CTRL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_raw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int nau8825_biq_coeff_put(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	struct soc_bytes_ext *params = (void *)kcontrol->private_value;
	void *data;

	if (!component->regmap)
		return -EINVAL;

	data = kmemdup(ucontrol->value.bytes.data,
		params->max, GFP_KERNEL | GFP_DMA);
	if (!data)
		return -ENOMEM;

	regmap_update_bits(component->regmap, NAU8825_REG_BIQ_CTRL,
		NAU8825_BIQ_WRT_EN, 0);
	regmap_raw_write(component->regmap, NAU8825_REG_BIQ_COF1,
		data, params->max);
	regmap_update_bits(component->regmap, NAU8825_REG_BIQ_CTRL,
		NAU8825_BIQ_WRT_EN, NAU8825_BIQ_WRT_EN);

	kfree(data);
	return 0;
}