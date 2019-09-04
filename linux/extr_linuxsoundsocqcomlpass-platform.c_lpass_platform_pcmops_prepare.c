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
struct snd_pcm_substream {int stream; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {int dma_addr; struct lpass_pcm_data* private_data; } ;
struct lpass_variant {int dummy; } ;
struct lpass_pcm_data {int dma_ch; } ;
struct lpass_data {int /*<<< orphan*/  lpaif_map; struct lpass_variant* variant; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  LPAIF_DMABASE_REG (struct lpass_variant*,int,int) ; 
 int /*<<< orphan*/  LPAIF_DMABUFF_REG (struct lpass_variant*,int,int) ; 
 int /*<<< orphan*/  LPAIF_DMACTL_ENABLE_MASK ; 
 int /*<<< orphan*/  LPAIF_DMACTL_ENABLE_ON ; 
 int /*<<< orphan*/  LPAIF_DMACTL_REG (struct lpass_variant*,int,int) ; 
 int /*<<< orphan*/  LPAIF_DMAPER_REG (struct lpass_variant*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct lpass_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpass_platform_pcmops_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(soc_runtime, DRV_NAME);
	struct lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	struct snd_pcm_runtime *rt = substream->runtime;
	struct lpass_pcm_data *pcm_data = rt->private_data;
	struct lpass_variant *v = drvdata->variant;
	int ret, ch, dir = substream->stream;

	ch = pcm_data->dma_ch;

	ret = regmap_write(drvdata->lpaif_map,
			LPAIF_DMABASE_REG(v, ch, dir),
			runtime->dma_addr);
	if (ret) {
		dev_err(soc_runtime->dev, "error writing to rdmabase reg: %d\n",
			ret);
		return ret;
	}

	ret = regmap_write(drvdata->lpaif_map,
			LPAIF_DMABUFF_REG(v, ch, dir),
			(snd_pcm_lib_buffer_bytes(substream) >> 2) - 1);
	if (ret) {
		dev_err(soc_runtime->dev, "error writing to rdmabuff reg: %d\n",
			ret);
		return ret;
	}

	ret = regmap_write(drvdata->lpaif_map,
			LPAIF_DMAPER_REG(v, ch, dir),
			(snd_pcm_lib_period_bytes(substream) >> 2) - 1);
	if (ret) {
		dev_err(soc_runtime->dev, "error writing to rdmaper reg: %d\n",
			ret);
		return ret;
	}

	ret = regmap_update_bits(drvdata->lpaif_map,
			LPAIF_DMACTL_REG(v, ch, dir),
			LPAIF_DMACTL_ENABLE_MASK, LPAIF_DMACTL_ENABLE_ON);
	if (ret) {
		dev_err(soc_runtime->dev, "error writing to rdmactl reg: %d\n",
			ret);
		return ret;
	}

	return 0;
}