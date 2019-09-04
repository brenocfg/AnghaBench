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
struct snd_pcm_chmap {struct snd_kcontrol* kctl; struct hdac_chmap* private_data; } ;
struct snd_pcm {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  c; } ;
struct snd_kcontrol {int count; TYPE_2__ tlv; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; TYPE_1__* vd; } ;
struct hdac_chmap {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_WRITE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  hdmi_chmap_ctl_get ; 
 int /*<<< orphan*/  hdmi_chmap_ctl_info ; 
 int /*<<< orphan*/  hdmi_chmap_ctl_put ; 
 int /*<<< orphan*/  hdmi_chmap_ctl_tlv ; 
 int snd_pcm_add_chmap_ctls (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct snd_pcm_chmap**) ; 

int snd_hdac_add_chmap_ctls(struct snd_pcm *pcm, int pcm_idx,
				struct hdac_chmap *hchmap)
{
	struct snd_pcm_chmap *chmap;
	struct snd_kcontrol *kctl;
	int err, i;

	err = snd_pcm_add_chmap_ctls(pcm,
				     SNDRV_PCM_STREAM_PLAYBACK,
				     NULL, 0, pcm_idx, &chmap);
	if (err < 0)
		return err;
	/* override handlers */
	chmap->private_data = hchmap;
	kctl = chmap->kctl;
	for (i = 0; i < kctl->count; i++)
		kctl->vd[i].access |= SNDRV_CTL_ELEM_ACCESS_WRITE;
	kctl->info = hdmi_chmap_ctl_info;
	kctl->get = hdmi_chmap_ctl_get;
	kctl->put = hdmi_chmap_ctl_put;
	kctl->tlv.c = hdmi_chmap_ctl_tlv;

	return 0;
}