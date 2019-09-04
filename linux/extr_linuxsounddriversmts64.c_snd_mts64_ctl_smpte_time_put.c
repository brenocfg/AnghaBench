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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct mts64 {unsigned int* time; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct mts64* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_mts64_ctl_smpte_time_put(struct snd_kcontrol *kctl,
					struct snd_ctl_elem_value *uctl)
{
	struct mts64 *mts = snd_kcontrol_chip(kctl);
	int idx = kctl->private_value;
	unsigned int time = uctl->value.integer.value[0] % 60;
	int changed = 0;

	spin_lock_irq(&mts->lock);
	if (mts->time[idx] != time) {
		changed = 1;
		mts->time[idx] = time;
	}
	spin_unlock_irq(&mts->lock);

	return changed;
}