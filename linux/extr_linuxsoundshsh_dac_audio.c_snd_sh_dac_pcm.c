#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_sh_dac {int /*<<< orphan*/  card; } ;
struct snd_pcm {int /*<<< orphan*/  name; struct snd_sh_dac* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_dma_continuous_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_sh_dac_pcm_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_sh_dac_pcm(struct snd_sh_dac *chip, int device)
{
	int err;
	struct snd_pcm *pcm;

	/* device should be always 0 for us */
	err = snd_pcm_new(chip->card, "SH_DAC PCM", device, 1, 0, &pcm);
	if (err < 0)
		return err;

	pcm->private_data = chip;
	strcpy(pcm->name, "SH_DAC PCM");
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_sh_dac_pcm_ops);

	/* buffer size=48K */
	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
					  snd_dma_continuous_data(GFP_KERNEL),
							48 * 1024,
							48 * 1024);

	return 0;
}