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
struct snd_ice1712 {struct snd_pcm* pcm_pro; int /*<<< orphan*/  pci; int /*<<< orphan*/  card; TYPE_1__ eeprom; } ;

/* Variables and functions */
 size_t ICE_EEP2_SYSCONF ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int VT1724_CFG_ADC_MASK ; 
 int VT1724_CFG_ADC_NONE ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_vt1724_capture_pro_ops ; 
 int /*<<< orphan*/  snd_vt1724_playback_pro_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_vt1724_pcm_profi(struct snd_ice1712 *ice, int device)
{
	struct snd_pcm *pcm;
	int capt, err;

	if ((ice->eeprom.data[ICE_EEP2_SYSCONF] & VT1724_CFG_ADC_MASK) ==
	    VT1724_CFG_ADC_NONE)
		capt = 0;
	else
		capt = 1;
	err = snd_pcm_new(ice->card, "ICE1724", device, 1, capt, &pcm);
	if (err < 0)
		return err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_vt1724_playback_pro_ops);
	if (capt)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_vt1724_capture_pro_ops);

	pcm->private_data = ice;
	pcm->info_flags = 0;
	strcpy(pcm->name, "ICE1724");

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(ice->pci),
					      256*1024, 256*1024);

	ice->pcm_pro = pcm;

	return 0;
}