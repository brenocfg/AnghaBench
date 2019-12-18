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
struct samsung_i2s_priv {int quirks; int /*<<< orphan*/  lock; scalar_t__ addr; } ;
struct i2s_dai {int dummy; } ;

/* Variables and functions */
 scalar_t__ I2SCON ; 
 int QUIRK_NEED_RSTCLR ; 
 int /*<<< orphan*/  is_secondary (struct i2s_dai*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct samsung_i2s_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct i2s_dai* to_info (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int samsung_i2s_dai_remove(struct snd_soc_dai *dai)
{
	struct samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	struct i2s_dai *i2s = to_info(dai);
	unsigned long flags;

	pm_runtime_get_sync(dai->dev);

	if (!is_secondary(i2s)) {
		if (priv->quirks & QUIRK_NEED_RSTCLR) {
			spin_lock_irqsave(&priv->lock, flags);
			writel(0, priv->addr + I2SCON);
			spin_unlock_irqrestore(&priv->lock, flags);
		}
	}

	pm_runtime_put(dai->dev);

	return 0;
}