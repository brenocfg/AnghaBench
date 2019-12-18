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
struct snd_kcontrol_new {char* name; unsigned int index; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_card {int dummy; } ;
struct hdspm {int io_type; int system_sample_rate; unsigned int qs_out_channels; unsigned int ds_out_channels; unsigned int ss_out_channels; scalar_t__ tco; struct snd_kcontrol** playback_mixer_ctls; } ;

/* Variables and functions */
#define  AES32 132 
#define  AIO 131 
 unsigned int ARRAY_SIZE (struct snd_kcontrol_new*) ; 
#define  MADI 130 
#define  MADIface 129 
#define  RayDAT 128 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct hdspm*) ; 
 struct snd_kcontrol_new* snd_hdspm_controls_aes32 ; 
 struct snd_kcontrol_new* snd_hdspm_controls_aio ; 
 struct snd_kcontrol_new* snd_hdspm_controls_madi ; 
 struct snd_kcontrol_new* snd_hdspm_controls_madiface ; 
 struct snd_kcontrol_new* snd_hdspm_controls_raydat ; 
 struct snd_kcontrol_new* snd_hdspm_controls_tco ; 
 struct snd_kcontrol_new snd_hdspm_playback_mixer ; 

__attribute__((used)) static int snd_hdspm_create_controls(struct snd_card *card,
					struct hdspm *hdspm)
{
	unsigned int idx, limit;
	int err;
	struct snd_kcontrol *kctl;
	struct snd_kcontrol_new *list = NULL;

	switch (hdspm->io_type) {
	case MADI:
		list = snd_hdspm_controls_madi;
		limit = ARRAY_SIZE(snd_hdspm_controls_madi);
		break;
	case MADIface:
		list = snd_hdspm_controls_madiface;
		limit = ARRAY_SIZE(snd_hdspm_controls_madiface);
		break;
	case AIO:
		list = snd_hdspm_controls_aio;
		limit = ARRAY_SIZE(snd_hdspm_controls_aio);
		break;
	case RayDAT:
		list = snd_hdspm_controls_raydat;
		limit = ARRAY_SIZE(snd_hdspm_controls_raydat);
		break;
	case AES32:
		list = snd_hdspm_controls_aes32;
		limit = ARRAY_SIZE(snd_hdspm_controls_aes32);
		break;
	}

	if (list) {
		for (idx = 0; idx < limit; idx++) {
			err = snd_ctl_add(card,
					snd_ctl_new1(&list[idx], hdspm));
			if (err < 0)
				return err;
		}
	}


	/* create simple 1:1 playback mixer controls */
	snd_hdspm_playback_mixer.name = "Chn";
	if (hdspm->system_sample_rate >= 128000) {
		limit = hdspm->qs_out_channels;
	} else if (hdspm->system_sample_rate >= 64000) {
		limit = hdspm->ds_out_channels;
	} else {
		limit = hdspm->ss_out_channels;
	}
	for (idx = 0; idx < limit; ++idx) {
		snd_hdspm_playback_mixer.index = idx + 1;
		kctl = snd_ctl_new1(&snd_hdspm_playback_mixer, hdspm);
		err = snd_ctl_add(card, kctl);
		if (err < 0)
			return err;
		hdspm->playback_mixer_ctls[idx] = kctl;
	}


	if (hdspm->tco) {
		/* add tco control elements */
		list = snd_hdspm_controls_tco;
		limit = ARRAY_SIZE(snd_hdspm_controls_tco);
		for (idx = 0; idx < limit; idx++) {
			err = snd_ctl_add(card,
					snd_ctl_new1(&list[idx], hdspm));
			if (err < 0)
				return err;
		}
	}

	return 0;
}