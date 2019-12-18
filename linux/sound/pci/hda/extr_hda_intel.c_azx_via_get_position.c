#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int period_bytes; unsigned int bufsize; int /*<<< orphan*/ * posbuf; TYPE_1__* substream; } ;
struct azx_dev {TYPE_2__ core; scalar_t__ insufficient; } ;
struct azx {int dummy; } ;
struct TYPE_7__ {int fifo_size; } ;
struct TYPE_5__ {scalar_t__ stream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_3__* azx_stream (struct azx_dev*) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int snd_hdac_stream_get_pos_lpib (TYPE_3__*) ; 

__attribute__((used)) static unsigned int azx_via_get_position(struct azx *chip,
					 struct azx_dev *azx_dev)
{
	unsigned int link_pos, mini_pos, bound_pos;
	unsigned int mod_link_pos, mod_dma_pos, mod_mini_pos;
	unsigned int fifo_size;

	link_pos = snd_hdac_stream_get_pos_lpib(azx_stream(azx_dev));
	if (azx_dev->core.substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		/* Playback, no problem using link position */
		return link_pos;
	}

	/* Capture */
	/* For new chipset,
	 * use mod to get the DMA position just like old chipset
	 */
	mod_dma_pos = le32_to_cpu(*azx_dev->core.posbuf);
	mod_dma_pos %= azx_dev->core.period_bytes;

	fifo_size = azx_stream(azx_dev)->fifo_size - 1;

	if (azx_dev->insufficient) {
		/* Link position never gather than FIFO size */
		if (link_pos <= fifo_size)
			return 0;

		azx_dev->insufficient = 0;
	}

	if (link_pos <= fifo_size)
		mini_pos = azx_dev->core.bufsize + link_pos - fifo_size;
	else
		mini_pos = link_pos - fifo_size;

	/* Find nearest previous boudary */
	mod_mini_pos = mini_pos % azx_dev->core.period_bytes;
	mod_link_pos = link_pos % azx_dev->core.period_bytes;
	if (mod_link_pos >= fifo_size)
		bound_pos = link_pos - mod_link_pos;
	else if (mod_dma_pos >= mod_mini_pos)
		bound_pos = mini_pos - mod_mini_pos;
	else {
		bound_pos = mini_pos - mod_mini_pos + azx_dev->core.period_bytes;
		if (bound_pos >= azx_dev->core.bufsize)
			bound_pos = 0;
	}

	/* Calculate real DMA position we want */
	return bound_pos + mod_dma_pos;
}