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
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct lpass_pcm_data* private_data; } ;
struct lpass_variant {int /*<<< orphan*/  (* free_dma_channel ) (struct lpass_data*,size_t) ;} ;
struct lpass_pcm_data {size_t dma_ch; } ;
struct lpass_data {int /*<<< orphan*/ ** substream; struct lpass_variant* variant; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 struct lpass_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct lpass_data*,size_t) ; 

__attribute__((used)) static int lpass_platform_pcmops_close(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(soc_runtime, DRV_NAME);
	struct lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	struct lpass_variant *v = drvdata->variant;
	struct lpass_pcm_data *data;

	data = runtime->private_data;
	drvdata->substream[data->dma_ch] = NULL;
	if (v->free_dma_channel)
		v->free_dma_channel(drvdata, data->dma_ch);

	return 0;
}