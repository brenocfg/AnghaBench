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
struct snd_pcm_chmap_elem {int dummy; } ;
struct snd_pcm {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_subclass; scalar_t__ info_flags; struct ct_atc* private_data; } ;
struct ct_atc {struct snd_pcm** pcms; int /*<<< orphan*/  pci; TYPE_1__* card; } ;
typedef  enum CTALSADEVS { ____Placeholder_CTALSADEVS } CTALSADEVS ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CLFE 131 
#define  FRONT 130 
 int IEC958 ; 
#define  SIDE 129 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_SG ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_PCM_SUBCLASS_GENERIC_MIX ; 
#define  SURROUND 128 
 struct snd_pcm_chmap_elem* clfe_map ; 
 int /*<<< orphan*/  ct_pcm_capture_ops ; 
 int /*<<< orphan*/  ct_pcm_playback_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct snd_pcm_chmap_elem* side_map ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int snd_pcm_add_chmap_ctls (struct snd_pcm*,int /*<<< orphan*/ ,struct snd_pcm_chmap_elem const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (TYPE_1__*,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_pcm_chmap_elem* snd_pcm_std_chmaps ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 struct snd_pcm_chmap_elem* surround_map ; 

int ct_alsa_pcm_create(struct ct_atc *atc,
		       enum CTALSADEVS device,
		       const char *device_name)
{
	struct snd_pcm *pcm;
	const struct snd_pcm_chmap_elem *map;
	int chs;
	int err;
	int playback_count, capture_count;

	playback_count = (IEC958 == device) ? 1 : 256;
	capture_count = (FRONT == device) ? 1 : 0;
	err = snd_pcm_new(atc->card, "ctxfi", device,
			  playback_count, capture_count, &pcm);
	if (err < 0) {
		dev_err(atc->card->dev, "snd_pcm_new failed!! Err=%d\n",
			err);
		return err;
	}

	pcm->private_data = atc;
	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	strlcpy(pcm->name, device_name, sizeof(pcm->name));

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &ct_pcm_playback_ops);

	if (FRONT == device)
		snd_pcm_set_ops(pcm,
				SNDRV_PCM_STREAM_CAPTURE, &ct_pcm_capture_ops);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
			snd_dma_pci_data(atc->pci), 128*1024, 128*1024);

	chs = 2;
	switch (device) {
	case FRONT:
		chs = 8;
		map = snd_pcm_std_chmaps;
		break;
	case SURROUND:
		map = surround_map;
		break;
	case CLFE:
		map = clfe_map;
		break;
	case SIDE:
		map = side_map;
		break;
	default:
		map = snd_pcm_std_chmaps;
		break;
	}
	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK, map, chs,
				     0, NULL);
	if (err < 0)
		return err;

#ifdef CONFIG_PM_SLEEP
	atc->pcms[device] = pcm;
#endif

	return 0;
}