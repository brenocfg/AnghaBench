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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  dma_chan ;

/* Variables and functions */
 int /*<<< orphan*/  MASTERCONTROL ; 
 int /*<<< orphan*/  MASTERCONTROL_ALLOC_DMA_CHAN ; 
 int /*<<< orphan*/  SCP_SET ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,...) ; 
 int dspio_scp (struct hda_codec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int dspio_free_dma_chan(struct hda_codec *codec, unsigned int dma_chan)
{
	int status = 0;
	unsigned int dummy = 0;

	codec_dbg(codec, "     dspio_free_dma_chan() -- begin\n");
	codec_dbg(codec, "dspio_free_dma_chan: chan=%d\n", dma_chan);

	status = dspio_scp(codec, MASTERCONTROL, 0x20,
			MASTERCONTROL_ALLOC_DMA_CHAN, SCP_SET, &dma_chan,
			sizeof(dma_chan), NULL, &dummy);

	if (status < 0) {
		codec_dbg(codec, "dspio_free_dma_chan: SCP Failed\n");
		return status;
	}

	codec_dbg(codec, "     dspio_free_dma_chan() -- complete\n");

	return status;
}