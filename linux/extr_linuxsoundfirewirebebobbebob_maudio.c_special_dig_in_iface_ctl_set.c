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
struct special_params {scalar_t__ dig_in_fmt; int /*<<< orphan*/  clk_lock; int /*<<< orphan*/  dig_out_fmt; int /*<<< orphan*/  clk_src; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {unsigned int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_bebob {int /*<<< orphan*/  mutex; TYPE_3__* unit; struct special_params* maudio_special_quirk; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int avc_audio_set_selector (TYPE_3__*,int,int,unsigned int) ; 
 int avc_maudio_set_special_clk (struct snd_bebob*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_bebob* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  special_dig_in_iface_labels ; 
 int /*<<< orphan*/  special_stream_formation_set (struct snd_bebob*) ; 

__attribute__((used)) static int special_dig_in_iface_ctl_set(struct snd_kcontrol *kctl,
					struct snd_ctl_elem_value *uval)
{
	struct snd_bebob *bebob = snd_kcontrol_chip(kctl);
	struct special_params *params = bebob->maudio_special_quirk;
	unsigned int id, dig_in_fmt, dig_in_iface;
	int err;

	id = uval->value.enumerated.item[0];
	if (id >= ARRAY_SIZE(special_dig_in_iface_labels))
		return -EINVAL;

	/* decode user value */
	dig_in_fmt = (id >> 1) & 0x01;
	dig_in_iface = id & 0x01;

	mutex_lock(&bebob->mutex);

	err = avc_maudio_set_special_clk(bebob,
					 params->clk_src,
					 dig_in_fmt,
					 params->dig_out_fmt,
					 params->clk_lock);
	if (err < 0)
		goto end;

	/* For ADAT, optical interface is only available. */
	if (params->dig_in_fmt > 0) {
		err = 1;
		goto end;
	}

	/* For S/PDIF, optical/coaxial interfaces are selectable. */
	err = avc_audio_set_selector(bebob->unit, 0x00, 0x04, dig_in_iface);
	if (err < 0)
		dev_err(&bebob->unit->device,
			"fail to set digital input interface: %d\n", err);
	err = 1;
end:
	special_stream_formation_set(bebob);
	mutex_unlock(&bebob->mutex);
	return err;
}