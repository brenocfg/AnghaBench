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
struct snd_pcm {int /*<<< orphan*/  name; scalar_t__ info_flags; struct snd_ice1712* private_data; } ;
struct TYPE_2__ {int* data; } ;
struct snd_ice1712 {int has_spdif; struct snd_pcm* pcm; int /*<<< orphan*/  pci; int /*<<< orphan*/  card; scalar_t__ force_rdma1; scalar_t__ force_pdma4; TYPE_1__ eeprom; } ;

/* Variables and functions */
 size_t ICE_EEP2_SPDIF ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int VT1724_CFG_SPDIF_IN ; 
 int VT1724_CFG_SPDIF_OUT_INT ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_vt1724_capture_spdif_ops ; 
 int /*<<< orphan*/  snd_vt1724_playback_spdif_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_vt1724_pcm_spdif(struct snd_ice1712 *ice, int device)
{
	char *name;
	struct snd_pcm *pcm;
	int play, capt;
	int err;

	if (ice->force_pdma4 ||
	    (ice->eeprom.data[ICE_EEP2_SPDIF] & VT1724_CFG_SPDIF_OUT_INT)) {
		play = 1;
		ice->has_spdif = 1;
	} else
		play = 0;
	if (ice->force_rdma1 ||
	    (ice->eeprom.data[ICE_EEP2_SPDIF] & VT1724_CFG_SPDIF_IN)) {
		capt = 1;
		ice->has_spdif = 1;
	} else
		capt = 0;
	if (!play && !capt)
		return 0; /* no spdif device */

	if (ice->force_pdma4 || ice->force_rdma1)
		name = "ICE1724 Secondary";
	else
		name = "ICE1724 IEC958";
	err = snd_pcm_new(ice->card, name, device, play, capt, &pcm);
	if (err < 0)
		return err;

	if (play)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_vt1724_playback_spdif_ops);
	if (capt)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_vt1724_capture_spdif_ops);

	pcm->private_data = ice;
	pcm->info_flags = 0;
	strcpy(pcm->name, name);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(ice->pci),
					      256*1024, 256*1024);

	ice->pcm = pcm;

	return 0;
}