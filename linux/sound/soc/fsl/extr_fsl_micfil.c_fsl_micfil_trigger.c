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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct fsl_micfil {int /*<<< orphan*/  regmap; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MICFIL_CTRL1_DISEL_MASK ; 
 int MICFIL_CTRL1_DISEL_SHIFT ; 
 int MICFIL_CTRL1_PDMIEN ; 
 int /*<<< orphan*/  MICFIL_CTRL1_PDMIEN_MASK ; 
 int /*<<< orphan*/  REG_MICFIL_CTRL1 ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int fsl_micfil_reset (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct fsl_micfil* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_micfil_trigger(struct snd_pcm_substream *substream, int cmd,
			      struct snd_soc_dai *dai)
{
	struct fsl_micfil *micfil = snd_soc_dai_get_drvdata(dai);
	struct device *dev = &micfil->pdev->dev;
	int ret;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = fsl_micfil_reset(dev);
		if (ret) {
			dev_err(dev, "failed to soft reset\n");
			return ret;
		}

		/* DMA Interrupt Selection - DISEL bits
		 * 00 - DMA and IRQ disabled
		 * 01 - DMA req enabled
		 * 10 - IRQ enabled
		 * 11 - reserved
		 */
		ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
					 MICFIL_CTRL1_DISEL_MASK,
					 (1 << MICFIL_CTRL1_DISEL_SHIFT));
		if (ret) {
			dev_err(dev, "failed to update DISEL bits\n");
			return ret;
		}

		/* Enable the module */
		ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
					 MICFIL_CTRL1_PDMIEN_MASK,
					 MICFIL_CTRL1_PDMIEN);
		if (ret) {
			dev_err(dev, "failed to enable the module\n");
			return ret;
		}

		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/* Disable the module */
		ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
					 MICFIL_CTRL1_PDMIEN_MASK,
					 0);
		if (ret) {
			dev_err(dev, "failed to enable the module\n");
			return ret;
		}

		ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
					 MICFIL_CTRL1_DISEL_MASK,
					 (0 << MICFIL_CTRL1_DISEL_SHIFT));
		if (ret) {
			dev_err(dev, "failed to update DISEL bits\n");
			return ret;
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}