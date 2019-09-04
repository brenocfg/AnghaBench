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
struct sdio_func {int dummy; } ;
struct lbs_private {int power_up_on_resume; scalar_t__ wol_criteria; scalar_t__ fw_ready; } ;
struct if_sdio_card {struct lbs_private* priv; } ;
struct device {int dummy; } ;
typedef  int mmc_pm_flag_t ;

/* Variables and functions */
 scalar_t__ EHS_REMOVE_WAKEUP ; 
 int ENOSYS ; 
 int MMC_PM_KEEP_POWER ; 
 int MMC_PM_WAKE_SDIO_IRQ ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 struct sdio_func* dev_to_sdio_func (struct device*) ; 
 int /*<<< orphan*/  if_sdio_power_off (struct if_sdio_card*) ; 
 int /*<<< orphan*/  lbs_iface_active (struct lbs_private*) ; 
 int lbs_suspend (struct lbs_private*) ; 
 int /*<<< orphan*/  sdio_func_id (struct sdio_func*) ; 
 struct if_sdio_card* sdio_get_drvdata (struct sdio_func*) ; 
 int sdio_get_host_pm_caps (struct sdio_func*) ; 
 int sdio_set_host_pm_flags (struct sdio_func*,int) ; 

__attribute__((used)) static int if_sdio_suspend(struct device *dev)
{
	struct sdio_func *func = dev_to_sdio_func(dev);
	struct if_sdio_card *card = sdio_get_drvdata(func);
	struct lbs_private *priv = card->priv;
	int ret;

	mmc_pm_flag_t flags = sdio_get_host_pm_caps(func);
	priv->power_up_on_resume = false;

	/* If we're powered off anyway, just let the mmc layer remove the
	 * card. */
	if (!lbs_iface_active(priv)) {
		if (priv->fw_ready) {
			priv->power_up_on_resume = true;
			if_sdio_power_off(card);
		}

		return 0;
	}

	dev_info(dev, "%s: suspend: PM flags = 0x%x\n",
		 sdio_func_id(func), flags);

	/* If we aren't being asked to wake on anything, we should bail out
	 * and let the SD stack power down the card.
	 */
	if (priv->wol_criteria == EHS_REMOVE_WAKEUP) {
		dev_info(dev, "Suspend without wake params -- powering down card\n");
		if (priv->fw_ready) {
			ret = lbs_suspend(priv);
			if (ret)
				return ret;

			priv->power_up_on_resume = true;
			if_sdio_power_off(card);
		}

		return 0;
	}

	if (!(flags & MMC_PM_KEEP_POWER)) {
		dev_err(dev, "%s: cannot remain alive while host is suspended\n",
			sdio_func_id(func));
		return -ENOSYS;
	}

	ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
	if (ret)
		return ret;

	ret = lbs_suspend(priv);
	if (ret)
		return ret;

	return sdio_set_host_pm_flags(func, MMC_PM_WAKE_SDIO_IRQ);
}