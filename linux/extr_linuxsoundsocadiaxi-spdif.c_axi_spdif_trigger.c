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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct axi_spdif {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int AXI_SPDIF_CTRL_TXDATA ; 
 int /*<<< orphan*/  AXI_SPDIF_REG_CTRL ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct axi_spdif* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axi_spdif_trigger(struct snd_pcm_substream *substream, int cmd,
	struct snd_soc_dai *dai)
{
	struct axi_spdif *spdif = snd_soc_dai_get_drvdata(dai);
	unsigned int val;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = AXI_SPDIF_CTRL_TXDATA;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = 0;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(spdif->regmap, AXI_SPDIF_REG_CTRL,
		AXI_SPDIF_CTRL_TXDATA, val);

	return 0;
}