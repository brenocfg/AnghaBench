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
struct snd_gus_card {int /*<<< orphan*/ * pcm_cap_substream; scalar_t__ c_period_size; int /*<<< orphan*/  c_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_GB_REC_DMA_CONTROL ; 
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_START ; 
 int /*<<< orphan*/  snd_gf1_i_look8 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_i_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_pcm_capture_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_gf1_pcm_capture_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_gf1_pcm_interrupt_dma_read(struct snd_gus_card * gus)
{
	snd_gf1_i_write8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL, 0);	/* disable sampling */
	snd_gf1_i_look8(gus, SNDRV_GF1_GB_REC_DMA_CONTROL);	/* Sampling Control Register */
	if (gus->pcm_cap_substream != NULL) {
		snd_gf1_pcm_capture_prepare(gus->pcm_cap_substream); 
		snd_gf1_pcm_capture_trigger(gus->pcm_cap_substream, SNDRV_PCM_TRIGGER_START);
		gus->c_pos += gus->c_period_size;
		snd_pcm_period_elapsed(gus->pcm_cap_substream);
	}
}