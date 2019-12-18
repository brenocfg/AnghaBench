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
typedef  int /*<<< orphan*/  uint8_t ;
struct snd_kcontrol {TYPE_3__* vd; scalar_t__ private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct sigmadsp_control {int cached; int /*<<< orphan*/  num_bytes; int /*<<< orphan*/  cache; } ;
struct sigmadsp {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int access; } ;

/* Variables and functions */
 int SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sigmadsp_ctrl_write (struct sigmadsp*,struct sigmadsp_control*,int /*<<< orphan*/ *) ; 
 struct sigmadsp* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int sigmadsp_ctrl_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct sigmadsp_control *ctrl = (void *)kcontrol->private_value;
	struct sigmadsp *sigmadsp = snd_kcontrol_chip(kcontrol);
	uint8_t *data;
	int ret = 0;

	mutex_lock(&sigmadsp->lock);

	data = ucontrol->value.bytes.data;

	if (!(kcontrol->vd[0].access & SNDRV_CTL_ELEM_ACCESS_INACTIVE))
		ret = sigmadsp_ctrl_write(sigmadsp, ctrl, data);

	if (ret == 0) {
		memcpy(ctrl->cache, data, ctrl->num_bytes);
		ctrl->cached = true;
	}

	mutex_unlock(&sigmadsp->lock);

	return ret;
}