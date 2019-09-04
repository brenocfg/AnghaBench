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
struct sst_hsw_stream {int dummy; } ;
struct sst_hsw {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned char* dma_area; int buffer_size; int /*<<< orphan*/  format; TYPE_1__* control; int /*<<< orphan*/  dma_bytes; } ;
struct hsw_priv_data {struct sst_hsw* hsw; } ;
struct hsw_pcm_data {int /*<<< orphan*/  stream; struct snd_pcm_substream* substream; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ snd_pcm_uframes_t ;
struct TYPE_2__ {int appl_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 unsigned char* SST_OLD_POSITION (unsigned char*,struct snd_pcm_runtime*,scalar_t__) ; 
 int /*<<< orphan*/  SST_SAMPLES (struct snd_pcm_runtime*,scalar_t__) ; 
 scalar_t__ bytes_to_frames (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int /*<<< orphan*/  snd_pcm_format_set_silence (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 struct hsw_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_hsw_get_dsp_position (struct sst_hsw*,int /*<<< orphan*/ ) ; 
 scalar_t__ sst_hsw_stream_get_old_position (struct sst_hsw*,struct sst_hsw_stream*) ; 
 int /*<<< orphan*/  sst_hsw_stream_get_silence_start (struct sst_hsw*,struct sst_hsw_stream*) ; 
 int /*<<< orphan*/  sst_hsw_stream_set_old_position (struct sst_hsw*,struct sst_hsw_stream*,scalar_t__) ; 

__attribute__((used)) static u32 hsw_notify_pointer(struct sst_hsw_stream *stream, void *data)
{
	struct hsw_pcm_data *pcm_data = data;
	struct snd_pcm_substream *substream = pcm_data->substream;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct hsw_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct sst_hsw *hsw = pdata->hsw;
	u32 pos;
	snd_pcm_uframes_t position = bytes_to_frames(runtime,
		 sst_hsw_get_dsp_position(hsw, pcm_data->stream));
	unsigned char *dma_area = runtime->dma_area;
	snd_pcm_uframes_t dma_frames =
		bytes_to_frames(runtime, runtime->dma_bytes);
	snd_pcm_uframes_t old_position;
	ssize_t samples;

	pos = frames_to_bytes(runtime,
		(runtime->control->appl_ptr % runtime->buffer_size));

	dev_vdbg(rtd->dev, "PCM: App pointer %d bytes\n", pos);

	/* SST fw don't know where to stop dma
	 * So, SST driver need to clean the data which has been consumed
	 */
	if (dma_area == NULL || dma_frames <= 0
		|| (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		|| !sst_hsw_stream_get_silence_start(hsw, stream)) {
		snd_pcm_period_elapsed(substream);
		return pos;
	}

	old_position = sst_hsw_stream_get_old_position(hsw, stream);
	if (position > old_position) {
		if (position < dma_frames) {
			samples = SST_SAMPLES(runtime, position - old_position);
			snd_pcm_format_set_silence(runtime->format,
				SST_OLD_POSITION(dma_area,
					runtime, old_position),
				samples);
		} else
			dev_err(rtd->dev, "PCM: position is wrong\n");
	} else {
		if (old_position < dma_frames) {
			samples = SST_SAMPLES(runtime,
				dma_frames - old_position);
			snd_pcm_format_set_silence(runtime->format,
				SST_OLD_POSITION(dma_area,
					runtime, old_position),
				samples);
		} else
			dev_err(rtd->dev, "PCM: dma_bytes is wrong\n");
		if (position < dma_frames) {
			samples = SST_SAMPLES(runtime, position);
			snd_pcm_format_set_silence(runtime->format,
				dma_area, samples);
		} else
			dev_err(rtd->dev, "PCM: position is wrong\n");
	}
	sst_hsw_stream_set_old_position(hsw, stream, position);

	/* let alsa know we have play a period */
	snd_pcm_period_elapsed(substream);
	return pos;
}