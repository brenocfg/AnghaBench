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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hdmi_eld {scalar_t__ eld_size; int /*<<< orphan*/  eld_buffer; scalar_t__ eld_valid; } ;
struct hdmi_spec_per_pin {struct hdmi_eld sink_eld; } ;
struct hdmi_spec {int /*<<< orphan*/  pcm_lock; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ ELD_MAX_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hdmi_spec_per_pin* pcm_idx_to_pin (struct hdmi_spec*,int) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int hdmi_eld_ctl_get(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_pin *per_pin;
	struct hdmi_eld *eld;
	int pcm_idx;
	int err = 0;

	pcm_idx = kcontrol->private_value;
	mutex_lock(&spec->pcm_lock);
	per_pin = pcm_idx_to_pin(spec, pcm_idx);
	if (!per_pin) {
		/* no pin is bound to the pcm */
		memset(ucontrol->value.bytes.data, 0,
		       ARRAY_SIZE(ucontrol->value.bytes.data));
		goto unlock;
	}

	eld = &per_pin->sink_eld;
	if (eld->eld_size > ARRAY_SIZE(ucontrol->value.bytes.data) ||
	    eld->eld_size > ELD_MAX_SIZE) {
		snd_BUG();
		err = -EINVAL;
		goto unlock;
	}

	memset(ucontrol->value.bytes.data, 0,
	       ARRAY_SIZE(ucontrol->value.bytes.data));
	if (eld->eld_valid)
		memcpy(ucontrol->value.bytes.data, eld->eld_buffer,
		       eld->eld_size);

 unlock:
	mutex_unlock(&spec->pcm_lock);
	return err;
}