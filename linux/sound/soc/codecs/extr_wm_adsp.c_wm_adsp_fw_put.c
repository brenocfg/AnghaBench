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
struct wm_adsp {scalar_t__ fw; int /*<<< orphan*/  pwr_lock; int /*<<< orphan*/  compr_list; scalar_t__ booted; } ;
struct soc_enum {size_t shift_l; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {scalar_t__* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ WM_ADSP_NUM_FW ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wm_adsp* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

int wm_adsp_fw_put(struct snd_kcontrol *kcontrol,
		   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	struct wm_adsp *dsp = snd_soc_component_get_drvdata(component);
	int ret = 0;

	if (ucontrol->value.enumerated.item[0] == dsp[e->shift_l].fw)
		return 0;

	if (ucontrol->value.enumerated.item[0] >= WM_ADSP_NUM_FW)
		return -EINVAL;

	mutex_lock(&dsp[e->shift_l].pwr_lock);

	if (dsp[e->shift_l].booted || !list_empty(&dsp[e->shift_l].compr_list))
		ret = -EBUSY;
	else
		dsp[e->shift_l].fw = ucontrol->value.enumerated.item[0];

	mutex_unlock(&dsp[e->shift_l].pwr_lock);

	return ret;
}