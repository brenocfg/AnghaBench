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
struct snd_intelhad {int aes_bits; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_intelhad* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int had_iec958_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_intelhad *intelhaddata = snd_kcontrol_chip(kcontrol);

	mutex_lock(&intelhaddata->mutex);
	ucontrol->value.iec958.status[0] = (intelhaddata->aes_bits >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (intelhaddata->aes_bits >> 8) & 0xff;
	ucontrol->value.iec958.status[2] =
					(intelhaddata->aes_bits >> 16) & 0xff;
	ucontrol->value.iec958.status[3] =
					(intelhaddata->aes_bits >> 24) & 0xff;
	mutex_unlock(&intelhaddata->mutex);
	return 0;
}