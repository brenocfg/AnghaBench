#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct snd_pcm_substream {TYPE_2__ dma_buffer; TYPE_1__* runtime; } ;
struct lx_stream {unsigned int is_capture; scalar_t__ frame_pos; int /*<<< orphan*/  status; struct snd_pcm_substream* stream; } ;
struct lx6464es {TYPE_3__* card; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int channels; int period_size; int periods; } ;

/* Variables and functions */
 int /*<<< orphan*/  LX_STREAM_STATUS_RUNNING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int lx_buffer_ask (struct lx6464es*,int /*<<< orphan*/ ,unsigned int const,int*,int*,int*) ; 
 int lx_buffer_give (struct lx6464es*,int /*<<< orphan*/ ,unsigned int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int lx_stream_start (struct lx6464es*,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void lx_trigger_start(struct lx6464es *chip, struct lx_stream *lx_stream)
{
	struct snd_pcm_substream *substream = lx_stream->stream;
	const unsigned int is_capture = lx_stream->is_capture;

	int err;

	const u32 channels = substream->runtime->channels;
	const u32 bytes_per_frame = channels * 3;
	const u32 period_size = substream->runtime->period_size;
	const u32 periods = substream->runtime->periods;
	const u32 period_bytes = period_size * bytes_per_frame;

	dma_addr_t buf = substream->dma_buffer.addr;
	int i;

	u32 needed, freed;
	u32 size_array[5];

	for (i = 0; i != periods; ++i) {
		u32 buffer_index = 0;

		err = lx_buffer_ask(chip, 0, is_capture, &needed, &freed,
				    size_array);
		dev_dbg(chip->card->dev, "starting: needed %d, freed %d\n",
			    needed, freed);

		err = lx_buffer_give(chip, 0, is_capture, period_bytes,
				     lower_32_bits(buf), upper_32_bits(buf),
				     &buffer_index);

		dev_dbg(chip->card->dev, "starting: buffer index %x on 0x%lx (%d bytes)\n",
			    buffer_index, (unsigned long)buf, period_bytes);
		buf += period_bytes;
	}

	err = lx_buffer_ask(chip, 0, is_capture, &needed, &freed, size_array);
	dev_dbg(chip->card->dev, "starting: needed %d, freed %d\n", needed, freed);

	dev_dbg(chip->card->dev, "starting: starting stream\n");
	err = lx_stream_start(chip, 0, is_capture);
	if (err < 0)
		dev_err(chip->card->dev, "couldn't start stream\n");
	else
		lx_stream->status = LX_STREAM_STATUS_RUNNING;

	lx_stream->frame_pos = 0;
}