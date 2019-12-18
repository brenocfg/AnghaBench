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
struct snd_kcontrol {unsigned char private_value; } ;
struct TYPE_4__ {unsigned char* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ac97 {unsigned char channel_mode; TYPE_3__* build_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* update_jacks ) (struct snd_ac97*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (struct snd_ac97*) ; 

__attribute__((used)) static int ac97_channel_mode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	unsigned char mode = ucontrol->value.enumerated.item[0];

	if (mode >= kcontrol->private_value)
		return -EINVAL;

	if (mode != ac97->channel_mode) {
		ac97->channel_mode = mode;
		if (ac97->build_ops->update_jacks)
			ac97->build_ops->update_jacks(ac97);
		return 1;
	}
	return 0;
}