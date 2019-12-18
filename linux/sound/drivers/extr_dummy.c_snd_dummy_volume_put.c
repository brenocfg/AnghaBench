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
struct snd_dummy {int** mixer_volume; int /*<<< orphan*/  mixer_lock; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct snd_dummy* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_dummy_volume_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_dummy *dummy = snd_kcontrol_chip(kcontrol);
	int change, addr = kcontrol->private_value;
	int left, right;

	left = ucontrol->value.integer.value[0];
	if (left < -50)
		left = -50;
	if (left > 100)
		left = 100;
	right = ucontrol->value.integer.value[1];
	if (right < -50)
		right = -50;
	if (right > 100)
		right = 100;
	spin_lock_irq(&dummy->mixer_lock);
	change = dummy->mixer_volume[addr][0] != left ||
	         dummy->mixer_volume[addr][1] != right;
	dummy->mixer_volume[addr][0] = left;
	dummy->mixer_volume[addr][1] = right;
	spin_unlock_irq(&dummy->mixer_lock);
	return change;
}