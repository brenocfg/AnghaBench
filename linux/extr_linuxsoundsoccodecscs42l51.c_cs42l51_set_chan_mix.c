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

/* Variables and functions */
 unsigned char CHAN_MIX_BOTH ; 
 unsigned char CHAN_MIX_NORMAL ; 
 unsigned char CHAN_MIX_SWAP ; 
 int /*<<< orphan*/  CS42L51_PCM_MIXER ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned char) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int cs42l51_set_chan_mix(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	unsigned char val;

	switch (ucontrol->value.enumerated.item[0]) {
	default:
	case 0:
		val = CHAN_MIX_NORMAL;
		break;
	case 1:
		val = CHAN_MIX_BOTH;
		break;
	case 2:
		val = CHAN_MIX_SWAP;
		break;
	}

	snd_soc_component_write(component, CS42L51_PCM_MIXER, val);

	return 1;
}