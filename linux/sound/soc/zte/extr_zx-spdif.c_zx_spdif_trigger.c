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
typedef  int /*<<< orphan*/  u32 ;
struct zx_spdif_info {scalar_t__ reg_base; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 scalar_t__ ZX_FIFOCTRL ; 
 int /*<<< orphan*/  ZX_FIFOCTRL_TX_FIFO_RST ; 
 struct zx_spdif_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zx_spdif_cfg_tx (scalar_t__,int) ; 

__attribute__((used)) static int zx_spdif_trigger(struct snd_pcm_substream *substream, int cmd,
			    struct snd_soc_dai *dai)
{
	u32 val;
	struct zx_spdif_info *zx_spdif = dev_get_drvdata(dai->dev);
	int  ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		val = readl_relaxed(zx_spdif->reg_base + ZX_FIFOCTRL);
		val |= ZX_FIFOCTRL_TX_FIFO_RST;
		writel_relaxed(val, zx_spdif->reg_base + ZX_FIFOCTRL);
	/* fall thru */
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		zx_spdif_cfg_tx(zx_spdif->reg_base, true);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		zx_spdif_cfg_tx(zx_spdif->reg_base, false);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}