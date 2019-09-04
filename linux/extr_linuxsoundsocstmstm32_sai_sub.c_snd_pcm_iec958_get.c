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
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct stm32_sai_sub_data {int /*<<< orphan*/  ctrl_lock; TYPE_3__ iec958; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stm32_sai_sub_data* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_pcm_iec958_get(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *uctl)
{
	struct stm32_sai_sub_data *sai = snd_kcontrol_chip(kcontrol);

	mutex_lock(&sai->ctrl_lock);
	memcpy(uctl->value.iec958.status, sai->iec958.status, 4);
	mutex_unlock(&sai->ctrl_lock);

	return 0;
}