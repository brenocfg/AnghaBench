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
struct snd_kcontrol {int private_value; } ;
struct snd_ice1712 {int* pro_volumes; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ice1712_update_volume (struct snd_ice1712*,int) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ice1712_pro_mixer_volume_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	int priv_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) +
		kcontrol->private_value;
	unsigned int nval, change;

	nval = (ucontrol->value.integer.value[0] & 127) |
	       ((ucontrol->value.integer.value[1] & 127) << 16);
	spin_lock_irq(&ice->reg_lock);
	nval |= ice->pro_volumes[priv_idx] & ~0x007f007f;
	change = nval != ice->pro_volumes[priv_idx];
	ice->pro_volumes[priv_idx] = nval;
	snd_ice1712_update_volume(ice, priv_idx);
	spin_unlock_irq(&ice->reg_lock);
	return change;
}