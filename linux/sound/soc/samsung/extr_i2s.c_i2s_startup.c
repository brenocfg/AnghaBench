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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct samsung_i2s_priv {int quirks; int /*<<< orphan*/  pcm_lock; } ;
struct i2s_dai {TYPE_1__* priv; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_RSTCLR ; 
 int /*<<< orphan*/  DAI_MANAGER ; 
 int /*<<< orphan*/  DAI_OPENED ; 
 scalar_t__ I2SCON ; 
 int QUIRK_NEED_RSTCLR ; 
 int /*<<< orphan*/  any_active (struct i2s_dai*) ; 
 struct i2s_dai* get_other_dai (struct i2s_dai*) ; 
 scalar_t__ is_manager (struct i2s_dai*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct samsung_i2s_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct i2s_dai* to_info (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int i2s_startup(struct snd_pcm_substream *substream,
	  struct snd_soc_dai *dai)
{
	struct samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	struct i2s_dai *i2s = to_info(dai);
	struct i2s_dai *other = get_other_dai(i2s);
	unsigned long flags;

	pm_runtime_get_sync(dai->dev);

	spin_lock_irqsave(&priv->pcm_lock, flags);

	i2s->mode |= DAI_OPENED;

	if (is_manager(other))
		i2s->mode &= ~DAI_MANAGER;
	else
		i2s->mode |= DAI_MANAGER;

	if (!any_active(i2s) && (priv->quirks & QUIRK_NEED_RSTCLR))
		writel(CON_RSTCLR, i2s->priv->addr + I2SCON);

	spin_unlock_irqrestore(&priv->pcm_lock, flags);

	return 0;
}