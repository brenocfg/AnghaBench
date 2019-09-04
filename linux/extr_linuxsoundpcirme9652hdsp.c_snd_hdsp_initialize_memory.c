#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long area; unsigned long addr; } ;
struct hdsp {unsigned long capture_buffer; unsigned long playback_buffer; TYPE_2__ playback_dma_buf; TYPE_2__ capture_dma_buf; int /*<<< orphan*/  card_name; TYPE_1__* card; int /*<<< orphan*/  pci; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HDSP_DMA_AREA_BYTES ; 
 int /*<<< orphan*/  HDSP_inputBufferAddress ; 
 int /*<<< orphan*/  HDSP_outputBufferAddress ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_2__*) ; 
 scalar_t__ snd_hammerfall_get_buffer (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_hdsp_initialize_memory(struct hdsp *hdsp)
{
	unsigned long pb_bus, cb_bus;

	if (snd_hammerfall_get_buffer(hdsp->pci, &hdsp->capture_dma_buf, HDSP_DMA_AREA_BYTES) < 0 ||
	    snd_hammerfall_get_buffer(hdsp->pci, &hdsp->playback_dma_buf, HDSP_DMA_AREA_BYTES) < 0) {
		if (hdsp->capture_dma_buf.area)
			snd_dma_free_pages(&hdsp->capture_dma_buf);
		dev_err(hdsp->card->dev,
			"%s: no buffers available\n", hdsp->card_name);
		return -ENOMEM;
	}

	/* Align to bus-space 64K boundary */

	cb_bus = ALIGN(hdsp->capture_dma_buf.addr, 0x10000ul);
	pb_bus = ALIGN(hdsp->playback_dma_buf.addr, 0x10000ul);

	/* Tell the card where it is */

	hdsp_write(hdsp, HDSP_inputBufferAddress, cb_bus);
	hdsp_write(hdsp, HDSP_outputBufferAddress, pb_bus);

	hdsp->capture_buffer = hdsp->capture_dma_buf.area + (cb_bus - hdsp->capture_dma_buf.addr);
	hdsp->playback_buffer = hdsp->playback_dma_buf.area + (pb_bus - hdsp->playback_dma_buf.addr);

	return 0;
}