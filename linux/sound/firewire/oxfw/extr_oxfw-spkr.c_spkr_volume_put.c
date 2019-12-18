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
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct fw_spkr {unsigned int mixer_channels; scalar_t__ volume_min; scalar_t__ volume_max; scalar_t__* volume; int /*<<< orphan*/  volume_fb_id; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_CURRENT ; 
 int /*<<< orphan*/  CTL_WRITE ; 
 int EINVAL ; 
 int avc_audio_feature_volume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t* channel_map ; 

__attribute__((used)) static int spkr_volume_put(struct snd_kcontrol *control,
			   struct snd_ctl_elem_value *value)
{
	struct snd_oxfw *oxfw = control->private_data;
	struct fw_spkr *spkr = oxfw->spec;
	unsigned int i, changed_channels;
	bool equal_values = true;
	s16 volume;
	int err;

	for (i = 0; i < spkr->mixer_channels; ++i) {
		if (value->value.integer.value[i] < spkr->volume_min ||
		    value->value.integer.value[i] > spkr->volume_max)
			return -EINVAL;
		if (value->value.integer.value[i] !=
		    value->value.integer.value[0])
			equal_values = false;
	}

	changed_channels = 0;
	for (i = 0; i < spkr->mixer_channels; ++i)
		if (value->value.integer.value[channel_map[i]] !=
							spkr->volume[i])
			changed_channels |= 1 << (i + 1);

	if (equal_values && changed_channels != 0)
		changed_channels = 1 << 0;

	for (i = 0; i <= spkr->mixer_channels; ++i) {
		volume = value->value.integer.value[channel_map[i ? i - 1 : 0]];
		if (changed_channels & (1 << i)) {
			err = avc_audio_feature_volume(oxfw->unit,
						  spkr->volume_fb_id, &volume,
						  i, CTL_CURRENT, CTL_WRITE);
			if (err < 0)
				return err;
		}
		if (i > 0)
			spkr->volume[i - 1] = volume;
	}

	return changed_channels != 0;
}