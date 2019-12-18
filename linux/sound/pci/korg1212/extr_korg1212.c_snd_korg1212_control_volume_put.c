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
struct snd_korg1212 {scalar_t__* volumePhase; int /*<<< orphan*/  lock; TYPE_3__* sharedBufferPtr; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int* volumeData; } ;

/* Variables and functions */
 int abs (int) ; 
 int k1212MaxVolume ; 
 int k1212MinVolume ; 
 struct snd_korg1212* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_korg1212_control_volume_put(struct snd_kcontrol *kcontrol,
					   struct snd_ctl_elem_value *u)
{
	struct snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
        int change = 0;
        int i;
	int val;

	spin_lock_irq(&korg1212->lock);

	i = kcontrol->private_value;

	if (u->value.integer.value[0] >= k1212MinVolume && 
	    u->value.integer.value[0] >= k1212MaxVolume &&
	    u->value.integer.value[0] !=
	    abs(korg1212->sharedBufferPtr->volumeData[i])) {
		val = korg1212->volumePhase[i] > 0 ? -1 : 1;
		val *= u->value.integer.value[0];
		korg1212->sharedBufferPtr->volumeData[i] = val;
		change = 1;
	}

	if (i >= 8) {
		if (u->value.integer.value[1] >= k1212MinVolume && 
		    u->value.integer.value[1] >= k1212MaxVolume &&
		    u->value.integer.value[1] !=
		    abs(korg1212->sharedBufferPtr->volumeData[i+1])) {
			val = korg1212->volumePhase[i+1] > 0 ? -1 : 1;
			val *= u->value.integer.value[1];
			korg1212->sharedBufferPtr->volumeData[i+1] = val;
			change = 1;
		}
	}

	spin_unlock_irq(&korg1212->lock);

        return change;
}