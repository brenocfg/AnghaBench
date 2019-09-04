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
typedef  int u32 ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct lpass_variant {int dummy; } ;
struct lpass_data {int /*<<< orphan*/  lpaif_map; struct lpass_variant* variant; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LPAIF_IRQCLEAR_REG (struct lpass_variant*,int /*<<< orphan*/ ) ; 
 int LPAIF_IRQ_ERR (int) ; 
 int LPAIF_IRQ_PER (int) ; 
 int /*<<< orphan*/  LPAIF_IRQ_PORT_HOST ; 
 int LPAIF_IRQ_XRUN (int) ; 
 int /*<<< orphan*/  SNDRV_PCM_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stop (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (struct snd_pcm_substream*) ; 

__attribute__((used)) static irqreturn_t lpass_dma_interrupt_handler(
			struct snd_pcm_substream *substream,
			struct lpass_data *drvdata,
			int chan, u32 interrupts)
{
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct lpass_variant *v = drvdata->variant;
	irqreturn_t ret = IRQ_NONE;
	int rv;

	if (interrupts & LPAIF_IRQ_PER(chan)) {
		rv = regmap_write(drvdata->lpaif_map,
				LPAIF_IRQCLEAR_REG(v, LPAIF_IRQ_PORT_HOST),
				LPAIF_IRQ_PER(chan));
		if (rv) {
			dev_err(soc_runtime->dev,
				"error writing to irqclear reg: %d\n", rv);
			return IRQ_NONE;
		}
		snd_pcm_period_elapsed(substream);
		ret = IRQ_HANDLED;
	}

	if (interrupts & LPAIF_IRQ_XRUN(chan)) {
		rv = regmap_write(drvdata->lpaif_map,
				LPAIF_IRQCLEAR_REG(v, LPAIF_IRQ_PORT_HOST),
				LPAIF_IRQ_XRUN(chan));
		if (rv) {
			dev_err(soc_runtime->dev,
				"error writing to irqclear reg: %d\n", rv);
			return IRQ_NONE;
		}
		dev_warn(soc_runtime->dev, "xrun warning\n");
		snd_pcm_stop_xrun(substream);
		ret = IRQ_HANDLED;
	}

	if (interrupts & LPAIF_IRQ_ERR(chan)) {
		rv = regmap_write(drvdata->lpaif_map,
				LPAIF_IRQCLEAR_REG(v, LPAIF_IRQ_PORT_HOST),
				LPAIF_IRQ_ERR(chan));
		if (rv) {
			dev_err(soc_runtime->dev,
				"error writing to irqclear reg: %d\n", rv);
			return IRQ_NONE;
		}
		dev_err(soc_runtime->dev, "bus access error\n");
		snd_pcm_stop(substream, SNDRV_PCM_STATE_DISCONNECTED);
		ret = IRQ_HANDLED;
	}

	return ret;
}