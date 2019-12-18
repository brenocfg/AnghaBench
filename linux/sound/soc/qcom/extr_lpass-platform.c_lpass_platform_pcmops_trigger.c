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
struct snd_pcm_runtime {struct lpass_pcm_data* private_data; } ;
struct lpass_variant {int dummy; } ;
struct lpass_pcm_data {int dma_ch; } ;
struct lpass_data {int /*<<< orphan*/  lpaif_map; struct lpass_variant* variant; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  LPAIF_DMACTL_ENABLE_MASK ; 
 int /*<<< orphan*/  LPAIF_DMACTL_ENABLE_OFF ; 
 int /*<<< orphan*/  LPAIF_DMACTL_ENABLE_ON ; 
 int /*<<< orphan*/  LPAIF_DMACTL_REG (struct lpass_variant*,int,int) ; 
 int /*<<< orphan*/  LPAIF_IRQCLEAR_REG (struct lpass_variant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPAIF_IRQEN_REG (struct lpass_variant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPAIF_IRQ_ALL (int) ; 
 int /*<<< orphan*/  LPAIF_IRQ_PORT_HOST ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lpass_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpass_platform_pcmops_trigger(struct snd_pcm_substream *substream,
		int cmd)
{
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(soc_runtime, DRV_NAME);
	struct lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	struct snd_pcm_runtime *rt = substream->runtime;
	struct lpass_pcm_data *pcm_data = rt->private_data;
	struct lpass_variant *v = drvdata->variant;
	int ret, ch, dir = substream->stream;

	ch = pcm_data->dma_ch;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/* clear status before enabling interrupts */
		ret = regmap_write(drvdata->lpaif_map,
				LPAIF_IRQCLEAR_REG(v, LPAIF_IRQ_PORT_HOST),
				LPAIF_IRQ_ALL(ch));
		if (ret) {
			dev_err(soc_runtime->dev,
				"error writing to irqclear reg: %d\n", ret);
			return ret;
		}

		ret = regmap_update_bits(drvdata->lpaif_map,
				LPAIF_IRQEN_REG(v, LPAIF_IRQ_PORT_HOST),
				LPAIF_IRQ_ALL(ch),
				LPAIF_IRQ_ALL(ch));
		if (ret) {
			dev_err(soc_runtime->dev,
				"error writing to irqen reg: %d\n", ret);
			return ret;
		}

		ret = regmap_update_bits(drvdata->lpaif_map,
				LPAIF_DMACTL_REG(v, ch, dir),
				LPAIF_DMACTL_ENABLE_MASK,
				LPAIF_DMACTL_ENABLE_ON);
		if (ret) {
			dev_err(soc_runtime->dev,
				"error writing to rdmactl reg: %d\n", ret);
			return ret;
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = regmap_update_bits(drvdata->lpaif_map,
				LPAIF_DMACTL_REG(v, ch, dir),
				LPAIF_DMACTL_ENABLE_MASK,
				LPAIF_DMACTL_ENABLE_OFF);
		if (ret) {
			dev_err(soc_runtime->dev,
				"error writing to rdmactl reg: %d\n", ret);
			return ret;
		}

		ret = regmap_update_bits(drvdata->lpaif_map,
				LPAIF_IRQEN_REG(v, LPAIF_IRQ_PORT_HOST),
				LPAIF_IRQ_ALL(ch), 0);
		if (ret) {
			dev_err(soc_runtime->dev,
				"error writing to irqen reg: %d\n", ret);
			return ret;
		}
		break;
	}

	return 0;
}