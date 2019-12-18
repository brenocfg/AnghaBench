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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct samsung_i2s_priv {int /*<<< orphan*/  pcm_lock; } ;
struct i2s_dai {scalar_t__ bfs; scalar_t__ rfs; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAI_MANAGER ; 
 int /*<<< orphan*/  DAI_OPENED ; 
 struct i2s_dai* get_other_dai (struct i2s_dai*) ; 
 scalar_t__ is_opened (struct i2s_dai*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct samsung_i2s_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct i2s_dai* to_info (struct snd_soc_dai*) ; 

__attribute__((used)) static void i2s_shutdown(struct snd_pcm_substream *substream,
	struct snd_soc_dai *dai)
{
	struct samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	struct i2s_dai *i2s = to_info(dai);
	struct i2s_dai *other = get_other_dai(i2s);
	unsigned long flags;

	spin_lock_irqsave(&priv->pcm_lock, flags);

	i2s->mode &= ~DAI_OPENED;
	i2s->mode &= ~DAI_MANAGER;

	if (is_opened(other))
		other->mode |= DAI_MANAGER;

	/* Reset any constraint on RFS and BFS */
	i2s->rfs = 0;
	i2s->bfs = 0;

	spin_unlock_irqrestore(&priv->pcm_lock, flags);

	pm_runtime_put(dai->dev);
}