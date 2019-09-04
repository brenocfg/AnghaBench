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
struct snd_pcm {TYPE_1__* streams; int /*<<< orphan*/  name; scalar_t__ info_flags; struct snd_ice1712* private_data; } ;
struct snd_ice1712 {scalar_t__ cs8427; struct snd_pcm* pcm_pro; int /*<<< orphan*/  pci; int /*<<< orphan*/  card; } ;
struct TYPE_2__ {int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int snd_cs8427_iec958_build (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int snd_ice1712_build_pro_mixer (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_capture_pro_ops ; 
 int /*<<< orphan*/  snd_ice1712_playback_pro_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_ice1712_pcm_profi(struct snd_ice1712 *ice, int device)
{
	struct snd_pcm *pcm;
	int err;

	err = snd_pcm_new(ice->card, "ICE1712 multi", device, 1, 1, &pcm);
	if (err < 0)
		return err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ice1712_playback_pro_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ice1712_capture_pro_ops);

	pcm->private_data = ice;
	pcm->info_flags = 0;
	strcpy(pcm->name, "ICE1712 multi");

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(ice->pci), 256*1024, 256*1024);

	ice->pcm_pro = pcm;

	if (ice->cs8427) {
		/* assign channels to iec958 */
		err = snd_cs8427_iec958_build(ice->cs8427,
					      pcm->streams[0].substream,
					      pcm->streams[1].substream);
		if (err < 0)
			return err;
	}

	return snd_ice1712_build_pro_mixer(ice);
}