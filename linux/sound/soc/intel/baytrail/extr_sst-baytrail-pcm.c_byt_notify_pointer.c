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
struct sst_byt_stream {int dummy; } ;
struct sst_byt_priv_data {struct sst_byt* byt; } ;
struct sst_byt_pcm_data {int /*<<< orphan*/  hw_ptr; int /*<<< orphan*/  stream; struct snd_pcm_substream* substream; } ;
struct sst_byt {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int buffer_size; TYPE_1__* control; } ;
struct TYPE_2__ {int appl_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 struct sst_byt_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_byt_get_dsp_position (struct sst_byt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 byt_notify_pointer(struct sst_byt_stream *stream, void *data)
{
	struct sst_byt_pcm_data *pcm_data = data;
	struct snd_pcm_substream *substream = pcm_data->substream;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct sst_byt_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct sst_byt *byt = pdata->byt;
	u32 pos, hw_pos;

	hw_pos = sst_byt_get_dsp_position(byt, pcm_data->stream,
					  snd_pcm_lib_buffer_bytes(substream));
	pcm_data->hw_ptr = hw_pos;
	pos = frames_to_bytes(runtime,
			      (runtime->control->appl_ptr %
			       runtime->buffer_size));

	dev_dbg(rtd->dev, "PCM: App/DMA pointer %u/%u bytes\n", pos, hw_pos);

	snd_pcm_period_elapsed(substream);
	return pos;
}