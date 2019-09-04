#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t subdevice; size_t device; } ;
struct snd_kcontrol {TYPE_4__ id; } ;
struct TYPE_5__ {scalar_t__* value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct loopback {int /*<<< orphan*/  cable_lock; TYPE_3__** setup; } ;
struct TYPE_7__ {unsigned int notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct loopback* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int loopback_notify_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct loopback *loopback = snd_kcontrol_chip(kcontrol);
	unsigned int val;
	int change = 0;

	val = ucontrol->value.integer.value[0] ? 1 : 0;
	mutex_lock(&loopback->cable_lock);
	if (val != loopback->setup[kcontrol->id.subdevice]
				[kcontrol->id.device].notify) {
		loopback->setup[kcontrol->id.subdevice]
			[kcontrol->id.device].notify = val;
		change = 1;
	}
	mutex_unlock(&loopback->cable_lock);
	return change;
}