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
struct lx_stream {unsigned int is_capture; int frame_pos; struct snd_pcm_substream* stream; } ;
struct lx6464es {int /*<<< orphan*/  lock; TYPE_3__* card; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int channels; int period_size; int const periods; } ;

/* Variables and functions */
 int MAX_STREAM_BUFFER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int lx_buffer_ask (struct lx6464es*,int /*<<< orphan*/ ,unsigned int const,int*,int*,int*) ; 
 int lx_buffer_give (struct lx6464es*,int /*<<< orphan*/ ,unsigned int const,int const,int,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpack_pointer (scalar_t__,int*,int*) ; 

__attribute__((used)) static int lx_interrupt_request_new_buffer(struct lx6464es *chip,
					   struct lx_stream *lx_stream)
{
	struct snd_pcm_substream *substream = lx_stream->stream;
	const unsigned int is_capture = lx_stream->is_capture;
	int err;

	const u32 channels = substream->runtime->channels;
	const u32 bytes_per_frame = channels * 3;
	const u32 period_size = substream->runtime->period_size;
	const u32 period_bytes = period_size * bytes_per_frame;
	const u32 pos = lx_stream->frame_pos;
	const u32 next_pos = ((pos+1) == substream->runtime->periods) ?
		0 : pos + 1;

	dma_addr_t buf = substream->dma_buffer.addr + pos * period_bytes;
	u32 buf_hi = 0;
	u32 buf_lo = 0;
	u32 buffer_index = 0;

	u32 needed, freed;
	u32 size_array[MAX_STREAM_BUFFER];

	dev_dbg(chip->card->dev, "->lx_interrupt_request_new_buffer\n");

	mutex_lock(&chip->lock);

	err = lx_buffer_ask(chip, 0, is_capture, &needed, &freed, size_array);
	dev_dbg(chip->card->dev,
		"interrupt: needed %d, freed %d\n", needed, freed);

	unpack_pointer(buf, &buf_lo, &buf_hi);
	err = lx_buffer_give(chip, 0, is_capture, period_bytes, buf_lo, buf_hi,
			     &buffer_index);
	dev_dbg(chip->card->dev,
		"interrupt: gave buffer index %x on 0x%lx (%d bytes)\n",
		    buffer_index, (unsigned long)buf, period_bytes);

	lx_stream->frame_pos = next_pos;
	mutex_unlock(&chip->lock);

	return err;
}