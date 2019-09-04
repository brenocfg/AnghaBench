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
struct snd_kcontrol {int dummy; } ;
struct snd_intelhad {unsigned int aes_bits; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_intelhad* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int had_iec958_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	unsigned int val;
	struct snd_intelhad *intelhaddata = snd_kcontrol_chip(kcontrol);
	int changed = 0;

	val = (ucontrol->value.iec958.status[0] << 0) |
		(ucontrol->value.iec958.status[1] << 8) |
		(ucontrol->value.iec958.status[2] << 16) |
		(ucontrol->value.iec958.status[3] << 24);
	mutex_lock(&intelhaddata->mutex);
	if (intelhaddata->aes_bits != val) {
		intelhaddata->aes_bits = val;
		changed = 1;
	}
	mutex_unlock(&intelhaddata->mutex);
	return changed;
}