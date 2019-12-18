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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_5__ {int* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct ct_mixer {struct amixer** amixers; } ;
struct ct_atc {scalar_t__ mixer; } ;
struct amixer {TYPE_1__* ops; } ;
typedef  enum CT_AMIXER_CTL { ____Placeholder_CT_AMIXER_CTL } CT_AMIXER_CTL ;
struct TYPE_4__ {int (* get_scale ) (struct amixer*) ;} ;

/* Variables and functions */
 int CHN_NUM ; 
 int VOL_MAX ; 
 int VOL_SCALE ; 
 int get_amixer_index (int /*<<< orphan*/ ) ; 
 struct ct_atc* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int stub1 (struct amixer*) ; 

__attribute__((used)) static int ct_alsa_mix_volume_get(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct ct_atc *atc = snd_kcontrol_chip(kcontrol);
	enum CT_AMIXER_CTL type = get_amixer_index(kcontrol->private_value);
	struct amixer *amixer;
	int i, val;

	for (i = 0; i < 2; i++) {
		amixer = ((struct ct_mixer *)atc->mixer)->
						amixers[type*CHN_NUM+i];
		val = amixer->ops->get_scale(amixer) / VOL_SCALE;
		if (val < 0)
			val = 0;
		else if (val > VOL_MAX)
			val = VOL_MAX;
		ucontrol->value.integer.value[i] = val;
	}

	return 0;
}