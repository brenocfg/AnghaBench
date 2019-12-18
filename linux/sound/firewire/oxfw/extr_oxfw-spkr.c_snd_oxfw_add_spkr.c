#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_oxfw {TYPE_1__* card; int /*<<< orphan*/  unit; struct fw_spkr* spec; } ;
struct snd_kcontrol_new {char* name; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  const iface; } ;
struct fw_spkr {int mixer_channels; int mute_fb_id; int volume_fb_id; int /*<<< orphan*/ * volume; int /*<<< orphan*/  mute; int /*<<< orphan*/  volume_max; int /*<<< orphan*/  volume_min; } ;
struct TYPE_2__ {int /*<<< orphan*/  card_dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct snd_kcontrol_new const*) ; 
 int /*<<< orphan*/  CTL_CURRENT ; 
 int /*<<< orphan*/  CTL_MAX ; 
 int /*<<< orphan*/  CTL_MIN ; 
 int /*<<< orphan*/  CTL_READ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  SNDRV_CTL_ELEM_IFACE_MIXER 134 
 int avc_audio_feature_mute (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int avc_audio_feature_volume (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fw_spkr* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int snd_ctl_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  snd_ctl_boolean_mono_info 133 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new const*,struct snd_oxfw*) ; 
#define  spkr_mute_get 132 
#define  spkr_mute_put 131 
#define  spkr_volume_get 130 
#define  spkr_volume_info 129 
#define  spkr_volume_put 128 

int snd_oxfw_add_spkr(struct snd_oxfw *oxfw, bool is_lacie)
{
	static const struct snd_kcontrol_new controls[] = {
		{
			.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
			.name = "PCM Playback Switch",
			.info = snd_ctl_boolean_mono_info,
			.get = spkr_mute_get,
			.put = spkr_mute_put,
		},
		{
			.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
			.name = "PCM Playback Volume",
			.info = spkr_volume_info,
			.get = spkr_volume_get,
			.put = spkr_volume_put,
		},
	};
	struct fw_spkr *spkr;
	unsigned int i, first_ch;
	int err;

	spkr = devm_kzalloc(&oxfw->card->card_dev, sizeof(struct fw_spkr),
			    GFP_KERNEL);
	if (!spkr)
		return -ENOMEM;
	oxfw->spec = spkr;

	if (is_lacie) {
		spkr->mixer_channels = 1;
		spkr->mute_fb_id = 0x01;
		spkr->volume_fb_id = 0x01;
	} else {
		spkr->mixer_channels = 6;
		spkr->mute_fb_id = 0x01;
		spkr->volume_fb_id = 0x02;
	}

	err = avc_audio_feature_volume(oxfw->unit, spkr->volume_fb_id,
				       &spkr->volume_min, 0, CTL_MIN, CTL_READ);
	if (err < 0)
		return err;
	err = avc_audio_feature_volume(oxfw->unit, spkr->volume_fb_id,
				       &spkr->volume_max, 0, CTL_MAX, CTL_READ);
	if (err < 0)
		return err;

	err = avc_audio_feature_mute(oxfw->unit, spkr->mute_fb_id, &spkr->mute,
				     CTL_READ);
	if (err < 0)
		return err;

	first_ch = spkr->mixer_channels == 1 ? 0 : 1;
	for (i = 0; i < spkr->mixer_channels; ++i) {
		err = avc_audio_feature_volume(oxfw->unit, spkr->volume_fb_id,
					       &spkr->volume[i], first_ch + i,
					       CTL_CURRENT, CTL_READ);
		if (err < 0)
			return err;
	}

	for (i = 0; i < ARRAY_SIZE(controls); ++i) {
		err = snd_ctl_add(oxfw->card,
				  snd_ctl_new1(&controls[i], oxfw));
		if (err < 0)
			return err;
	}

	return 0;
}