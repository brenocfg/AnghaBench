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
struct snd_soc_dai {struct device* dev; } ;
struct fsl_micfil {int* channel_gain; int /*<<< orphan*/  regmap; TYPE_1__* soc; int /*<<< orphan*/  dma_params_rx; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fifo_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICFIL_CTRL2_QSEL_MASK ; 
 int MICFIL_FIFO_CTRL_FIFOWMK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MICFIL_FIFO_CTRL_FIFOWMK_MASK ; 
 unsigned int MICFIL_MEDIUM_QUALITY ; 
 int /*<<< orphan*/  REG_MICFIL_CTRL2 ; 
 int /*<<< orphan*/  REG_MICFIL_FIFO_CTRL ; 
 int /*<<< orphan*/  REG_MICFIL_OUT_CTRL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct fsl_micfil* dev_get_drvdata (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dai_set_drvdata (struct snd_soc_dai*,struct fsl_micfil*) ; 

__attribute__((used)) static int fsl_micfil_dai_probe(struct snd_soc_dai *cpu_dai)
{
	struct fsl_micfil *micfil = dev_get_drvdata(cpu_dai->dev);
	struct device *dev = cpu_dai->dev;
	unsigned int val;
	int ret;
	int i;

	/* set qsel to medium */
	ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL2,
				 MICFIL_CTRL2_QSEL_MASK, MICFIL_MEDIUM_QUALITY);
	if (ret) {
		dev_err(dev, "failed to set quality mode bits, reg 0x%X\n",
			REG_MICFIL_CTRL2);
		return ret;
	}

	/* set default gain to max_gain */
	regmap_write(micfil->regmap, REG_MICFIL_OUT_CTRL, 0x77777777);
	for (i = 0; i < 8; i++)
		micfil->channel_gain[i] = 0xF;

	snd_soc_dai_init_dma_data(cpu_dai, NULL,
				  &micfil->dma_params_rx);

	/* FIFO Watermark Control - FIFOWMK*/
	val = MICFIL_FIFO_CTRL_FIFOWMK(micfil->soc->fifo_depth) - 1;
	ret = regmap_update_bits(micfil->regmap, REG_MICFIL_FIFO_CTRL,
				 MICFIL_FIFO_CTRL_FIFOWMK_MASK,
				 val);
	if (ret) {
		dev_err(dev, "failed to set FIFOWMK\n");
		return ret;
	}

	snd_soc_dai_set_drvdata(cpu_dai, micfil);

	return 0;
}