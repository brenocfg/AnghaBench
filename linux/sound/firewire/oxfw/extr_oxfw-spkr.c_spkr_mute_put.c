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
struct snd_oxfw {int /*<<< orphan*/  unit; struct fw_spkr* spec; } ;
struct snd_kcontrol {struct snd_oxfw* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct fw_spkr {int mute; int /*<<< orphan*/  mute_fb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_WRITE ; 
 int avc_audio_feature_mute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spkr_mute_put(struct snd_kcontrol *control,
			 struct snd_ctl_elem_value *value)
{
	struct snd_oxfw *oxfw = control->private_data;
	struct fw_spkr *spkr = oxfw->spec;
	bool mute;
	int err;

	mute = !value->value.integer.value[0];

	if (mute == spkr->mute)
		return 0;

	err = avc_audio_feature_mute(oxfw->unit, spkr->mute_fb_id, &mute,
				     CTL_WRITE);
	if (err < 0)
		return err;
	spkr->mute = mute;

	return 1;
}