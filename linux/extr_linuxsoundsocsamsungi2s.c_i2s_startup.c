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
struct i2s_dai {int quirks; scalar_t__ addr; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_RSTCLR ; 
 int /*<<< orphan*/  DAI_MANAGER ; 
 int /*<<< orphan*/  DAI_OPENED ; 
 scalar_t__ I2SCON ; 
 int QUIRK_NEED_RSTCLR ; 
 int /*<<< orphan*/  any_active (struct i2s_dai*) ; 
 struct i2s_dai* get_other_dai (struct i2s_dai*) ; 
 scalar_t__ is_manager (struct i2s_dai*) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct i2s_dai* to_info (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int i2s_startup(struct snd_pcm_substream *substream,
	  struct snd_soc_dai *dai)
{
	struct i2s_dai *i2s = to_info(dai);
	struct i2s_dai *other = get_other_dai(i2s);
	unsigned long flags;

	pm_runtime_get_sync(dai->dev);

	spin_lock_irqsave(&lock, flags);

	i2s->mode |= DAI_OPENED;

	if (is_manager(other))
		i2s->mode &= ~DAI_MANAGER;
	else
		i2s->mode |= DAI_MANAGER;

	if (!any_active(i2s) && (i2s->quirks & QUIRK_NEED_RSTCLR))
		writel(CON_RSTCLR, i2s->addr + I2SCON);

	spin_unlock_irqrestore(&lock, flags);

	return 0;
}