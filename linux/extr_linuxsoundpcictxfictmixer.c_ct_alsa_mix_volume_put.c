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
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct ct_mixer {struct amixer** amixers; } ;
struct ct_atc {struct ct_mixer* mixer; } ;
struct amixer {TYPE_3__* ops; } ;
typedef  enum CT_AMIXER_CTL { ____Placeholder_CT_AMIXER_CTL } CT_AMIXER_CTL ;
struct TYPE_6__ {int (* get_scale ) (struct amixer*) ;int /*<<< orphan*/  (* commit_write ) (struct amixer*) ;int /*<<< orphan*/  (* set_scale ) (struct amixer*,int) ;} ;

/* Variables and functions */
 int AMIXER_MASTER_F ; 
 int AMIXER_PCM_F ; 
 int CHN_NUM ; 
 int VOL_MAX ; 
 int VOL_SCALE ; 
 int get_amixer_index (int /*<<< orphan*/ ) ; 
 struct ct_atc* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int stub1 (struct amixer*) ; 
 int /*<<< orphan*/  stub2 (struct amixer*,int) ; 
 int /*<<< orphan*/  stub3 (struct amixer*) ; 
 int /*<<< orphan*/  stub4 (struct amixer*,int) ; 
 int /*<<< orphan*/  stub5 (struct amixer*) ; 

__attribute__((used)) static int ct_alsa_mix_volume_put(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct ct_atc *atc = snd_kcontrol_chip(kcontrol);
	struct ct_mixer *mixer = atc->mixer;
	enum CT_AMIXER_CTL type = get_amixer_index(kcontrol->private_value);
	struct amixer *amixer;
	int i, j, val, oval, change = 0;

	for (i = 0; i < 2; i++) {
		val = ucontrol->value.integer.value[i];
		if (val < 0)
			val = 0;
		else if (val > VOL_MAX)
			val = VOL_MAX;
		val *= VOL_SCALE;
		amixer = mixer->amixers[type*CHN_NUM+i];
		oval = amixer->ops->get_scale(amixer);
		if (val != oval) {
			amixer->ops->set_scale(amixer, val);
			amixer->ops->commit_write(amixer);
			change = 1;
			/* Synchronize Master/PCM playback AMIXERs. */
			if (AMIXER_MASTER_F == type || AMIXER_PCM_F == type) {
				for (j = 1; j < 4; j++) {
					amixer = mixer->
						amixers[(type+j)*CHN_NUM+i];
					amixer->ops->set_scale(amixer, val);
					amixer->ops->commit_write(amixer);
				}
			}
		}
	}

	return change;
}