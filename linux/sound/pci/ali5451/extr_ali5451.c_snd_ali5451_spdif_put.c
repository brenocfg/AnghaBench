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
struct snd_kcontrol {int private_value; struct snd_ali* private_data; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ali {int spdif_mask; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ali_disable_spdif_chnout (struct snd_ali*) ; 
 int /*<<< orphan*/  snd_ali_disable_spdif_in (struct snd_ali*) ; 
 int /*<<< orphan*/  snd_ali_disable_spdif_out (struct snd_ali*) ; 
 int /*<<< orphan*/  snd_ali_enable_spdif_chnout (struct snd_ali*) ; 
 int /*<<< orphan*/  snd_ali_enable_spdif_in (struct snd_ali*) ; 
 int /*<<< orphan*/  snd_ali_enable_spdif_out (struct snd_ali*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ali5451_spdif_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ali *codec = kcontrol->private_data;
	unsigned int change = 0, spdif_enable = 0;

	spdif_enable = ucontrol->value.integer.value[0] ? 1 : 0;

	spin_lock_irq(&codec->reg_lock);
	switch (kcontrol->private_value) {
	case 0:
		change = (codec->spdif_mask & 0x02) ? 1 : 0;
		change = change ^ spdif_enable;
		if (change) {
			if (spdif_enable) {
				codec->spdif_mask |= 0x02;
				snd_ali_enable_spdif_out(codec);
			} else {
				codec->spdif_mask &= ~(0x02);
				codec->spdif_mask &= ~(0x04);
				snd_ali_disable_spdif_out(codec);
			}
		}
		break;
	case 1: 
		change = (codec->spdif_mask & 0x04) ? 1 : 0;
		change = change ^ spdif_enable;
		if (change && (codec->spdif_mask & 0x02)) {
			if (spdif_enable) {
				codec->spdif_mask |= 0x04;
				snd_ali_enable_spdif_chnout(codec);
			} else {
				codec->spdif_mask &= ~(0x04);
				snd_ali_disable_spdif_chnout(codec);
			}
		}
		break;
	case 2:
		change = (codec->spdif_mask & 0x01) ? 1 : 0;
		change = change ^ spdif_enable;
		if (change) {
			if (spdif_enable) {
				codec->spdif_mask |= 0x01;
				snd_ali_enable_spdif_in(codec);
			} else {
				codec->spdif_mask &= ~(0x01);
				snd_ali_disable_spdif_in(codec);
			}
		}
		break;
	default:
		break;
	}
	spin_unlock_irq(&codec->reg_lock);
	
	return change;
}