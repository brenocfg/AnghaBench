#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_kcontrol_new {int index; unsigned int private_value; void* subdevice; } ;
struct hda_gen_spec {int dummy; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* HDA_SUBDEV_AMP_FLAG ; 
 int /*<<< orphan*/  cap_sw_temp ; 
 int /*<<< orphan*/  cap_vol_temp ; 
 struct snd_kcontrol_new* snd_hda_gen_add_kctl (struct hda_gen_spec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_bind_cap_vol_ctl(struct hda_codec *codec, int idx,
				   unsigned int vol_ctl, unsigned int sw_ctl)
{
	struct hda_gen_spec *spec = codec->spec;
	struct snd_kcontrol_new *knew;

	if (vol_ctl) {
		knew = snd_hda_gen_add_kctl(spec, NULL, &cap_vol_temp);
		if (!knew)
			return -ENOMEM;
		knew->index = idx;
		knew->private_value = vol_ctl;
		knew->subdevice = HDA_SUBDEV_AMP_FLAG;
	}
	if (sw_ctl) {
		knew = snd_hda_gen_add_kctl(spec, NULL, &cap_sw_temp);
		if (!knew)
			return -ENOMEM;
		knew->index = idx;
		knew->private_value = sw_ctl;
		knew->subdevice = HDA_SUBDEV_AMP_FLAG;
	}
	return 0;
}