#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  str_id; } ;
struct sst_runtime_stream {TYPE_6__* ops; TYPE_5__ stream_info; } ;
struct sst_data {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {TYPE_2__ member_0; } ;
struct snd_sst_stream_params {TYPE_1__ member_0; } ;
struct snd_sst_alloc_params_ext {int /*<<< orphan*/  member_0; } ;
struct snd_sst_params {int /*<<< orphan*/  stream_id; int /*<<< orphan*/  codec; struct snd_sst_alloc_params_ext aparams; struct snd_sst_stream_params sparams; int /*<<< orphan*/  member_0; } ;
struct snd_soc_dai {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  area; } ;
struct snd_pcm_substream {TYPE_4__ dma_buffer; TYPE_3__* runtime; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int (* open ) (int /*<<< orphan*/ ,struct snd_sst_params*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  dma_area; struct sst_runtime_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_CODEC_TYPE_PCM ; 
 struct sst_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 TYPE_7__* sst ; 
 int /*<<< orphan*/  sst_fill_alloc_params (struct snd_pcm_substream*,struct snd_sst_alloc_params_ext*) ; 
 int /*<<< orphan*/  sst_fill_pcm_params (struct snd_pcm_substream*,struct snd_sst_stream_params*) ; 
 int sst_fill_stream_params (struct snd_pcm_substream*,struct sst_data*,struct snd_sst_params*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct snd_sst_params*) ; 

__attribute__((used)) static int sst_platform_alloc_stream(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct sst_runtime_stream *stream =
			substream->runtime->private_data;
	struct snd_sst_stream_params param = {{{0,},},};
	struct snd_sst_params str_params = {0};
	struct snd_sst_alloc_params_ext alloc_params = {0};
	int ret_val = 0;
	struct sst_data *ctx = snd_soc_dai_get_drvdata(dai);

	/* set codec params and inform SST driver the same */
	sst_fill_pcm_params(substream, &param);
	sst_fill_alloc_params(substream, &alloc_params);
	substream->runtime->dma_area = substream->dma_buffer.area;
	str_params.sparams = param;
	str_params.aparams = alloc_params;
	str_params.codec = SST_CODEC_TYPE_PCM;

	/* fill the device type and stream id to pass to SST driver */
	ret_val = sst_fill_stream_params(substream, ctx, &str_params, false);
	if (ret_val < 0)
		return ret_val;

	stream->stream_info.str_id = str_params.stream_id;

	ret_val = stream->ops->open(sst->dev, &str_params);
	if (ret_val <= 0)
		return ret_val;


	return ret_val;
}