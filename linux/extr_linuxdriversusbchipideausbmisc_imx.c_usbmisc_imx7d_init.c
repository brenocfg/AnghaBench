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
 int MX6_BM_OVER_CUR_DIS ; 
 int MX6_BM_OVER_CUR_POLARITY ; 
 scalar_t__ MX7D_USBNC_USB_CTRL2 ; 
 int MX7D_USB_VBUS_WAKEUP_SOURCE_BVALID ; 
 int MX7D_USB_VBUS_WAKEUP_SOURCE_MASK ; 
 struct imx_usbmisc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usbmisc_imx7d_set_wakeup (struct imx_usbmisc_data*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int usbmisc_imx7d_init(struct imx_usbmisc_data *data)
{
	struct imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	unsigned long flags;
	u32 reg;

	if (data->index >= 1)
		return -EINVAL;

	spin_lock_irqsave(&usbmisc->lock, flags);
	reg = readl(usbmisc->base);
	if (data->disable_oc) {
		reg |= MX6_BM_OVER_CUR_DIS;
	} else if (data->oc_polarity == 1) {
		/* High active */
		reg &= ~(MX6_BM_OVER_CUR_DIS | MX6_BM_OVER_CUR_POLARITY);
	}
	writel(reg, usbmisc->base);

	reg = readl(usbmisc->base + MX7D_USBNC_USB_CTRL2);
	reg &= ~MX7D_USB_VBUS_WAKEUP_SOURCE_MASK;
	writel(reg | MX7D_USB_VBUS_WAKEUP_SOURCE_BVALID,
		 usbmisc->base + MX7D_USBNC_USB_CTRL2);
	spin_unlock_irqrestore(&usbmisc->lock, flags);

	usbmisc_imx7d_set_wakeup(data, false);

	return 0;
}