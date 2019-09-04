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
struct imx_usbmisc_data {int index; int oc_polarity; scalar_t__ disable_oc; int /*<<< orphan*/  dev; } ;
struct imx_usbmisc {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int MX6_BM_NON_BURST_SETTING ; 
 int MX6_BM_OVER_CUR_DIS ; 
 int MX6_BM_OVER_CUR_POLARITY ; 
 struct imx_usbmisc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usbmisc_imx6q_set_wakeup (struct imx_usbmisc_data*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int usbmisc_imx6q_init(struct imx_usbmisc_data *data)
{
	struct imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	unsigned long flags;
	u32 reg;

	if (data->index > 3)
		return -EINVAL;

	spin_lock_irqsave(&usbmisc->lock, flags);

	reg = readl(usbmisc->base + data->index * 4);
	if (data->disable_oc) {
		reg |= MX6_BM_OVER_CUR_DIS;
	} else if (data->oc_polarity == 1) {
		/* High active */
		reg &= ~(MX6_BM_OVER_CUR_DIS | MX6_BM_OVER_CUR_POLARITY);
	}
	writel(reg, usbmisc->base + data->index * 4);

	/* SoC non-burst setting */
	reg = readl(usbmisc->base + data->index * 4);
	writel(reg | MX6_BM_NON_BURST_SETTING,
			usbmisc->base + data->index * 4);

	spin_unlock_irqrestore(&usbmisc->lock, flags);

	usbmisc_imx6q_set_wakeup(data, false);

	return 0;
}