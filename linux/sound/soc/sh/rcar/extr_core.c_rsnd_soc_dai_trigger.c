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
struct rsnd_priv {int /*<<< orphan*/  lock; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  irq ; 
 int /*<<< orphan*/  quit ; 
 int rsnd_dai_call (int /*<<< orphan*/ ,struct rsnd_dai_stream*,struct rsnd_priv*,...) ; 
 struct rsnd_priv* rsnd_dai_to_priv (struct snd_soc_dai*) ; 
 struct rsnd_dai* rsnd_dai_to_rdai (struct snd_soc_dai*) ; 
 struct rsnd_dai_stream* rsnd_rdai_to_io (struct rsnd_dai*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start ; 
 int /*<<< orphan*/  stop ; 

__attribute__((used)) static int rsnd_soc_dai_trigger(struct snd_pcm_substream *substream, int cmd,
			    struct snd_soc_dai *dai)
{
	struct rsnd_priv *priv = rsnd_dai_to_priv(dai);
	struct rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	struct rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		ret = rsnd_dai_call(init, io, priv);
		if (ret < 0)
			goto dai_trigger_end;

		ret = rsnd_dai_call(start, io, priv);
		if (ret < 0)
			goto dai_trigger_end;

		ret = rsnd_dai_call(irq, io, priv, 1);
		if (ret < 0)
			goto dai_trigger_end;

		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		ret = rsnd_dai_call(irq, io, priv, 0);

		ret |= rsnd_dai_call(stop, io, priv);

		ret |= rsnd_dai_call(quit, io, priv);

		break;
	default:
		ret = -EINVAL;
	}

dai_trigger_end:
	spin_unlock_irqrestore(&priv->lock, flags);

	return ret;
}