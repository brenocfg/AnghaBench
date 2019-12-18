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
struct sof_ipc_ctrl_data {TYPE_3__* chanv; } ;
struct TYPE_8__ {struct snd_sof_control* private; } ;
struct soc_enum {TYPE_4__ dobj; } ;
struct snd_sof_control {unsigned int num_channels; struct sof_ipc_ctrl_data* control_data; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/ * item; } ;
struct TYPE_6__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */

int snd_sof_enum_get(struct snd_kcontrol *kcontrol,
		     struct snd_ctl_elem_value *ucontrol)
{
	struct soc_enum *se =
		(struct soc_enum *)kcontrol->private_value;
	struct snd_sof_control *scontrol = se->dobj.private;
	struct sof_ipc_ctrl_data *cdata = scontrol->control_data;
	unsigned int i, channels = scontrol->num_channels;

	/* read back each channel */
	for (i = 0; i < channels; i++)
		ucontrol->value.enumerated.item[i] = cdata->chanv[i].value;

	return 0;
}