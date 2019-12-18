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
struct soc_enum {unsigned int items; unsigned int shift_l; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {unsigned int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct cs43130_private {int dev_id; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CS43131_CHIP_ID 129 
#define  CS43198_CHIP_ID 128 
 int EINVAL ; 
 int /*<<< orphan*/  pcm_ch_dis_seq ; 
 int /*<<< orphan*/  pcm_ch_en_seq ; 
 int /*<<< orphan*/  regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs43130_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_enum_item_to_val (struct soc_enum*,unsigned int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_put_enum_double (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int cs43130_pcm_ch_put(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int *item = ucontrol->value.enumerated.item;
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct cs43130_private *cs43130 = snd_soc_component_get_drvdata(component);
	unsigned int val;

	if (item[0] >= e->items)
		return -EINVAL;
	val = snd_soc_enum_item_to_val(e, item[0]) << e->shift_l;

	switch (cs43130->dev_id) {
	case CS43131_CHIP_ID:
	case CS43198_CHIP_ID:
		if (val >= 2)
			regmap_multi_reg_write(cs43130->regmap, pcm_ch_en_seq,
					       ARRAY_SIZE(pcm_ch_en_seq));
		else
			regmap_multi_reg_write(cs43130->regmap, pcm_ch_dis_seq,
					       ARRAY_SIZE(pcm_ch_dis_seq));
		break;
	}

	return snd_soc_put_enum_double(kcontrol, ucontrol);
}