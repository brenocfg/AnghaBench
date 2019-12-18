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
struct sprd_compr_stream {TYPE_3__* dma; TYPE_2__* compr_ops; int /*<<< orphan*/  info_size; int /*<<< orphan*/  info_phys; int /*<<< orphan*/  num_channels; } ;
struct sprd_compr_params {int /*<<< orphan*/  format; int /*<<< orphan*/  rate; int /*<<< orphan*/  info_size; int /*<<< orphan*/  info_phys; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  direction; } ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {struct device* dev; } ;
struct snd_compr_stream {int /*<<< orphan*/  direction; struct snd_soc_pcm_runtime* private_data; struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct sprd_compr_stream* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  sample_rate; } ;
struct snd_compr_params {TYPE_1__ codec; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  chan; } ;
struct TYPE_5__ {int (* set_params ) (int /*<<< orphan*/ ,struct sprd_compr_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int sprd_platform_compr_dma_config (struct snd_compr_stream*,struct snd_compr_params*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct sprd_compr_params*) ; 

__attribute__((used)) static int sprd_platform_compr_set_params(struct snd_compr_stream *cstream,
					  struct snd_compr_params *params)
{
	struct snd_compr_runtime *runtime = cstream->runtime;
	struct sprd_compr_stream *stream = runtime->private_data;
	struct snd_soc_pcm_runtime *rtd = cstream->private_data;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct device *dev = component->dev;
	struct sprd_compr_params compr_params = { };
	int ret;

	/*
	 * Configure the DMA engine 2-stage transfer mode. Channel 1 set as the
	 * destination channel, and channel 0 set as the source channel, that
	 * means once the source channel's transaction is done, it will trigger
	 * the destination channel's transaction automatically.
	 */
	ret = sprd_platform_compr_dma_config(cstream, params, 1);
	if (ret) {
		dev_err(dev, "failed to config stage 1 DMA: %d\n", ret);
		return ret;
	}

	ret = sprd_platform_compr_dma_config(cstream, params, 0);
	if (ret) {
		dev_err(dev, "failed to config stage 0 DMA: %d\n", ret);
		goto config_err;
	}

	compr_params.direction = cstream->direction;
	compr_params.sample_rate = params->codec.sample_rate;
	compr_params.channels = stream->num_channels;
	compr_params.info_phys = stream->info_phys;
	compr_params.info_size = stream->info_size;
	compr_params.rate = params->codec.bit_rate;
	compr_params.format = params->codec.id;

	ret = stream->compr_ops->set_params(cstream->direction, &compr_params);
	if (ret) {
		dev_err(dev, "failed to set parameters: %d\n", ret);
		goto params_err;
	}

	return 0;

params_err:
	dma_release_channel(stream->dma[0].chan);
config_err:
	dma_release_channel(stream->dma[1].chan);
	return ret;
}