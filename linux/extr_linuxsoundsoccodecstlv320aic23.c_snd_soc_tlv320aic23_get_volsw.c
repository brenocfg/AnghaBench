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
typedef  int u16 ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLV320AIC23_ANLG ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_soc_tlv320aic23_get_volsw(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	u16 val;

	val = snd_soc_component_read32(component, TLV320AIC23_ANLG) & (0x1C0);
	val = val >> 6;
	val = (val >= 4) ? 4  : (3 -  val);
	ucontrol->value.integer.value[0] = val;
	return 0;

}