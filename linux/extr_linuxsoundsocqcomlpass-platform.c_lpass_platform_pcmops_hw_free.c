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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {struct lpass_pcm_data* private_data; } ;
struct lpass_variant {int dummy; } ;
struct lpass_pcm_data {int /*<<< orphan*/  dma_ch; } ;
struct lpass_data {int /*<<< orphan*/  lpaif_map; struct lpass_variant* variant; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 unsigned int LPAIF_DMACTL_REG (struct lpass_variant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct lpass_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpass_platform_pcmops_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(soc_runtime, DRV_NAME);
	struct lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	struct snd_pcm_runtime *rt = substream->runtime;
	struct lpass_pcm_data *pcm_data = rt->private_data;
	struct lpass_variant *v = drvdata->variant;
	unsigned int reg;
	int ret;

	reg = LPAIF_DMACTL_REG(v, pcm_data->dma_ch, substream->stream);
	ret = regmap_write(drvdata->lpaif_map, reg, 0);
	if (ret)
		dev_err(soc_runtime->dev, "error writing to rdmactl reg: %d\n",
			ret);

	return ret;
}