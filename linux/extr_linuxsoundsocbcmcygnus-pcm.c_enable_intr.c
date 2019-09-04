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
typedef  int /*<<< orphan*/  u32 ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct cygnus_aio_port {TYPE_1__* cygaud; int /*<<< orphan*/  portnum; } ;
struct TYPE_2__ {scalar_t__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANY_CAPTURE_IRQ ; 
 int /*<<< orphan*/  ANY_PLAYBACK_IRQ ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ ESR0_MASK_CLR_OFFSET ; 
 scalar_t__ ESR0_STATUS_CLR_OFFSET ; 
 scalar_t__ ESR1_MASK_CLR_OFFSET ; 
 scalar_t__ ESR1_STATUS_CLR_OFFSET ; 
 scalar_t__ ESR2_MASK_CLR_OFFSET ; 
 scalar_t__ ESR2_STATUS_CLR_OFFSET ; 
 scalar_t__ ESR3_MASK_CLR_OFFSET ; 
 scalar_t__ ESR3_STATUS_CLR_OFFSET ; 
 scalar_t__ ESR4_MASK_CLR_OFFSET ; 
 scalar_t__ ESR4_STATUS_CLR_OFFSET ; 
 scalar_t__ INTH_R5F_MASK_CLEAR_OFFSET ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 struct cygnus_aio_port* cygnus_dai_get_dma_data (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void enable_intr(struct snd_pcm_substream *substream)
{
	struct cygnus_aio_port *aio;
	u32 clear_mask;

	aio = cygnus_dai_get_dma_data(substream);

	/* The port number maps to the bit position to be cleared */
	clear_mask = BIT(aio->portnum);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		/* Clear interrupt status before enabling them */
		writel(clear_mask, aio->cygaud->audio + ESR0_STATUS_CLR_OFFSET);
		writel(clear_mask, aio->cygaud->audio + ESR1_STATUS_CLR_OFFSET);
		writel(clear_mask, aio->cygaud->audio + ESR3_STATUS_CLR_OFFSET);
		/* Unmask the interrupts of the given port*/
		writel(clear_mask, aio->cygaud->audio + ESR0_MASK_CLR_OFFSET);
		writel(clear_mask, aio->cygaud->audio + ESR1_MASK_CLR_OFFSET);
		writel(clear_mask, aio->cygaud->audio + ESR3_MASK_CLR_OFFSET);

		writel(ANY_PLAYBACK_IRQ,
			aio->cygaud->audio + INTH_R5F_MASK_CLEAR_OFFSET);
	} else {
		writel(clear_mask, aio->cygaud->audio + ESR2_STATUS_CLR_OFFSET);
		writel(clear_mask, aio->cygaud->audio + ESR4_STATUS_CLR_OFFSET);
		writel(clear_mask, aio->cygaud->audio + ESR2_MASK_CLR_OFFSET);
		writel(clear_mask, aio->cygaud->audio + ESR4_MASK_CLR_OFFSET);

		writel(ANY_CAPTURE_IRQ,
			aio->cygaud->audio + INTH_R5F_MASK_CLEAR_OFFSET);
	}

}