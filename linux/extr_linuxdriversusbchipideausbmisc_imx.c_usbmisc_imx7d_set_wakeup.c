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
typedef  int u32 ;
struct imx_usbmisc_data {int /*<<< orphan*/  dev; } ;
struct imx_usbmisc {int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int MX6_BM_ID_WAKEUP ; 
 int MX6_BM_VBUS_WAKEUP ; 
 int MX6_BM_WAKEUP_ENABLE ; 
 int MX6_BM_WAKEUP_INTR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct imx_usbmisc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbmisc_imx7d_set_wakeup
	(struct imx_usbmisc_data *data, bool enabled)
{
	struct imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	unsigned long flags;
	u32 val;
	u32 wakeup_setting = (MX6_BM_WAKEUP_ENABLE |
		MX6_BM_VBUS_WAKEUP | MX6_BM_ID_WAKEUP);

	spin_lock_irqsave(&usbmisc->lock, flags);
	val = readl(usbmisc->base);
	if (enabled) {
		writel(val | wakeup_setting, usbmisc->base);
	} else {
		if (val & MX6_BM_WAKEUP_INTR)
			dev_dbg(data->dev, "wakeup int\n");
		writel(val & ~wakeup_setting, usbmisc->base);
	}
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	return 0;
}