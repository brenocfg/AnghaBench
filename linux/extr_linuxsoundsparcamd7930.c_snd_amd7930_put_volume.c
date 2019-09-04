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
struct snd_amd7930 {int mgain; int rgain; int pgain; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  VOLUME_CAPTURE 130 
#define  VOLUME_MONITOR 129 
#define  VOLUME_PLAYBACK 128 
 int /*<<< orphan*/  __amd7930_update_map (struct snd_amd7930*) ; 
 struct snd_amd7930* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_amd7930_put_volume(struct snd_kcontrol *kctl, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_amd7930 *amd = snd_kcontrol_chip(kctl);
	unsigned long flags;
	int type = kctl->private_value;
	int *swval, change;

	switch (type) {
	case VOLUME_MONITOR:
		swval = &amd->mgain;
		break;
	case VOLUME_CAPTURE:
		swval = &amd->rgain;
		break;
	case VOLUME_PLAYBACK:
	default:
		swval = &amd->pgain;
		break;
	}

	spin_lock_irqsave(&amd->lock, flags);

	if (*swval != ucontrol->value.integer.value[0]) {
		*swval = ucontrol->value.integer.value[0] & 0xff;
		__amd7930_update_map(amd);
		change = 1;
	} else
		change = 0;

	spin_unlock_irqrestore(&amd->lock, flags);

	return change;
}