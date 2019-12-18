#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_3__* card; TYPE_4__* pcm; } ;
struct TYPE_6__ {int /*<<< orphan*/  channels_max; } ;
struct snd_soc_dai_driver {TYPE_1__ playback; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; struct snd_soc_dai_driver* driver; } ;
struct snd_kcontrol_new {int access; char* name; int /*<<< orphan*/  device; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  iface; } ;
struct snd_kcontrol {int dummy; } ;
struct hdmi_codec_priv {int /*<<< orphan*/  chmap_idx; TYPE_5__* chmap_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  chmap; TYPE_2__* kctl; struct hdmi_codec_priv* private_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  device; } ;
struct TYPE_8__ {int /*<<< orphan*/  snd_card; } ;
struct TYPE_7__ {int /*<<< orphan*/  get; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HDMI_CODEC_CHMAP_IDX_UNKNOWN ; 
 int SNDRV_CTL_ELEM_ACCESS_READ ; 
 int SNDRV_CTL_ELEM_ACCESS_VOLATILE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_PCM ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  hdmi_codec_chmap_ctl_get ; 
 int /*<<< orphan*/  hdmi_codec_stereo_chmaps ; 
 int /*<<< orphan*/  hdmi_eld_ctl_get ; 
 int /*<<< orphan*/  hdmi_eld_ctl_info ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,int /*<<< orphan*/ ) ; 
 int snd_pcm_add_chmap_ctls (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__**) ; 
 struct hdmi_codec_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int hdmi_codec_pcm_new(struct snd_soc_pcm_runtime *rtd,
			      struct snd_soc_dai *dai)
{
	struct snd_soc_dai_driver *drv = dai->driver;
	struct hdmi_codec_priv *hcp = snd_soc_dai_get_drvdata(dai);
	struct snd_kcontrol *kctl;
	struct snd_kcontrol_new hdmi_eld_ctl = {
		.access	= SNDRV_CTL_ELEM_ACCESS_READ |
			  SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.iface	= SNDRV_CTL_ELEM_IFACE_PCM,
		.name	= "ELD",
		.info	= hdmi_eld_ctl_info,
		.get	= hdmi_eld_ctl_get,
		.device	= rtd->pcm->device,
	};
	int ret;

	ret =  snd_pcm_add_chmap_ctls(rtd->pcm, SNDRV_PCM_STREAM_PLAYBACK,
				      NULL, drv->playback.channels_max, 0,
				      &hcp->chmap_info);
	if (ret < 0)
		return ret;

	/* override handlers */
	hcp->chmap_info->private_data = hcp;
	hcp->chmap_info->kctl->get = hdmi_codec_chmap_ctl_get;

	/* default chmap supported is stereo */
	hcp->chmap_info->chmap = hdmi_codec_stereo_chmaps;
	hcp->chmap_idx = HDMI_CODEC_CHMAP_IDX_UNKNOWN;

	/* add ELD ctl with the device number corresponding to the PCM stream */
	kctl = snd_ctl_new1(&hdmi_eld_ctl, dai->component);
	if (!kctl)
		return -ENOMEM;

	return snd_ctl_add(rtd->card->snd_card, kctl);
}