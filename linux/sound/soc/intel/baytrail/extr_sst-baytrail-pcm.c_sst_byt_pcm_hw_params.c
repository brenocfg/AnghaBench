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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct sst_byt_priv_data {struct sst_byt* byt; struct sst_byt_pcm_data* pcm; } ;
struct sst_byt_pcm_data {int /*<<< orphan*/  stream; } ;
struct sst_byt {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct snd_pcm_substream {size_t stream; TYPE_1__ dma_buffer; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct sst_byt_pcm_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct sst_byt_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int sst_byt_stream_buffer (struct sst_byt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sst_byt_stream_commit (struct sst_byt*,int /*<<< orphan*/ ) ; 
 int sst_byt_stream_set_bits (struct sst_byt*,int /*<<< orphan*/ ,int) ; 
 int sst_byt_stream_set_channels (struct sst_byt*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sst_byt_stream_set_rate (struct sst_byt*,int /*<<< orphan*/ ,int) ; 
 int sst_byt_stream_type (struct sst_byt*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int sst_byt_pcm_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct sst_byt_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct sst_byt_pcm_data *pcm_data = &pdata->pcm[substream->stream];
	struct sst_byt *byt = pdata->byt;
	u32 rate, bits;
	u8 channels;
	int ret, playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);

	dev_dbg(rtd->dev, "PCM: hw_params, pcm_data %p\n", pcm_data);

	ret = sst_byt_stream_type(byt, pcm_data->stream,
				  1, 1, !playback);
	if (ret < 0) {
		dev_err(rtd->dev, "failed to set stream format %d\n", ret);
		return ret;
	}

	rate = params_rate(params);
	ret = sst_byt_stream_set_rate(byt, pcm_data->stream, rate);
	if (ret < 0) {
		dev_err(rtd->dev, "could not set rate %d\n", rate);
		return ret;
	}

	bits = snd_pcm_format_width(params_format(params));
	ret = sst_byt_stream_set_bits(byt, pcm_data->stream, bits);
	if (ret < 0) {
		dev_err(rtd->dev, "could not set formats %d\n",
			params_rate(params));
		return ret;
	}

	channels = (u8)(params_channels(params) & 0xF);
	ret = sst_byt_stream_set_channels(byt, pcm_data->stream, channels);
	if (ret < 0) {
		dev_err(rtd->dev, "could not set channels %d\n",
			params_rate(params));
		return ret;
	}

	snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(params));

	ret = sst_byt_stream_buffer(byt, pcm_data->stream,
				    substream->dma_buffer.addr,
				    params_buffer_bytes(params));
	if (ret < 0) {
		dev_err(rtd->dev, "PCM: failed to set DMA buffer %d\n", ret);
		return ret;
	}

	ret = sst_byt_stream_commit(byt, pcm_data->stream);
	if (ret < 0) {
		dev_err(rtd->dev, "PCM: failed stream commit %d\n", ret);
		return ret;
	}

	return 0;
}