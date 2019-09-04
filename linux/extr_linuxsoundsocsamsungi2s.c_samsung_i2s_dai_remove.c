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
struct i2s_dai {int quirks; int /*<<< orphan*/  lock; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ I2SCON ; 
 int QUIRK_NEED_RSTCLR ; 
 int /*<<< orphan*/  is_secondary (struct i2s_dai*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct i2s_dai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int samsung_i2s_dai_remove(struct snd_soc_dai *dai)
{
	struct i2s_dai *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned long flags;

	pm_runtime_get_sync(dai->dev);

	if (!is_secondary(i2s)) {
		if (i2s->quirks & QUIRK_NEED_RSTCLR) {
			spin_lock_irqsave(i2s->lock, flags);
			writel(0, i2s->addr + I2SCON);
			spin_unlock_irqrestore(i2s->lock, flags);
		}
	}

	pm_runtime_put(dai->dev);

	return 0;
}