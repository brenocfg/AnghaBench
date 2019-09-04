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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct snd_pcm {int /*<<< orphan*/  name; scalar_t__ info_flags; struct snd_card_asihpi* private_data; } ;
struct snd_card_asihpi {int /*<<< orphan*/  pci; int /*<<< orphan*/  card; TYPE_2__* hpi; } ;
struct TYPE_4__ {TYPE_1__* adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_BYTES_MAX ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int hpi_adapter_get_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_asihpi_capture_mmap_ops ; 
 int /*<<< orphan*/  snd_card_asihpi_playback_mmap_ops ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_card_asihpi_pcm_new(struct snd_card_asihpi *asihpi, int device)
{
	struct snd_pcm *pcm;
	int err;
	u16 num_instreams, num_outstreams, x16;
	u32 x32;

	err = hpi_adapter_get_info(asihpi->hpi->adapter->index,
			&num_outstreams, &num_instreams,
			&x16, &x32, &x16);

	err = snd_pcm_new(asihpi->card, "Asihpi PCM", device,
			num_outstreams,	num_instreams, &pcm);
	if (err < 0)
		return err;

	/* pointer to ops struct is stored, dont change ops afterwards! */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_card_asihpi_playback_mmap_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_card_asihpi_capture_mmap_ops);

	pcm->private_data = asihpi;
	pcm->info_flags = 0;
	strcpy(pcm->name, "Asihpi PCM");

	/*? do we want to emulate MMAP for non-BBM cards?
	Jack doesn't work with ALSAs MMAP emulation - WHY NOT? */
	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
						snd_dma_pci_data(asihpi->pci),
						64*1024, BUFFER_BYTES_MAX);

	return 0;
}