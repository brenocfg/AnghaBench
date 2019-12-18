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
typedef  int u8 ;
typedef  int u32 ;
struct sst_module {int dummy; } ;
struct sst_hsw {int dummy; } ;
struct sst_dsp {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; TYPE_2__* cpu_dai; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {int dma_bytes; int /*<<< orphan*/  dma_area; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_dma_buffer {int dummy; } ;
struct hsw_priv_data {TYPE_1__** dmab; struct hsw_pcm_data** pcm; struct sst_hsw* hsw; } ;
struct hsw_pcm_data {int allocated; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * volume; int /*<<< orphan*/  runtime; } ;
typedef  enum sst_hsw_stream_type { ____Placeholder_sst_hsw_stream_type } sst_hsw_stream_type ;
typedef  enum sst_hsw_stream_path_id { ____Placeholder_sst_hsw_stream_path_id } sst_hsw_stream_path_id ;
struct TYPE_6__ {int dai_id; } ;
struct TYPE_5__ {size_t id; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S24_LE 130 
#define  SNDRV_PCM_FORMAT_S32_LE 129 
#define  SNDRV_PCM_FORMAT_S8 128 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SST_HSW_CHANNEL_CONFIG_STEREO ; 
 int SST_HSW_DEPTH_16BIT ; 
 int SST_HSW_DEPTH_32BIT ; 
 int SST_HSW_DEPTH_8BIT ; 
 int /*<<< orphan*/  SST_HSW_INTERLEAVING_PER_CHANNEL ; 
 int SST_HSW_MODULE_PCM ; 
 int SST_HSW_MODULE_PCM_CAPTURE ; 
 int SST_HSW_MODULE_PCM_REFERENCE ; 
 int SST_HSW_MODULE_PCM_SYSTEM ; 
 int /*<<< orphan*/  SST_HSW_STREAM_FORMAT_PCM_FORMAT ; 
 int SST_HSW_STREAM_PATH_SSP0_IN ; 
 int SST_HSW_STREAM_PATH_SSP0_OUT ; 
 int SST_HSW_STREAM_TYPE_CAPTURE ; 
 int SST_HSW_STREAM_TYPE_LOOPBACK ; 
 int SST_HSW_STREAM_TYPE_RENDER ; 
 int SST_HSW_STREAM_TYPE_SYSTEM ; 
 int create_adsp_page_table (struct snd_pcm_substream*,struct hsw_priv_data*,struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ,int,size_t) ; 
 int create_channel_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hsw_notify_pointer ; 
 TYPE_3__* mod_map ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 struct snd_dma_buffer* snd_pcm_get_dma_buf (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int snd_sgbuf_get_addr (struct snd_dma_buffer*,int /*<<< orphan*/ ) ; 
 struct hsw_priv_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct sst_dsp* sst_hsw_get_dsp (struct sst_hsw*) ; 
 int sst_hsw_stream_buffer (struct sst_hsw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int sst_hsw_stream_commit (struct sst_hsw*,int /*<<< orphan*/ *) ; 
 int sst_hsw_stream_format (struct sst_hsw*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int sst_hsw_stream_free (struct sst_hsw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sst_hsw_stream_new (struct sst_hsw*,size_t,int /*<<< orphan*/ ,struct hsw_pcm_data*) ; 
 int sst_hsw_stream_pause (struct sst_hsw*,int /*<<< orphan*/ *,int) ; 
 int sst_hsw_stream_reset (struct sst_hsw*,int /*<<< orphan*/ *) ; 
 int sst_hsw_stream_set_bits (struct sst_hsw*,int /*<<< orphan*/ *,int) ; 
 int sst_hsw_stream_set_channels (struct sst_hsw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sst_hsw_stream_set_map_config (struct sst_hsw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_hsw_stream_set_module_info (struct sst_hsw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sst_hsw_stream_set_rate (struct sst_hsw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sst_hsw_stream_set_style (struct sst_hsw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_hsw_stream_set_valid (struct sst_hsw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sst_hsw_stream_set_volume (struct sst_hsw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sst_module* sst_module_get_from_id (struct sst_dsp*,int) ; 

__attribute__((used)) static int hsw_pcm_hw_params(struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct hsw_priv_data *pdata = snd_soc_component_get_drvdata(component);
	struct hsw_pcm_data *pcm_data;
	struct sst_hsw *hsw = pdata->hsw;
	struct sst_module *module_data;
	struct sst_dsp *dsp;
	struct snd_dma_buffer *dmab;
	enum sst_hsw_stream_type stream_type;
	enum sst_hsw_stream_path_id path_id;
	u32 rate, bits, map, pages, module_id;
	u8 channels;
	int ret, dai;

	dai = mod_map[rtd->cpu_dai->id].dai_id;
	pcm_data = &pdata->pcm[dai][substream->stream];

	/* check if we are being called a subsequent time */
	if (pcm_data->allocated) {
		ret = sst_hsw_stream_reset(hsw, pcm_data->stream);
		if (ret < 0)
			dev_dbg(rtd->dev, "error: reset stream failed %d\n",
				ret);

		ret = sst_hsw_stream_free(hsw, pcm_data->stream);
		if (ret < 0) {
			dev_dbg(rtd->dev, "error: free stream failed %d\n",
				ret);
			return ret;
		}
		pcm_data->allocated = false;

		pcm_data->stream = sst_hsw_stream_new(hsw, rtd->cpu_dai->id,
			hsw_notify_pointer, pcm_data);
		if (pcm_data->stream == NULL) {
			dev_err(rtd->dev, "error: failed to create stream\n");
			return -EINVAL;
		}
	}

	/* stream direction */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		path_id = SST_HSW_STREAM_PATH_SSP0_OUT;
	else
		path_id = SST_HSW_STREAM_PATH_SSP0_IN;

	/* DSP stream type depends on DAI ID */
	switch (rtd->cpu_dai->id) {
	case 0:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			stream_type = SST_HSW_STREAM_TYPE_SYSTEM;
			module_id = SST_HSW_MODULE_PCM_SYSTEM;
		}
		else {
			stream_type = SST_HSW_STREAM_TYPE_CAPTURE;
			module_id = SST_HSW_MODULE_PCM_CAPTURE;
		}
		break;
	case 1:
	case 2:
		stream_type = SST_HSW_STREAM_TYPE_RENDER;
		module_id = SST_HSW_MODULE_PCM;
		break;
	case 3:
		/* path ID needs to be OUT for loopback */
		stream_type = SST_HSW_STREAM_TYPE_LOOPBACK;
		path_id = SST_HSW_STREAM_PATH_SSP0_OUT;
		module_id = SST_HSW_MODULE_PCM_REFERENCE;
		break;
	default:
		dev_err(rtd->dev, "error: invalid DAI ID %d\n",
			rtd->cpu_dai->id);
		return -EINVAL;
	}

	ret = sst_hsw_stream_format(hsw, pcm_data->stream,
		path_id, stream_type, SST_HSW_STREAM_FORMAT_PCM_FORMAT);
	if (ret < 0) {
		dev_err(rtd->dev, "error: failed to set format %d\n", ret);
		return ret;
	}

	rate = params_rate(params);
	ret = sst_hsw_stream_set_rate(hsw, pcm_data->stream, rate);
	if (ret < 0) {
		dev_err(rtd->dev, "error: could not set rate %d\n", rate);
		return ret;
	}

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		bits = SST_HSW_DEPTH_16BIT;
		sst_hsw_stream_set_valid(hsw, pcm_data->stream, 16);
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		bits = SST_HSW_DEPTH_32BIT;
		sst_hsw_stream_set_valid(hsw, pcm_data->stream, 24);
		break;
	case SNDRV_PCM_FORMAT_S8:
		bits = SST_HSW_DEPTH_8BIT;
		sst_hsw_stream_set_valid(hsw, pcm_data->stream, 8);
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		bits = SST_HSW_DEPTH_32BIT;
		sst_hsw_stream_set_valid(hsw, pcm_data->stream, 32);
		break;
	default:
		dev_err(rtd->dev, "error: invalid format %d\n",
			params_format(params));
		return -EINVAL;
	}

	ret = sst_hsw_stream_set_bits(hsw, pcm_data->stream, bits);
	if (ret < 0) {
		dev_err(rtd->dev, "error: could not set bits %d\n", bits);
		return ret;
	}

	channels = params_channels(params);
	map = create_channel_map(SST_HSW_CHANNEL_CONFIG_STEREO);
	sst_hsw_stream_set_map_config(hsw, pcm_data->stream,
			map, SST_HSW_CHANNEL_CONFIG_STEREO);

	ret = sst_hsw_stream_set_channels(hsw, pcm_data->stream, channels);
	if (ret < 0) {
		dev_err(rtd->dev, "error: could not set channels %d\n",
			channels);
		return ret;
	}

	ret = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(params));
	if (ret < 0) {
		dev_err(rtd->dev, "error: could not allocate %d bytes for PCM %d\n",
			params_buffer_bytes(params), ret);
		return ret;
	}

	dmab = snd_pcm_get_dma_buf(substream);

	ret = create_adsp_page_table(substream, pdata, rtd, runtime->dma_area,
		runtime->dma_bytes, rtd->cpu_dai->id);
	if (ret < 0)
		return ret;

	sst_hsw_stream_set_style(hsw, pcm_data->stream,
		SST_HSW_INTERLEAVING_PER_CHANNEL);

	if (runtime->dma_bytes % PAGE_SIZE)
		pages = (runtime->dma_bytes / PAGE_SIZE) + 1;
	else
		pages = runtime->dma_bytes / PAGE_SIZE;

	ret = sst_hsw_stream_buffer(hsw, pcm_data->stream,
		pdata->dmab[rtd->cpu_dai->id][substream->stream].addr,
		pages, runtime->dma_bytes, 0,
		snd_sgbuf_get_addr(dmab, 0) >> PAGE_SHIFT);
	if (ret < 0) {
		dev_err(rtd->dev, "error: failed to set DMA buffer %d\n", ret);
		return ret;
	}

	dsp = sst_hsw_get_dsp(hsw);

	module_data = sst_module_get_from_id(dsp, module_id);
	if (module_data == NULL) {
		dev_err(rtd->dev, "error: failed to get module config\n");
		return -EINVAL;
	}

	sst_hsw_stream_set_module_info(hsw, pcm_data->stream,
		pcm_data->runtime);

	ret = sst_hsw_stream_commit(hsw, pcm_data->stream);
	if (ret < 0) {
		dev_err(rtd->dev, "error: failed to commit stream %d\n", ret);
		return ret;
	}

	if (!pcm_data->allocated) {
		/* Set previous saved volume */
		sst_hsw_stream_set_volume(hsw, pcm_data->stream, 0,
				0, pcm_data->volume[0]);
		sst_hsw_stream_set_volume(hsw, pcm_data->stream, 0,
				1, pcm_data->volume[1]);
		pcm_data->allocated = true;
	}

	ret = sst_hsw_stream_pause(hsw, pcm_data->stream, 1);
	if (ret < 0)
		dev_err(rtd->dev, "error: failed to pause %d\n", ret);

	return 0;
}