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
struct snd_soc_dai {int /*<<< orphan*/  dev; TYPE_1__* driver; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct lpass_data {int /*<<< orphan*/  variant; int /*<<< orphan*/  lpaif_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LPAIF_I2SCTL_MICEN_DISABLE ; 
 unsigned int LPAIF_I2SCTL_MICEN_ENABLE ; 
 unsigned int LPAIF_I2SCTL_MICEN_MASK ; 
 int /*<<< orphan*/  LPAIF_I2SCTL_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int LPAIF_I2SCTL_SPKEN_DISABLE ; 
 unsigned int LPAIF_I2SCTL_SPKEN_ENABLE ; 
 unsigned int LPAIF_I2SCTL_SPKEN_MASK ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct lpass_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int lpass_cpu_daiops_trigger(struct snd_pcm_substream *substream,
		int cmd, struct snd_soc_dai *dai)
{
	struct lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	int ret = -EINVAL;
	unsigned int val, mask;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			val = LPAIF_I2SCTL_SPKEN_ENABLE;
			mask = LPAIF_I2SCTL_SPKEN_MASK;
		} else  {
			val = LPAIF_I2SCTL_MICEN_ENABLE;
			mask = LPAIF_I2SCTL_MICEN_MASK;
		}

		ret = regmap_update_bits(drvdata->lpaif_map,
				LPAIF_I2SCTL_REG(drvdata->variant,
						dai->driver->id),
				mask, val);
		if (ret)
			dev_err(dai->dev, "error writing to i2sctl reg: %d\n",
				ret);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			val = LPAIF_I2SCTL_SPKEN_DISABLE;
			mask = LPAIF_I2SCTL_SPKEN_MASK;
		} else  {
			val = LPAIF_I2SCTL_MICEN_DISABLE;
			mask = LPAIF_I2SCTL_MICEN_MASK;
		}

		ret = regmap_update_bits(drvdata->lpaif_map,
				LPAIF_I2SCTL_REG(drvdata->variant,
						dai->driver->id),
				mask, val);
		if (ret)
			dev_err(dai->dev, "error writing to i2sctl reg: %d\n",
				ret);
		break;
	}

	return ret;
}