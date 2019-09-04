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
struct snd_pcm_chmap {unsigned int max_channels; TYPE_1__* chmap; struct hdmi_codec_priv* private_data; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {unsigned char* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct hdmi_codec_priv {size_t chmap_idx; } ;
struct TYPE_4__ {unsigned char* map; } ;

/* Variables and functions */
 size_t HDMI_CODEC_CHMAP_IDX_UNKNOWN ; 
 struct snd_pcm_chmap* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int hdmi_codec_chmap_ctl_get(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	unsigned const char *map;
	unsigned int i;
	struct snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	struct hdmi_codec_priv *hcp = info->private_data;

	map = info->chmap[hcp->chmap_idx].map;

	for (i = 0; i < info->max_channels; i++) {
		if (hcp->chmap_idx == HDMI_CODEC_CHMAP_IDX_UNKNOWN)
			ucontrol->value.integer.value[i] = 0;
		else
			ucontrol->value.integer.value[i] = map[i];
	}

	return 0;
}