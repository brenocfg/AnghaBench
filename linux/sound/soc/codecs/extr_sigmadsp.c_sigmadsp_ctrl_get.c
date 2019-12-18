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
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct sigmadsp_control {int cached; int /*<<< orphan*/  num_bytes; int /*<<< orphan*/  cache; int /*<<< orphan*/  addr; } ;
struct sigmadsp {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sigmadsp_read (struct sigmadsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sigmadsp* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int sigmadsp_ctrl_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct sigmadsp_control *ctrl = (void *)kcontrol->private_value;
	struct sigmadsp *sigmadsp = snd_kcontrol_chip(kcontrol);
	int ret = 0;

	mutex_lock(&sigmadsp->lock);

	if (!ctrl->cached) {
		ret = sigmadsp_read(sigmadsp, ctrl->addr, ctrl->cache,
			ctrl->num_bytes);
	}

	if (ret == 0) {
		ctrl->cached = true;
		memcpy(ucontrol->value.bytes.data, ctrl->cache,
			ctrl->num_bytes);
	}

	mutex_unlock(&sigmadsp->lock);

	return ret;
}