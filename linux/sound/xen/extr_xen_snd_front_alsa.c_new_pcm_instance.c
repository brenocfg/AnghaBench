#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct xen_snd_front_pcm_stream_info {int dummy; } ;
struct xen_snd_front_pcm_instance_info {int num_pcm_streams_pb; int num_pcm_streams_cap; struct snd_pcm* pcm; TYPE_5__* streams_cap; TYPE_3__* streams_pb; int /*<<< orphan*/  pcm_hw; struct xen_snd_front_card_info* card_info; } ;
struct xen_snd_front_card_info {TYPE_7__* card; TYPE_2__* front_info; } ;
struct xen_front_cfg_pcm_instance {int num_streams_pb; int num_streams_cap; int /*<<< orphan*/  device_id; int /*<<< orphan*/  name; TYPE_6__* streams_cap; TYPE_4__* streams_pb; int /*<<< orphan*/  pcm_hw; } ;
struct snd_pcm {int nonatomic; int /*<<< orphan*/  name; scalar_t__ info_flags; struct xen_snd_front_pcm_instance_info* private_data; } ;
struct TYPE_14__ {int /*<<< orphan*/  card_dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  index; int /*<<< orphan*/  pcm_hw; } ;
struct TYPE_12__ {int /*<<< orphan*/  index; int /*<<< orphan*/  pcm_hw; } ;
struct TYPE_11__ {int /*<<< orphan*/  index; int /*<<< orphan*/  pcm_hw; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; int /*<<< orphan*/  pcm_hw; } ;
struct TYPE_9__ {TYPE_1__* xb_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_drv_alsa_capture_ops ; 
 int /*<<< orphan*/  snd_drv_alsa_playback_ops ; 
 int snd_pcm_new (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int new_pcm_instance(struct xen_snd_front_card_info *card_info,
			    struct xen_front_cfg_pcm_instance *instance_cfg,
			    struct xen_snd_front_pcm_instance_info *pcm_instance_info)
{
	struct snd_pcm *pcm;
	int ret, i;

	dev_dbg(&card_info->front_info->xb_dev->dev,
		"New PCM device \"%s\" with id %d playback %d capture %d",
		instance_cfg->name,
		instance_cfg->device_id,
		instance_cfg->num_streams_pb,
		instance_cfg->num_streams_cap);

	pcm_instance_info->card_info = card_info;

	pcm_instance_info->pcm_hw = instance_cfg->pcm_hw;

	if (instance_cfg->num_streams_pb) {
		pcm_instance_info->streams_pb =
				devm_kcalloc(&card_info->card->card_dev,
					     instance_cfg->num_streams_pb,
					     sizeof(struct xen_snd_front_pcm_stream_info),
					     GFP_KERNEL);
		if (!pcm_instance_info->streams_pb)
			return -ENOMEM;
	}

	if (instance_cfg->num_streams_cap) {
		pcm_instance_info->streams_cap =
				devm_kcalloc(&card_info->card->card_dev,
					     instance_cfg->num_streams_cap,
					     sizeof(struct xen_snd_front_pcm_stream_info),
					     GFP_KERNEL);
		if (!pcm_instance_info->streams_cap)
			return -ENOMEM;
	}

	pcm_instance_info->num_pcm_streams_pb =
			instance_cfg->num_streams_pb;
	pcm_instance_info->num_pcm_streams_cap =
			instance_cfg->num_streams_cap;

	for (i = 0; i < pcm_instance_info->num_pcm_streams_pb; i++) {
		pcm_instance_info->streams_pb[i].pcm_hw =
			instance_cfg->streams_pb[i].pcm_hw;
		pcm_instance_info->streams_pb[i].index =
			instance_cfg->streams_pb[i].index;
	}

	for (i = 0; i < pcm_instance_info->num_pcm_streams_cap; i++) {
		pcm_instance_info->streams_cap[i].pcm_hw =
			instance_cfg->streams_cap[i].pcm_hw;
		pcm_instance_info->streams_cap[i].index =
			instance_cfg->streams_cap[i].index;
	}

	ret = snd_pcm_new(card_info->card, instance_cfg->name,
			  instance_cfg->device_id,
			  instance_cfg->num_streams_pb,
			  instance_cfg->num_streams_cap,
			  &pcm);
	if (ret < 0)
		return ret;

	pcm->private_data = pcm_instance_info;
	pcm->info_flags = 0;
	/* we want to handle all PCM operations in non-atomic context */
	pcm->nonatomic = true;
	strncpy(pcm->name, "Virtual card PCM", sizeof(pcm->name));

	if (instance_cfg->num_streams_pb)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_drv_alsa_playback_ops);

	if (instance_cfg->num_streams_cap)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_drv_alsa_capture_ops);

	pcm_instance_info->pcm = pcm;
	return 0;
}