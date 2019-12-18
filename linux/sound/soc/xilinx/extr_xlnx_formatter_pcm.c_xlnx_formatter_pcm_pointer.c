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
typedef  scalar_t__ u32 ;
struct xlnx_pcm_stream_param {scalar_t__ buffer_size; scalar_t__ mmio; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct xlnx_pcm_stream_param* private_data; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ XLNX_AUD_XFER_COUNT ; 
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,scalar_t__) ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static snd_pcm_uframes_t
xlnx_formatter_pcm_pointer(struct snd_pcm_substream *substream)
{
	u32 pos;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct xlnx_pcm_stream_param *stream_data = runtime->private_data;

	pos = readl(stream_data->mmio + XLNX_AUD_XFER_COUNT);

	if (pos >= stream_data->buffer_size)
		pos = 0;

	return bytes_to_frames(runtime, pos);
}