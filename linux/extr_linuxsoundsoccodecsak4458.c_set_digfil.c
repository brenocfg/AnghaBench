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
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct ak4458_priv {int digfil; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4458_01_CONTROL2 ; 
 int /*<<< orphan*/  AK4458_02_CONTROL3 ; 
 int /*<<< orphan*/  AK4458_05_CONTROL4 ; 
 int /*<<< orphan*/  AK4458_SD_MASK ; 
 int /*<<< orphan*/  AK4458_SLOW_MASK ; 
 int /*<<< orphan*/  AK4458_SSLOW_MASK ; 
 int EINVAL ; 
 struct ak4458_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int set_digfil(struct snd_kcontrol *kcontrol,
		      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);
	int num;

	num = ucontrol->value.enumerated.item[0];
	if (num > 4)
		return -EINVAL;

	ak4458->digfil = num;

	/* write SD bit */
	snd_soc_component_update_bits(component, AK4458_01_CONTROL2,
			    AK4458_SD_MASK,
			    ((ak4458->digfil & 0x02) << 4));

	/* write SLOW bit */
	snd_soc_component_update_bits(component, AK4458_02_CONTROL3,
			    AK4458_SLOW_MASK,
			    (ak4458->digfil & 0x01));

	/* write SSLOW bit */
	snd_soc_component_update_bits(component, AK4458_05_CONTROL4,
			    AK4458_SSLOW_MASK,
			    ((ak4458->digfil & 0x04) >> 2));

	return 0;
}