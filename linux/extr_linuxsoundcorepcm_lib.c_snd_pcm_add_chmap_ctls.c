#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_chmap_elem {int dummy; } ;
struct snd_pcm_chmap {int stream; int max_channels; TYPE_3__* kctl; struct snd_pcm_chmap_elem const* chmap; struct snd_pcm* pcm; } ;
struct snd_pcm {TYPE_2__* streams; int /*<<< orphan*/  card; int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int /*<<< orphan*/  c; } ;
struct snd_kcontrol_new {int access; char* name; unsigned long private_value; int /*<<< orphan*/  count; int /*<<< orphan*/  device; TYPE_1__ tlv; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  iface; } ;
struct TYPE_8__ {int /*<<< orphan*/  private_free; } ;
struct TYPE_7__ {TYPE_3__* chmap_kctl; int /*<<< orphan*/  substream_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_CTL_ELEM_ACCESS_READ ; 
 int SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK ; 
 int SNDRV_CTL_ELEM_ACCESS_TLV_READ ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_PCM ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ WARN_ON (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_chmap*) ; 
 struct snd_pcm_chmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_chmap_ctl_get ; 
 int /*<<< orphan*/  pcm_chmap_ctl_info ; 
 int /*<<< orphan*/  pcm_chmap_ctl_private_free ; 
 int /*<<< orphan*/  pcm_chmap_ctl_tlv ; 
 int snd_ctl_add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_pcm_chmap*) ; 

int snd_pcm_add_chmap_ctls(struct snd_pcm *pcm, int stream,
			   const struct snd_pcm_chmap_elem *chmap,
			   int max_channels,
			   unsigned long private_value,
			   struct snd_pcm_chmap **info_ret)
{
	struct snd_pcm_chmap *info;
	struct snd_kcontrol_new knew = {
		.iface = SNDRV_CTL_ELEM_IFACE_PCM,
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ |
			SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK,
		.info = pcm_chmap_ctl_info,
		.get = pcm_chmap_ctl_get,
		.tlv.c = pcm_chmap_ctl_tlv,
	};
	int err;

	if (WARN_ON(pcm->streams[stream].chmap_kctl))
		return -EBUSY;
	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	info->pcm = pcm;
	info->stream = stream;
	info->chmap = chmap;
	info->max_channels = max_channels;
	if (stream == SNDRV_PCM_STREAM_PLAYBACK)
		knew.name = "Playback Channel Map";
	else
		knew.name = "Capture Channel Map";
	knew.device = pcm->device;
	knew.count = pcm->streams[stream].substream_count;
	knew.private_value = private_value;
	info->kctl = snd_ctl_new1(&knew, info);
	if (!info->kctl) {
		kfree(info);
		return -ENOMEM;
	}
	info->kctl->private_free = pcm_chmap_ctl_private_free;
	err = snd_ctl_add(pcm->card, info->kctl);
	if (err < 0)
		return err;
	pcm->streams[stream].chmap_kctl = info->kctl;
	if (info_ret)
		*info_ret = info;
	return 0;
}