#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct snd_pcm_substream {TYPE_1__* runtime; int /*<<< orphan*/  stream; } ;
struct i2s_stream_instance {scalar_t__ bytescount; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_3__ {int /*<<< orphan*/  buffer_size; struct i2s_stream_instance* private_data; } ;

/* Variables and functions */
 scalar_t__ acp_get_byte_count (struct i2s_stream_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytes_to_frames (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frames_to_bytes (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t acp3x_dma_pointer(struct snd_pcm_substream *substream)
{
	u32 pos = 0;
	u32 buffersize = 0;
	u64 bytescount = 0;
	struct i2s_stream_instance *rtd =
		substream->runtime->private_data;

	buffersize = frames_to_bytes(substream->runtime,
				     substream->runtime->buffer_size);
	bytescount = acp_get_byte_count(rtd, substream->stream);
	if (bytescount > rtd->bytescount)
		bytescount -= rtd->bytescount;
	pos = do_div(bytescount, buffersize);
	return bytes_to_frames(substream->runtime, pos);
}