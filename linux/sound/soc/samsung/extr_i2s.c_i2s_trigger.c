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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct samsung_i2s_priv {int /*<<< orphan*/  lock; } ;
struct i2s_dai {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIC_RXFLUSH ; 
 int /*<<< orphan*/  FIC_TXFLUSH ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  config_setup (struct i2s_dai*) ; 
 int /*<<< orphan*/  i2s_fifo (struct i2s_dai*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_rxctrl (struct i2s_dai*,int) ; 
 int /*<<< orphan*/  i2s_txctrl (struct i2s_dai*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct samsung_i2s_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct i2s_dai* to_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2s_trigger(struct snd_pcm_substream *substream,
	int cmd, struct snd_soc_dai *dai)
{
	struct samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	int capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct i2s_dai *i2s = to_info(rtd->cpu_dai);
	unsigned long flags;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		pm_runtime_get_sync(dai->dev);
		spin_lock_irqsave(&priv->lock, flags);

		if (config_setup(i2s)) {
			spin_unlock_irqrestore(&priv->lock, flags);
			return -EINVAL;
		}

		if (capture)
			i2s_rxctrl(i2s, 1);
		else
			i2s_txctrl(i2s, 1);

		spin_unlock_irqrestore(&priv->lock, flags);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&priv->lock, flags);

		if (capture) {
			i2s_rxctrl(i2s, 0);
			i2s_fifo(i2s, FIC_RXFLUSH);
		} else {
			i2s_txctrl(i2s, 0);
			i2s_fifo(i2s, FIC_TXFLUSH);
		}

		spin_unlock_irqrestore(&priv->lock, flags);
		pm_runtime_put(dai->dev);
		break;
	}

	return 0;
}