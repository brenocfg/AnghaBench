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
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct max98095_priv {unsigned int mic1pre; } ;

/* Variables and functions */
 int /*<<< orphan*/  M98095_05F_LVL_MIC1 ; 
 int /*<<< orphan*/  M98095_MICPRE_MASK ; 
 int M98095_MICPRE_SHIFT ; 
 struct max98095_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int max98095_mic1pre_set(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	unsigned int sel = ucontrol->value.integer.value[0];

	max98095->mic1pre = sel;
	snd_soc_component_update_bits(component, M98095_05F_LVL_MIC1, M98095_MICPRE_MASK,
		(1+sel)<<M98095_MICPRE_SHIFT);

	return 0;
}